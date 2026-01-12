set(SOURCES argparse.cpp io.cpp ledger.cpp model.cpp queue.cpp argparse.cpp)

add_library(libsmallbanc ${SOURCES})
target_include_directories(libsmallbanc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
