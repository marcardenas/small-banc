#include <smallbanc/io.hpp>
#include <smallbanc/ledger.hpp>

#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace smallbanc
{

namespace ledger
{

void Ledger::insert( const model::Entry &entry )
{
  m_entries.push_back( entry );
}

const std::vector<model::Entry> &Ledger::entries() const { return m_entries; }

double Ledger::balance( unsigned int account_number ) const
{
  double bal = 0.0;
  for ( const auto &entry : m_entries )
  {
    if ( entry.origin == account_number )
    {
      bal -= entry.amount; // Débito reduce balance
    }
    if ( entry.destination == account_number )
    {
      bal += entry.amount; // Crédito aumenta balance
    }
  }
  return bal;
}

std::size_t Ledger::size() const { return m_entries.size(); }

LedgerReader::LedgerReader( std::shared_ptr<smallbanc::io::IFileReader> reader )
    : m_reader( reader )
{
}

LedgerReader LedgerReader::create( const std::string &file )
{
  auto reader = std::make_shared<smallbanc::io::FileReader>( file );
  return LedgerReader( reader );
}

Ledger LedgerReader::read() const
{
  std::string content = m_reader->read();

  std::istringstream stream( content );
  std::string line;

  Ledger ledger;

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
    auto timestamp =
      std::chrono::system_clock::from_time_t( std::mktime( &tm ) );

    // Tipo
    std::getline( line_stream, token, ',' );
    model::TransactionType type = ( token == "DEBIT" )
                                    ? model::TransactionType::Debit
                                    : model::TransactionType::Credit;

    // Cuentas origen
    unsigned int origin_account;
    std::getline( line_stream, token, ',' );
    origin_account = std::stoi( token );

    // Cuentas destino
    unsigned int destination_account;
    std::getline( line_stream, token, ',' );
    destination_account = std::stoi( token );

    // Monto
    std::getline( line_stream, token, ',' );
    double amount = std::stod( token );

    // Descripción
    std::getline( line_stream, token, ',' );
    std::string description = token;

    // Crear Entry
    model::Entry entry;
    entry.type = type;
    entry.origin = origin_account;
    entry.destination = destination_account;
    entry.amount = amount;
    entry.description = description;
    entry.m_timestamp = timestamp;

    ledger.insert( entry );
  }

  return ledger;
}

bool LedgerReader::exists() const
{
  return std::filesystem::exists( m_reader->filename() );
}

void LedgerWriter::write() const
{
  for ( const auto &client : m_dispatch_list )
  {
    auto record = build_ledger_record( client );
    m_writer->write( record );
  }
}

std::string LedgerWriter::build_ledger_record(
  const smallbanc::model::Entry &entry ) const
{
  std::string content;
  auto time_t = std::chrono::system_clock::to_time_t( entry.m_timestamp );
  std::tm tm = *std::localtime( &time_t );
  char buffer[20];
  std::strftime( buffer, sizeof( buffer ), "%Y-%m-%d %H:%M:%S", &tm );

  content += std::string( buffer ) + ",";
  content += entry.type == model::TransactionType::Debit ? "DEBIT," : "CREDIT,";
  content += std::to_string( entry.origin ) + ",";
  content += std::to_string( entry.destination ) + ",";
  content += std::to_string( entry.amount ) + ",";
  content += entry.description + "\n";

  return content;
}

} // namespace ledger

} // namespace smallbanc