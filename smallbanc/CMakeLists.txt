set(SOURCES actions.cpp argparse.cpp client.cpp io.cpp ledger.cpp model.cpp queue.cpp argparse.cpp)

add_library(smallbanc ${SOURCES})
target_include_directories(smallbanc PUBLIC ${CMAKE_SOURCE_DIR})
