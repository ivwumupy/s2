#include "s2/ui/macos_render_manager.h"

//
#include "s2/ui/draw_batch.h"
#include "s2/ui/macos_shaders.h"
#include "s2/ui/macos_window.h"

namespace s2::ui {
namespace internal {
namespace {
struct uniform_data {
  float viewport_size[2];
};
} // namespace
} // namespace internal
macos_render_manager::macos_render_manager() {
  device_ = MTLCreateSystemDefaultDevice();
  queue_ = [device_ newCommandQueue];
  init_shaders();
  init_pipelines();
  init_pass_desc();
}
macos_render_manager::~macos_render_manager() {
  [pass_desc_ release];
  [triangle_pipeline_ release];
  [color_wheel_pipeline_ release];
  [shaders_ release];
  [queue_ release];
  [device_ release];
}
void macos_render_manager::init_shaders() {
  auto shaders_data = dispatch_data_create(
      s2_ui_macos_shaders, s2_ui_macos_shaders_len, dispatch_get_main_queue(),
      DISPATCH_DATA_DESTRUCTOR_DEFAULT);
  NSError* error;
  shaders_ = [device_ newLibraryWithData:shaders_data error:&error];
  dispatch_release(shaders_data);
}
void macos_render_manager::init_pipelines() {
  auto desc = [[MTLRenderPipelineDescriptor alloc] init];
  desc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;

  NSError* error;
  // triangle pipeline
  {
    auto triangle_vertex = [shaders_ newFunctionWithName:@"triangle_vertex"];
    auto triangle_fragment =
        [shaders_ newFunctionWithName:@"triangle_fragment"];
    desc.vertexFunction = triangle_vertex;
    desc.fragmentFunction = triangle_fragment;

    auto vert_desc = [MTLVertexDescriptor vertexDescriptor];
    vert_desc.layouts[1].stepFunction = MTLVertexStepFunctionPerVertex;
    vert_desc.layouts[1].stride = 20; // float2 + float3
    vert_desc.attributes[0].format = MTLVertexFormatFloat2;
    vert_desc.attributes[0].offset = 0;
    vert_desc.attributes[0].bufferIndex = 1;
    vert_desc.attributes[1].format = MTLVertexFormatFloat3;
    vert_desc.attributes[1].offset = 8;
    vert_desc.attributes[1].bufferIndex = 1;
    desc.vertexDescriptor = vert_desc;

    triangle_pipeline_ = [device_ newRenderPipelineStateWithDescriptor:desc
                                                                 error:&error];

    [triangle_vertex release];
    [triangle_fragment release];
  }

  // color wheel pipeline
  {
    auto color_wheel_vertex =
        [shaders_ newFunctionWithName:@"color_wheel_vertex"];
    auto color_wheel_fragment =
        [shaders_ newFunctionWithName:@"color_wheel_fragment"];
    desc.vertexFunction = color_wheel_vertex;
    desc.fragmentFunction = color_wheel_fragment;

    auto vert_desc = [MTLVertexDescriptor vertexDescriptor];
    vert_desc.layouts[1].stepFunction = MTLVertexStepFunctionPerVertex;
    vert_desc.layouts[1].stride = 8; // float2 + float3
    vert_desc.attributes[0].format = MTLVertexFormatFloat2;
    vert_desc.attributes[0].offset = 0;
    vert_desc.attributes[0].bufferIndex = 1;
    desc.vertexDescriptor = vert_desc;

    desc.colorAttachments[0].blendingEnabled = true;
    desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
    desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;

    color_wheel_pipeline_ =
        [device_ newRenderPipelineStateWithDescriptor:desc error:&error];

    [color_wheel_vertex release];
    [color_wheel_fragment release];
  }

  [desc release];
}
void macos_render_manager::init_pass_desc() {
  pass_desc_ = [[MTLRenderPassDescriptor alloc] init];
  pass_desc_.colorAttachments[0].loadAction = MTLLoadActionClear;
  pass_desc_.colorAttachments[0].storeAction = MTLStoreActionStore;
  pass_desc_.colorAttachments[0].clearColor =
      MTLClearColorMake(0.3, 0.3, 0.3, 1);
  // pass_desc_.colorAttachments[0].clearColor = MTLClearColorMake(0, 1, 1, 1);
}
void macos_render_manager::setup_window(window* w) {
  auto win = static_cast<macos_window*>(w);
  auto layer = win->metal_layer();
  layer.device = device_;
}
void macos_render_manager::render_batch(window* w, draw_batch const& b) {
  auto win = static_cast<macos_window*>(w);
  auto drawable_size = win->drawable_size();

  auto vertex_buffer =
      [device_ newBufferWithBytes:b.vertices.begin()
                           length:b.vertices.size_in_bytes()
                          options:MTLResourceStorageModeShared |
                                  MTLResourceCPUCacheModeWriteCombined];

  @autoreleasepool {
    auto cmdbuf = [queue_ commandBuffer];
    auto drawable = win->drawable();
    pass_desc_.colorAttachments[0].texture = drawable.texture;
    auto encoder = [cmdbuf renderCommandEncoderWithDescriptor:pass_desc_];

    internal::uniform_data uniform = {static_cast<float>(drawable_size.width),
                                      static_cast<float>(drawable_size.height)};

    [encoder setRenderPipelineState:triangle_pipeline_];
    [encoder setVertexBytes:&uniform length:sizeof(uniform) atIndex:0];
    [encoder setVertexBuffer:vertex_buffer offset:0 atIndex:1];

    [encoder drawPrimitives:MTLPrimitiveTypeTriangle
                vertexStart:0
                vertexCount:b.vertices.count()];

    static constexpr struct {
      float pos[2];
    } unit_vertices[] = {
        {0, 0}, {1, 0}, {1, 1}, {0, 0}, {1, 1}, {0, 1},
    };
    static constexpr struct {
      float center[2];
      float radius[2];
    } wheel_data = {
        {0, 0},
        {200, 250},
    };
    // color wheel
    [encoder setRenderPipelineState:color_wheel_pipeline_];
    [encoder setVertexBytes:&unit_vertices
                     length:sizeof(unit_vertices)
                    atIndex:1];
    [encoder setVertexBytes:&wheel_data length:sizeof(wheel_data) atIndex:2];
    [encoder setFragmentBytes:&wheel_data length:sizeof(wheel_data) atIndex:0];
    [encoder drawPrimitives:MTLPrimitiveTypeTriangle
                vertexStart:0
                vertexCount:6];

    [encoder endEncoding];
    [cmdbuf presentDrawable:drawable];
    [cmdbuf commit];
  }

  [vertex_buffer release];
}
} // namespace s2::ui

// [SECTION] Notes
//
// https://developer.apple.com/documentation/metal/choosing-a-resource-storage-mode-for-apple-gpus?language=objc
//
// The storage mode you choose depends on how you plan to use Metal resources:
//
// 1. Populate and update on the CPU
//    Data shared by the CPU and GPU. Use MTLStorageModeShared. The CPU and GPU
//    share data. This is the default for buffer and texture storage.
// 2. Access exclusively on the GPU
//    Data owned by the GPU. Use MTLStorageModePrivate. Choose the mode if you
//    populate your resource with the GPU through a compute, render, or blit
//    pass. This case is common for render targets, intermediary resources, or
//    texture streaming. For guidance on how to copy data to a private resource,
//    see Copying Data to a Private Resource.
// 3. Populate on CPU and access frequently on GPU
//    Shared integrated memory for the CPU and GPU. Use MTLStorageModeShared.
// 4. Temporary texture contents for GPU passes
//    Memory held by the GPU for textures within or between passes. Use
//    MTLStorageModeMemoryless. Memoryless mode only works for textures, and
//    stores temporary resources in tiled memory for high performance. An
//    example is a depth or stencil texture thatʼs used only within a single
//    pass and isnʼt needed in an earlier or later rendering stage.
//
