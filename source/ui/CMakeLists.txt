s2_add_library(
  NAME ui
  PRIVATE
    platform.c
    platform_macos.m
  DEPS
    base
)
target_link_libraries(ui
  PRIVATE
    ${FRAMEWORK_APP_KIT}
)
