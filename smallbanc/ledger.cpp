#include <smallbanc/io.hpp>
#include <smallbanc/ledger.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace smallbanc
{

namespace ledger
{

void Ledger::add_entry( const Entry &entry ) { m_entries.push_back( entry ); }

const std::vector<Entry> &Ledger::entries() const { return m_entries; }

double Ledger::balance( unsigned int account_number ) const
{
  double bal = 0.0;
  for ( const auto &entry : m_entries )
  {
    if ( entry.get_origin().account_number == account_number )
    {
      bal -= entry.get_amount();  // Débito reduce balance
    }
    if ( entry.get_destination().account_number == account_number )
    {
      bal += entry.get_amount();  // Crédito aumenta balance
    }
  }
  return bal;
}

std::size_t Ledger::size() const { return m_entries.size(); }

LedgerReader::LedgerReader(
  std::shared_ptr<smallbanc::io::IFileReader> reader )
    : m_reader( reader )
{
}

std::vector<Entry> LedgerReader::read() const
{
  std::vector<Entry> entries;
  std::string content = m_reader->read();

  std::istringstream stream( content );
  std::string line;
  while ( std::getline( stream, line ) )
  {
    if ( line.empty() || line[0] == '#' )
      continue;

    std::istringstream line_stream( line );
    std::string token;

    // Fecha
    std::getline( line_stream, token, ',' );
    std::tm tm = {};
    std::istringstream ss( token );
    ss >> std::get_time( &tm, "%Y-%m-%d %H:%M:%S" );
    auto timestamp = std::chrono::system_clock::from_time_t( std::mktime( &tm ) );

    // Tipo
    std::getline( line_stream, token, ',' );
    TransactionType type =
      ( token == "DEBIT" ) ? TransactionType::Debit : TransactionType::Credit;

    // Cuentas origen
    Account origin;
    std::getline( line_stream, token, ',' );
    origin.account_number = std::stoi( token );

    // Cuentas destino
    Account destination;
    std::getline( line_stream, token, ',' );
    destination.account_number = std::stoi( token );

    // Monto
    std::getline( line_stream, token, ',' );
    double amount = std::stod( token );

    // Descripción
    std::getline( line_stream, token, ',' );
    std::string description = token;

    // Crear Entry con constructor
    Entry entry( type, origin, destination, amount, description, timestamp );
    entries.push_back( entry );
  }

  return entries;
}

} // namespace ledger

} // namespace smallbanc