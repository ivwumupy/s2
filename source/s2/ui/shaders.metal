#include <metal_stdlib>
using namespace metal;

struct uniform_data {
  //float2 viewport_size;
  uint cmd_count;
};

struct sdf_vout {
  float4 position [[position]];
};

constant float4 vertices[] = {
  {-1.0,  1.0, 0.0, 1.0},
  {-1.0, -3.0, 0.0, 1.0},
  { 3.0,  1.0, 0.0, 1.0},
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

enum {
  CMD_CIRCLE,
  CMD_SEGMENT,
};

[[fragment]]
float4 sdf_frag(
  sdf_vout in [[stage_in]],
  constant uniform_data const& uniform [[buffer(0)]],
  constant uint8_t const* cmds [[buffer(1)]],
  constant float const* data [[buffer(2)]]
) {
  float2 p = in.position.xy;
  uint j = 0;
  float3 c0 = float3(0, 0, 0);
  float3 c1 = float3(1, 1, 1);
  float3 col = c0;
  for (uint i = 0; i < uniform.cmd_count; i++) {
    uint8_t cmd = cmds[i];
    float d = 1.0;
    if (cmd == CMD_CIRCLE) {
      float2 center = float2(data[j], data[j+1]);
      float radius = data[j+2];
      d = sdf_circle(p - center, radius);
      j += 3;
    } else if (cmd == CMD_SEGMENT) {
      float2 start = float2(data[j], data[j+1]);
      float2 end = float2(data[j+2], data[j+3]);
      d = sdf_segment(p, start, end);
      j += 4;
    } else {
      // do nothing
    }
    col = mix(col, c1, clamp(1.0 - d, 0.0, 1.0));
  }
  return float4(col, 1.0);
}
