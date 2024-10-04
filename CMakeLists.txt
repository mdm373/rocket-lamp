# project constants
if (NOT DEFINED WS2812_PIN)
  set(WS2812_PIN "22")
endif()
if (NOT DEFINED IS_RGBW)
  set(IS_RGBW "false")
endif()
if (NOT DEFINED BUTTON_PIN)
  set(BUTTON_PIN "17")
endif()
if (NOT DEFINED ADC_PIN)
  set(ADC_PIN "26")
endif()
if (NOT DEFINED NUM_PIXELS)
  set(NUM_PIXELS "51")
endif()
if (NOT DEFINED FRAME_MS)
  set(FRAME_MS "33")
endif()
if (NOT DEFINED FEEDBACK_DELAY)
  set(FEEDBACK_DELAY "1000")
endif()
if (NOT DEFINED END_FIRE_PIXEL)
  set(END_FIRE_PIXEL "11")
endif()
if (NOT DEFINED END_ROCKET_PIXEL)
  set(END_ROCKET_PIXEL "31")
endif()

cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(rocket_lamp)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(rocket_lamp)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/.generated)
# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(rocket_lamp ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/.generated)

target_sources(rocket_lamp PRIVATE ${SRC_HEADERS})
target_sources(rocket_lamp PRIVATE ${SRC_FILES})
target_sources(rocket_lamp
  PRIVATE
  src/view.h
  src/view_mix.c
  src/view_rainbow.c
  src/view_white.c
  src/view_rocket.c
  src/poll_button.h
  src/poll_button.c
  src/rgb_color.h
  src/rgb_color.c
  src/read_adc.h
  src/read_adc.c
  src/main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(rocket_lamp PRIVATE pico_stdlib hardware_pio hardware_adc)
pico_add_extra_outputs(rocket_lamp)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(rocket_lamp)

# Additionally generate python and hex pioasm outputs for inclusion in the RP2040 datasheet
add_custom_target(pio_ws2812_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/.generated/ws2812.py)
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/.generated/ws2812.py
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio
        COMMAND Pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/src/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/.generated/ws2812.py
        VERBATIM)
add_dependencies(rocket_lamp pio_ws2812_datasheet)
add_definitions(
  -DBUTTON_PIN=${BUTTON_PIN}
  -DWS2812_PIN=${WS2812_PIN}
  -DIS_RGBW=${IS_RGBW}
  -DADC_PIN=${ADC_PIN}
  -DNUM_PIXELS=${NUM_PIXELS} 
  -DFRAME_MS=${FRAME_MS}
  -DFEEDBACK_DELAY=${FEEDBACK_DELAY}
  -DEND_FIRE_PIXEL=${END_FIRE_PIXEL}
  -DEND_ROCKET_PIXEL=${END_ROCKET_PIXEL}
  )
