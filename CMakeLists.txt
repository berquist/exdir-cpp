cmake_minimum_required(VERSION 3.10)
project(exdir-cpp VERSION 0.0.2 LANGUAGES CXX)

include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(EXDIR_CPP_SOURCE_FILES ${EXDIR_CPP_SOURCE_FILES}
  src/object.cpp
  src/group.cpp
  src/raw.cpp
  src/file.cpp
  src/ndarray.cpp
  src/npy.cpp
  src/dataset.cpp
)

# Add shared library target. Must be shared due to dependence on yaml-cpp.
# I am not completely sure why though.
add_library(exdir-cpp ${EXDIR_CPP_SOURCE_FILES})

# Find and link with yaml-cpp
find_package (yaml-cpp REQUIRED)
target_link_libraries(exdir-cpp PUBLIC yaml-cpp Boost::filesystem)

target_include_directories(exdir-cpp
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  
)

target_compile_options(exdir-cpp
  PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wshadow -Weffc++ -Wno-long-long>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-pedantic -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /wd4127 /wd4355>
)

set_target_properties(exdir-cpp PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
  PROJECT_LABEL "exdir-cpp"
)

install(TARGETS exdir-cpp
    EXPORT exdir-cpp-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		FILES_MATCHING PATTERN "*.hpp"
)

add_subdirectory(example)
