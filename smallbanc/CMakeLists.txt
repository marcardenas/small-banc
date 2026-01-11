set(SOURCES argparse.cpp ledger.cpp model.cpp queue.cpp argparse.h)
set(HEADERS argparse.h ledger.h model.h)

add_library(libsmallbanc ${SOURCES} ${HEADERS})
target_include_directories(libsmallbanc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
