// ----------------------------------------------------------------------------

#include "smallbanc/client.hpp"
#include "smallbanc/io.hpp"
#include "smallbanc/model.hpp"

// ----------------------------------------------------------------------------

namespace smallbanc
{

// ----------------------------------------------------------------------------

namespace client
{

// ----------------------------------------------------------------------------

std::vector<smallbanc::model::Client> ClientReader::read() const
{
  // Implementación de lectura de clientes desde el archivo
  // Por simplicidad, retornamos un vector vacío aquí
  return {};
}

// ----------------------------------------------------------------------------

ClientWriter::~ClientWriter()
{

}

// ----------------------------------------------------------------------------

void ClientWriter::insert( const smallbanc::model::Client &client )
{
  m_dispatch_list.push_back( client );
}

// ----------------------------------------------------------------------------

void ClientWriter::remove( unsigned int client_id )
{
  m_dispatch_list.erase(
    std::remove_if( m_dispatch_list.begin(), m_dispatch_list.end(),
      [client_id]( const smallbanc::model::Client &c )
      { return c.id == client_id; } ),
    m_dispatch_list.end() );
}

// ----------------------------------------------------------------------------

void ClientWriter::initialize() const { m_writer->initialize(); }

// ----------------------------------------------------------------------------

void ClientWriter::write() const
{
  for ( const auto &client : m_dispatch_list )
  {
    auto record = build_client_record( client );
    m_writer->write( record );
  }
}

// ----------------------------------------------------------------------------

std::string ClientWriter::build_client_record(
  const smallbanc::model::Client &client ) const
{
  // Construir una línea CSV para el cliente
  return std::to_string( client.id ) + "," + client.name + "," + client.email +
         "," + ( client.is_active ? "1" : "0" ) + "\n";
}
// ----------------------------------------------------------------------------

} // namespace client

// ----------------------------------------------------------------------------

} // namespace smallbanc

// ----------------------------------------------------------------------------
