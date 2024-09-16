set(COMPONENT_SRCDIRS
    "ESP32S2_Aperoliker_V1.2"
)

set(COMPONENT_ADD_INCLUDEDIRS
    "ESP32S2_Aperoliker_V1.2"
)

set(COMPONENT_REQUIRES
    "arduino-esp32"
    "AsyncTCP"
)

register_component()

target_compile_definitions(${COMPONENT_TARGET} PUBLIC -DESP32)
target_compile_options(${COMPONENT_TARGET} PRIVATE -fno-rtti)
