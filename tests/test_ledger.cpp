#include <gtest/gtest.h>

#include <smallbanc/ledger.h>

TEST( LedgerTest, CreateLedger )
{
  smallbanc::ledger::Ledger ledger =
      smallbanc::ledger::Ledger::create( "test_ledger.dat" );
  ASSERT_TRUE( true ); // Placeholder assertion
}