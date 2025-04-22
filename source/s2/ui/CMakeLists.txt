s2_add_library(
  NAME ui
  PRIVATE
    application.cc
  PRIVATE_MACOS
    macos_application.mm
    macos_window.mm
  DEPS
    base
)
if(S2_IS_MACOS)
  target_link_libraries(ui
    PRIVATE
      ${FRAMEWORK_APP_KIT}
  )
endif()
