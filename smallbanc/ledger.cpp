#include <smallbanc/io.h>
#include <smallbanc/ledger.h>

#include <iostream>

namespace smallbanc
{

namespace ledger
{

Ledger::Ledger( const std::string &file ) : m_file( file ) {}

void Ledger::fetch() {}

void Ledger::create( std::shared_ptr<smallbanc::io::IFileCreator> file_creator )
{
  file_creator->set( m_file );

  if ( !file_creator->exists() )
  {
    file_creator->create();
    m_exists = true;
  }
  else
  {
    throw std::runtime_error( "Ledger file already exists" );
  }
}

bool Ledger::exists() const { return m_exists; }

void Ledger::store() {}

} // namespace ledger

} // namespace smallbanc