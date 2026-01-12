#pragma once

#include "smallbanc/io.hpp"
#include "smallbanc/model.hpp"

#include <memory>
#include <string>
#include <vector>

namespace smallbanc
{
namespace ledger
{

class Ledger
{
public:
  Ledger() = default;

  void add_entry( const Entry &entry );
  const std::vector<Entry> &entries() const;

  double balance( unsigned int account_number ) const;
  std::size_t size() const;

private:
  std::vector<Entry> m_entries;
  std::string m_file;
};

class LedgerReader
{
public:
  LedgerReader( std::shared_ptr<smallbanc::io::IFileReader> reader );

  std::vector<Entry> read() const;

private:
  std::shared_ptr<smallbanc::io::IFileReader> m_reader;
};

} // namespace ledger
} // namespace smallbanc
