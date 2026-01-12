set(SOURCES smallbanc-cli.cpp)
set(OBJC_SOURCES smallbanc-objc-cli.mm)

add_executable(smallbanc-cli ${SOURCES})
add_executable(smallbanc-cli-mac ${OBJC_SOURCES})

find_library(FOUNDATION_LIBRARY Foundation REQUIRED)

target_link_libraries(smallbanc-cli smallbanc)
target_link_libraries(smallbanc-cli-mac PRIVATE smallbanc ${FOUNDATION_LIBRARY})

target_include_directories(smallbanc-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

set_target_properties(smallbanc-cli-mac PROPERTIES COMPILE_FLAGS "-ObjC++")