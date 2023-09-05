cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/stm32-cmake/cmake/stm32_gcc.cmake
)

project(stm32 C ASM)

stm32_fetch_cube(F7)
set(STM32XX STM32F7)

find_package(CMSIS COMPONENTS
  ${STM32XX}
  REQUIRED
)
find_package(HAL COMPONENTS
  ${STM32XX}
  RCC
  GPIO
  CORTEX
  REQUIRED
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
link_libraries(
  HAL::STM32::F7::RCC
  HAL::STM32::F7::GPIO
  HAL::STM32::F7::CORTEX
  CMSIS::STM32::F756ZG
  STM32::NoSys
)

add_executable(stm32-blink src/blink.c)
stm32_print_size_of_target(stm32-blink)

add_executable(stm32-button-exti src/button_exti.c)
stm32_print_size_of_target(stm32-button-exti)
