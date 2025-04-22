#include "s2/ui/macos_render_manager.h"

//
#include "s2/ui/macos_shaders.h"

namespace s2::ui {
macos_render_manager::macos_render_manager() {
  device_ = MTLCreateSystemDefaultDevice();
  init_shaders();
  init_pipelines();
}
macos_render_manager::~macos_render_manager() {
  [shaders_ release];
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
  // triangle pipeline
  auto triangle_vertex = [shaders_ newFunctionWithName:@"triangle_vertex"];
  auto triangle_fragment = [shaders_ newFunctionWithName:@"triangle_fragment"];
  desc.vertexDescriptor = [MTLVertexDescriptor vertexDescriptor];
  [desc release];
}
} // namespace s2::ui
