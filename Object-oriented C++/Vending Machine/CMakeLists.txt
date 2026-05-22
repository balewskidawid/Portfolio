cmake_minimum_required(VERSION 3.20)
project(vending_machine_ftxui CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(vending_machine ${SRC_FILES})
target_include_directories(vending_machine PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(vending_machine PRIVATE ftxui::screen ftxui::dom ftxui::component)

if (MSVC)
  target_compile_options(vending_machine PRIVATE /W4 /permissive-)
  target_compile_options(vending_machine PRIVATE /utf-8)
else()
  target_compile_options(vending_machine PRIVATE -Wall -Wextra -Wpedantic)
endif()

