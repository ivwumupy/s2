s2_add_library(
  NAME ui
  PRIVATE
    application.cc
    draw_batch.cc
  PRIVATE_MACOS
    macos_application.mm
    macos_render_manager.mm
    macos_text_manager.mm
    macos_window.mm
  DEPS
    base
)
if(S2_IS_MACOS)
  target_link_libraries(ui
    PRIVATE
      ${FRAMEWORK_APP_KIT}
      ${FRAMEWORK_METAL}
  )
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/shaders.ir
    COMMAND
      xcrun metal -o ${CMAKE_CURRENT_BINARY_DIR}/shaders.ir -c ${CMAKE_CURRENT_SOURCE_DIR}/shaders.metal
    DEPENDS
      shaders.metal
  )
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/shaders.metallib
    COMMAND
      xcrun metallib -o ${CMAKE_CURRENT_BINARY_DIR}/shaders.metallib ${CMAKE_CURRENT_BINARY_DIR}/shaders.ir
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/shaders.ir
  )
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/macos_shaders.h
    COMMAND
      xxd -i -n s2_ui_macos_shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders.metallib ${CMAKE_CURRENT_BINARY_DIR}/macos_shaders.h
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/shaders.metallib
  )
  add_custom_target(macos_shaders
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/macos_shaders.h
  )
  add_dependencies(ui macos_shaders)
endif()
