#include <metal_stdlib>
using namespace metal;

struct uniform_data {
  float2 viewport_size;
};

struct sdf_vout {
  float4 position [[position]];
};

constant float4 vertices[] = {
  {-1.0,  1.0, 0.0, 1.0},
  {-1.0, -1.0, 0.0, 1.0},
  { 1.0,  1.0, 0.0, 1.0},
};

[[vertex]]
float4 sdf_vert(uint vid [[vertex_id]]) {
  return vertices[vid];
}

float sdf_circle(float2 p, float r) {
  return length(p) - r;
}

float sdf_segment(float2 p, float2 a, float2 b) {
  float2 ap = p - a;
  float2 ab = b - a;
  float t = clamp(dot(ap, ab) / dot(ab, ab), 0.0, 1.0);
  return length(ap - ab * t);
}

[[fragment]]
float4 sdf_frag(sdf_vout in [[stage_in]], constant uniform_data const& uniform [[buffer(0)]]) {
  float2 p = in.position.xy;
  float2 o = uniform.viewport_size / 2.0;
  float d = sdf_circle(p - o, 400);
  //d = sdf_segment(p, float2(100,100), float2(300, 400));
  float3 c0 = float3(0, 0, 0);
  float3 c1 = float3(1, 1, 1);
  float3 col = mix(c0, c1, clamp(1.0 - d, 0.0, 1.0));
  return float4(col, 1.0);
}
