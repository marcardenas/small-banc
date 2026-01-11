set(SOURCES smallbanc-cli.cpp)

add_executable(smallbanc-cli ${SOURCES})

target_link_libraries(smallbanc-cli libsmallbanc)
target_include_directories(smallbanc-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
