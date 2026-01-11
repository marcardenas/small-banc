#include <smallbanc/ledger.h>

namespace smallbanc
{
namespace ledger

{

Ledger Ledger::create( const std::string &filename )
{
  Ledger ledger;
  // Implementation for creating a new ledger file goes here
  return ledger;
}

Ledger Ledger::from_file( const std::string filename )
{
  Ledger ledger;
  // Implementation for loading a ledger from an existing file goes here
  return ledger;
}

} // namespace ledger

} // namespace smallbanc