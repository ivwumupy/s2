s2_add_library(
  NAME ui
  PRIVATE
    application.cc
  PRIVATE_MACOS
    application_macos.mm
    window_macos.mm
  DEPS
    base
)
if(S2_IS_MACOS)
  target_link_libraries(ui
    PRIVATE
      ${FRAMEWORK_APP_KIT}
  )
endif()
