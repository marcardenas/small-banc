#include <gtest/gtest.h>

#include <smallbanc/io.hpp>
#include <smallbanc/ledger.hpp>

// Helper para crear cuentas de prueba
Account create_test_account( unsigned int account_number )
{
  Account acc;
  acc.account_number = account_number;
  acc.account_type = "Checking";
  acc.balance = 0.0;
  acc.owner.id = account_number;
  acc.owner.name = "Test User " + std::to_string( account_number );
  acc.owner.email = "test" + std::to_string( account_number ) + "@test.com";
  acc.owner.is_active = true;
  return acc;
}

// Helper para crear Entry de prueba
Entry create_test_entry( TransactionType type, unsigned int origin_num,
  unsigned int dest_num, double amount, const std::string &description )
{
  return Entry( type, create_test_account( origin_num ),
    create_test_account( dest_num ), amount, description,
    std::chrono::system_clock::now() );
}

class FileReaderMock : public smallbanc::io::IFileReader
{
public:
  FileReaderMock( const std::string &content )
      : smallbanc::io::IFileReader(), m_content( content )
  {
  }
  std::string read() const override { return m_content; }

private:
  std::string m_content;
};

// Tests básicos de Ledger
TEST( LedgerTest, CreateLedger )
{
  smallbanc::ledger::Ledger ledger;
  ASSERT_EQ( ledger.size(), 0 );
}

TEST( LedgerTest, AddEntry )
{
  smallbanc::ledger::Ledger ledger;
  Entry entry =
    create_test_entry( TransactionType::Debit, 1, 2, 100.0, "Test Payment" );

  ledger.add_entry( entry );

  ASSERT_EQ( ledger.size(), 1 );
  ASSERT_EQ( ledger.entries().size(), 1 );
}

TEST( LedgerTest, Size )
{
  smallbanc::ledger::Ledger ledger;

  ASSERT_EQ( ledger.size(), 0 );

  Entry entry =
    create_test_entry( TransactionType::Debit, 1, 2, 100.0, "Test1" );
  ledger.add_entry( entry );

  ASSERT_EQ( ledger.size(), 1 );

  Entry entry2 =
    create_test_entry( TransactionType::Credit, 2, 1, 50.0, "Test2" );
  ledger.add_entry( entry2 );

  ASSERT_EQ( ledger.size(), 2 );
}

TEST( LedgerTest, BalanceCalculation )
{
  smallbanc::ledger::Ledger ledger;

  // Agregar débito: cuenta 1 pierde 50
  Entry debit =
    create_test_entry( TransactionType::Debit, 1, 2, 50.0, "Debit" );
  ledger.add_entry( debit );

  // Agregar crédito: cuenta 1 recibe 30
  Entry credit =
    create_test_entry( TransactionType::Credit, 2, 1, 30.0, "Credit" );
  ledger.add_entry( credit );

  // Balance para cuenta 1: -50 + 30 = -20
  ASSERT_DOUBLE_EQ( ledger.balance( 1 ), -20.0 );
}

TEST( LedgerTest, BalanceZeroWhenNoEntries )
{
  smallbanc::ledger::Ledger ledger;
  ASSERT_DOUBLE_EQ( ledger.balance( 999 ), 0.0 );
}

TEST( LedgerTest, BalanceMultipleTransactions )
{
  smallbanc::ledger::Ledger ledger;

  // Cuenta 1: -100, +50, -25 = -75
  Entry e1 = create_test_entry( TransactionType::Debit, 1, 2, 100.0, "Out1" );
  Entry e2 = create_test_entry( TransactionType::Credit, 2, 1, 50.0, "In1" );
  Entry e3 = create_test_entry( TransactionType::Debit, 1, 3, 25.0, "Out2" );

  ledger.add_entry( e1 );
  ledger.add_entry( e2 );
  ledger.add_entry( e3 );

  ASSERT_DOUBLE_EQ( ledger.balance( 1 ), -75.0 );
  ASSERT_DOUBLE_EQ( ledger.balance( 2 ), 50.0 );
  ASSERT_DOUBLE_EQ( ledger.balance( 3 ), 25.0 );
}

TEST( LedgerTest, BalanceWithSameAccountOriginDestination )
{
  smallbanc::ledger::Ledger ledger;

  // Transacción interna (débito y crédito en misma cuenta se anulan)
  Entry internal =
    create_test_entry( TransactionType::Debit, 1, 1, 50.0, "Internal" );
  ledger.add_entry( internal );

  ASSERT_DOUBLE_EQ( ledger.balance( 1 ), 0.0 );
}

TEST( LedgerTest, AddMultipleEntriesAndVerifySize )
{
  smallbanc::ledger::Ledger ledger;

  for ( int i = 0; i < 10; ++i )
  {
    Entry entry = create_test_entry( TransactionType::Debit, i, i + 1, 10.0 * i,
      "Entry " + std::to_string( i ) );
    ledger.add_entry( entry );
  }

  ASSERT_EQ( ledger.size(), 10 );
  ASSERT_EQ( ledger.entries().size(), 10 );
}

// Tests para LedgerReader
TEST( LedgerReaderTest, ReadEmptyFile )
{
  auto reader = std::make_shared<FileReaderMock>( "" );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_TRUE( entries.empty() );
}

TEST( LedgerReaderTest, ReadIgnoresComments )
{
  std::string csv = "# Este es un comentario\n"
                    "2023-10-15 14:30:00,DEBIT,1,2,100.00,Test,txn-001\n"
                    "# Otro comentario\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 1 );
}

TEST( LedgerReaderTest, ReadIgnoresEmptyLines )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Test,txn-001\n"
                    "\n"
                    "2023-10-16 15:00:00,CREDIT,2,1,50.00,Test2,txn-002\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 2 );
}

TEST( LedgerReaderTest, ReadValidSingleEntry )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Pago,txn-001\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 1 );
}

TEST( LedgerReaderTest, ReadValidMultipleEntries )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Pago1,txn-001\n"
                    "2023-10-16 10:00:00,CREDIT,2,1,50.00,Pago2,txn-002\n"
                    "2023-10-17 16:45:00,DEBIT,3,4,75.50,Pago3,txn-003\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 3 );
}

TEST( LedgerReaderTest, ReadDebitVsCredit )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Test,txn-001\n"
                    "2023-10-16 15:00:00,CREDIT,2,1,50.00,Test2,txn-002\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 2 );
}

TEST( LedgerReaderTest, ReadWithDecimalAmounts )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,1234.56,Test,txn-001\n"
                    "2023-10-16 15:00:00,CREDIT,2,1,0.99,Test2,txn-002\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 2 );
}

TEST( LedgerReaderTest, ReadWithDescriptionSpaces )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Descripción "
                    "con espacios,txn-001\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  ASSERT_EQ( entries.size(), 1 );
}

// Tests de integración: Ledger + LedgerReader
TEST( LedgerIntegrationTest, ReadAndAddToLedger )
{
  std::string csv = "2023-10-15 14:30:00,DEBIT,1,2,100.00,Test1,txn-001\n"
                    "2023-10-16 15:00:00,CREDIT,2,1,50.00,Test2,txn-002\n";
  auto reader = std::make_shared<FileReaderMock>( csv );
  smallbanc::ledger::LedgerReader lr( reader );

  auto entries = lr.read();

  smallbanc::ledger::Ledger ledger;
  for ( const auto &entry : entries )
  {
    ledger.add_entry( entry );
  }

  ASSERT_EQ( ledger.size(), 2 );
}

TEST( LedgerTest, EntriesVectorImmutable )
{
  smallbanc::ledger::Ledger ledger;
  Entry entry =
    create_test_entry( TransactionType::Debit, 1, 2, 100.0, "Test" );
  ledger.add_entry( entry );

  const auto &entries = ledger.entries();
  ASSERT_EQ( entries.size(), 1 );
}
