#include <metal_stdlib>
using namespace metal;

struct uniform_data {
  float4x4 proj;
};

struct vertex_in {
  float2 position [[attribute(0)]];
  float2 tex_coord [[attribute(1)]];
  uchar4 color [[attribute(2)]];
};

struct vertex_out {
  float4 position [[position]];
  float2 tex_coord;
  float4 color;
};

[[vertex]]
vertex_out quad_vertex(vertex_in in [[stage_in]],
                       constant uniform_data const& uniform [[buffer(1)]]) {
  vertex_out out;
  out.position = uniform.proj * float4(in.position, 0.0, 1.0);
  out.tex_coord = in.tex_coord;
  out.color = float4(in.color) / float4(255.0);
  return out;
}

[[fragment]]
float4 quad_fragment(vertex_out in [[stage_in]],
                     texture2d<float> texture [[texture(0)]]) {
  constexpr sampler texture_sampler(min_filter::linear, mag_filter::linear, mip_filter::linear);
  float4 tex_color = texture.sample(texture_sampler, in.tex_coord);
  return in.color * tex_color;
}
