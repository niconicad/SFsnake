cmake_minimum_required(VERSION 3.16)
project(GAME LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

aux_source_directory(. SRC_LIST)
add_executable(GAME ${SRC_LIST})
target_link_libraries(GAME PRIVATE sfml-graphics sfml-audio)
target_compile_features(GAME PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET GAME
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:GAME>
        VERBATIM)
endif()

install(TARGETS GAME)
