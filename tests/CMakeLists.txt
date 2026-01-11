find_package(GTest REQUIRED)

add_executable(test_ledger test_ledger.cpp)

target_link_libraries(test_ledger PRIVATE GTest::GTest GTest::Main libsmallbanc)

gtest_discover_tests(test_ledger)