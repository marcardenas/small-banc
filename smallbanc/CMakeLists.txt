set(SOURCES argparse.cpp io.cpp ledger.cpp model.cpp queue.cpp argparse.cpp)

add_library(smallbanc ${SOURCES})
target_include_directories(smallbanc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
