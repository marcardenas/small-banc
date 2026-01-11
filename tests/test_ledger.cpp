#include <gtest/gtest.h>

#include <smallbanc/io.h>
#include <smallbanc/ledger.h>

class FileCreatorMock : public smallbanc::io::IFileCreator
{
public:
  FileCreatorMock() : smallbanc::io::IFileCreator() {}

  void create() override
  {
    if( m_loaded_file == m_file )
    {
      throw std::runtime_error( "File already created" );
    }
    
    FileCreatorMock::m_loaded_file = m_file;

    m_exists = true;
  }

  bool exists() const override { return m_exists; }

private:
  bool m_exists = false;

  static inline std::string m_loaded_file;
};

class FailedFileCreatorMock : public smallbanc::io::IFileCreator
{
public:
  FailedFileCreatorMock() : smallbanc::io::IFileCreator() {}
  void create() override { throw std::runtime_error( "File creation failed" ); }
  bool exists() const override { return false; }
};

TEST( LedgerTest, CreateLedger )
{
  smallbanc::ledger::Ledger ledger( "test_ledger.dat" );

  ASSERT_TRUE( true ); // Placeholder assertion
}

TEST( LedgerTest, LedgerExists )
{
  smallbanc::ledger::Ledger ledger( "ledger_that_doesnt_exists.dat" );

  ASSERT_FALSE( ledger.exists() );

  ledger.create( std::make_shared<FileCreatorMock>() );

  ASSERT_TRUE( ledger.exists() );
}

TEST( LedgerTest, LedgerFileCreationFails )
{
  smallbanc::ledger::Ledger ledger( "failed_creation.dat" );

  ASSERT_FALSE( ledger.exists() );
  ASSERT_THROW( ledger.create( std::make_shared<FailedFileCreatorMock>() ),
                std::runtime_error );
  ASSERT_FALSE( ledger.exists() );
}

TEST( LedgerTest, LedgerFileAlreadyExists )
{
  smallbanc::ledger::Ledger ledger( "existing_ledger.dat" );
  auto creator = std::make_shared<FileCreatorMock>();

  ASSERT_FALSE( ledger.exists() );
  ASSERT_NO_THROW( ledger.create( creator ) );
  ASSERT_TRUE( ledger.exists() );
  ASSERT_THROW( ledger.create( creator ), std::runtime_error );
}

TEST( LedgerTest, TwoCreatorsBehavesEqual )
{
  smallbanc::ledger::Ledger ledger( "existing_ledger.dat" );

  ASSERT_FALSE( ledger.exists() );
  ASSERT_NO_THROW( ledger.create( std::make_shared<FileCreatorMock>() ) );
  ASSERT_TRUE( ledger.exists() );
  ASSERT_THROW( ledger.create( std::make_shared<FileCreatorMock>() ),
                std::runtime_error );
}