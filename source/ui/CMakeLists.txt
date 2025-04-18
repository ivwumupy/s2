s2_add_library(
  NAME ui
  PRIVATE
    platform.cc
    platform_macos.mm
    scene.cc
  DEPS
    base
)
target_link_libraries(ui
  PRIVATE
    ${FRAMEWORK_APP_KIT}
)
