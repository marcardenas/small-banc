// ----------------------------------------------------------------------------

#pragma once

// ----------------------------------------------------------------------------

#include "smallbanc/io.hpp"
#include "smallbanc/model.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

// ----------------------------------------------------------------------------

namespace smallbanc
{

// ----------------------------------------------------------------------------

namespace ledger
{

// ----------------------------------------------------------------------------

class Ledger
{
public:
  Ledger() = default;

  void insert( const model::Entry &entry );
  const std::vector<model::Entry> &entries() const;

  double balance( unsigned int account_number ) const;
  std::size_t size() const;

private:
  std::vector<model::Entry> m_entries;
  std::string m_file;
};

// ----------------------------------------------------------------------------

class LedgerWriter
{
public:
  LedgerWriter( std::shared_ptr<smallbanc::io::IFileWriter> writer )
      : m_writer( writer )
  {
  }
  static std::shared_ptr<LedgerWriter> create( const std::string &file )
  {
    auto writer = std::make_shared<smallbanc::io::FileWriter>( file );
    return std::make_shared<LedgerWriter>( writer );
  }

  void initialize() const { m_writer->initialize(); }

  void write( const Ledger& ) const;

  bool exists()
  {
    return std::filesystem::exists( m_writer->filename() );
  }

  void insert( smallbanc::model::Entry &entry )
  {
    m_dispatch_list.push_back( entry );
  }

  void write() const;

private:
  std::string build_ledger_record( const smallbanc::model::Entry& entry ) const;

  std::shared_ptr<smallbanc::io::IFileWriter> m_writer;
  std::vector<smallbanc::model::Entry> m_dispatch_list;
};

// ----------------------------------------------------------------------------

class LedgerReader
{
public:
  LedgerReader( std::shared_ptr<smallbanc::io::IFileReader> reader );

  static LedgerReader create( const std::string &file );

  Ledger read() const;

  bool exists() const;

private:
  std::shared_ptr<smallbanc::io::IFileReader> m_reader;
};
// ----------------------------------------------------------------------------

} // namespace ledger

// ----------------------------------------------------------------------------

} // namespace smallbanc

// ----------------------------------------------------------------------------
