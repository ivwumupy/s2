#include <metal_stdlib>
using namespace metal;

struct uniform_data {
  float2 viewport_size;
};

// [SECTION] triangle pipeline

struct triangle_vin {
  float2 position [[attribute(0)]];
  float3 color [[attribute(1)]];
};

struct triangle_vout {
  float4 position [[position]];
  float4 color;
};

[[vertex]]
triangle_vout triangle_vertex(triangle_vin in [[stage_in]],
                              constant uniform_data const& uniform [[buffer(0)]]) {
  triangle_vout out;
  out.position = float4(in.position, 0.0, 1.0);
  out.position.xy /= uniform.viewport_size / 2.0;
  out.color = float4(in.color, 1.0);
  return out;
}

[[fragment]]
float4 triangle_fragment(triangle_vout in [[stage_in]]) {
  return in.color;
}

// [SECTION] color wheel

struct color_wheel_data {
  float2 center;
  float inner_radius;
  float outer_radius;
};

struct color_wheel_vin {
  float2 position [[attribute(0)]];
};

struct color_wheel_vout {
  float4 position [[position]];
  float2 screen_position;
};

[[vertex]]
color_wheel_vout color_wheel_vertex(
  constant uniform_data const& uniform [[buffer(0)]],
  color_wheel_vin in [[stage_in]],
  constant color_wheel_data const& data [[buffer(2)]]
) {
  color_wheel_vout out;
  float2 d = (in.position - float2(0.5, 0.5)) * 2; // d in {+1, -1} x {+1, -1}
  d += normalize(d) * (2.0 / data.outer_radius);
  float2 pos = data.center + d * data.outer_radius;
  out.screen_position = pos;
  out.position = float4(pos, 0.0, 1.0);
  out.position.xy /= uniform.viewport_size / 2.0;
  return out;
}

[[fragment]]
float4 color_wheel_fragment(
  color_wheel_vout in [[stage_in]],
  constant color_wheel_data const& data [[buffer(0)]]
) {
  float2 v = in.screen_position - data.center;
  float theta = atan2(v.y, v.x) + M_PI_F; // [0, 2pi]
  float h = theta / (2 * M_PI_F); // [0, 1]
  float3 rgb =
    clamp(
      abs(
        fmod(h * 6 + float3(0.0, 4.0, 2.0), 6.0)
        - 3.0)
      - 1.0,
      0.0, 1.0);
  float d = length(v);
  if (d < data.inner_radius || d > data.outer_radius) return float4(0.0, 0.0, 0.0, 0.0);
  return float4(rgb, 1.0);
}
