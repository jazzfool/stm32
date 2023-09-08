cmake_minimum_required(VERSION 3.16)

# always use ARM GCC compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER_FORCED TRUE)

set(ARM_FLAGS
    -mthumb
    -mcpu=cortex-m7
    --specs=nosys.specs
    --specs=nano.specs
    -nostdlib
    -nostartfiles
    -W
    -Wall
    -Wextra
    -Wundef
    -Wshadow
    -Wdouble-promotion
    -Wformat-truncation
    -fno-common
    -Wconversion
    -g3
    -Os
    -fno-tree-loop-distribute-patterns
    -ffunction-sections
    -fdata-sections
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

project(stm32 C ASM)

# use linker script
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32F756ZG.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# hal2 library
add_library(hal2 INTERFACE)
target_include_directories(hal2 INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/hal2)

# helper function to set up a target
function(add_program PROGRAM_NAME FILES)
  add_executable(${PROGRAM_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/hal2/reset.c
    ${FILES})
  target_link_libraries(${PROGRAM_NAME} PRIVATE
    hal2)
  target_include_directories(
    ${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
  target_compile_options(
    ${PROGRAM_NAME} PRIVATE
    ${ARM_FLAGS})
  target_link_options(
    ${PROGRAM_NAME} PRIVATE
    ${ARM_FLAGS})
  set_target_properties(
    ${PROGRAM_NAME} PROPERTIES
    LINK_DEPENDS ${LINKER_SCRIPT}      # relink if linker script changes
    OUTPUT_NAME  "${PROGRAM_NAME}.elf" # *.elf out
  )
  # objcopy elf into bin blob
  add_custom_command(TARGET ${PROGRAM_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy
    ARGS -O binary ${PROGRAM_NAME}.elf ${PROGRAM_NAME}.bin
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Forming binary blob ${PROGRAM_NAME}.bin"
    )
  # helper command to flash bin to STM32
  add_custom_target(flash-${PROGRAM_NAME}
    COMMAND st-flash --reset write ${PROGRAM_NAME}.bin 0x8000000
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endfunction()

add_program(blink "src/blink.c")
#add_program(button-exti "src/button_exti.c")
