// ----------------------------------------------------------------------------

#pragma once

// ----------------------------------------------------------------------------

#include "smallbanc/io.hpp"
#include "smallbanc/model.hpp"

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

  void add_entry( const model::Entry &entry );
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
  static LedgerWriter create( const std::string &file )
  {
    auto writer = std::make_shared<smallbanc::io::FileWriter>( file );
    return LedgerWriter( writer );
  }

  void initialize() const { m_writer->initialize(); }

  void write( const Ledger& ) const;

private:
  std::shared_ptr<smallbanc::io::IFileWriter> m_writer;
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
