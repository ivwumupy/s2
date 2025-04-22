#include <metal_stdlib>
using namespace metal;

struct uniform_data {
  float2 viewport_size;
};

// [SECTION] triangle pipeline

struct triangle_vin {
  float2 position [[attribute(0)]];
  uchar4 color [[attribute(1)]];
};

struct triangle_vout {
  float4 position [[position]];
  float4 color;
};

[[vertex]]
triangle_vout triangle_vertex(triangle_vin in [[stage_in]],
                              constant uniform_data const& uniform [[buffer(1)]]) {
  triangle_vout out;
  out.position = float4(in.position, 0.0, 1.0);
  out.color = float4(in.color) / float4(255.0);
  return out;
}

[[fragment]]
float4 triangle_fragment(triangle_vout in [[stage_in]]) {
  return in.color;
}
