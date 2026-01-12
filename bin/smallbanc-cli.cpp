#include <smallbanc/argparse.hpp>
#include <smallbanc/ledger.hpp>

#include <iostream>

void print_help()
{
  std::cout << "Usage: smallbanc-cli [command] [options]\n"
            << "Commands:\n"
            << "  add-entry             Add a new entry to the ledger\n"
            << "  get-balance           Get balance for an account\n"
            << "  list-entries          List all entries\n"
            << "Options:\n"
            << "  --help                Show this help message\n"
            << "  --config <file>       Specify configuration file\n"
            << "  --ledger <location>   Specify ledger location\n"
            << "  --account-from <id>   Source account for add-entry\n"
            << "  --account-to <id>     Destination account for add-entry\n"
            << "  --amount <value>      Amount for add-entry\n"
            << "  --description <text>  Description for add-entry\n"
            << "  --type <debit|credit> Type for add-entry\n"
            << "  --account <id>        Account for get-balance\n";
}

int main( int argc, char *argv[] )
{
  smallbanc::argparse::Args args;

  {
    smallbanc::argparse::Parser parser( std::ref( args ) );

    parser.set_args( argc, argv );
    parser.parse();
  }

  if ( args.help || args.command.empty() )
  {
    print_help();
    return 0;
  }

  auto lr = smallbanc::ledger::LedgerReader::create( args.ledger_location );
  auto lw = smallbanc::ledger::LedgerWriter::create( args.ledger_location );

  if ( !lr.exists() )
  {
    lw.initialize();
  }

  auto ledger = lr.read();

  // Ejecutar comando
  if ( args.command == "add-entry" )
  {
    if ( args.account_from == 0 || args.account_to == 0 || args.amount == 0.0 ||
         args.description.empty() || args.type.empty() )
    {
      std::cerr << "Error: Missing parameters for add-entry\n";
      return 1;
    }

    // Crear cuentas dummy (en producción, cargar de DB)
    Account origin;
    origin.account_number = args.account_from;
    Account destination;
    destination.account_number = args.account_to;

    TransactionType type = ( args.type == "debit" ) ? TransactionType::Debit
                                                    : TransactionType::Credit;
    Entry entry( type, origin, destination, args.amount, args.description,
      std::chrono::system_clock::now() );

    ledger.add_entry( entry );
    lw.write( ledger ); // Guardar cambios

    std::cout << "Entry added successfully\n";
  }
  else if ( args.command == "get-balance" )
  {
    if ( args.account_number == 0 )
    {
      std::cerr << "Error: Missing account number for get-balance\n";
      return 1;
    }

    double balance = ledger.balance( args.account_number );
    std::cout << "Balance for account " << args.account_number << ": "
              << balance << "\n";
  }
  else if ( args.command == "list-entries" )
  {
    const auto &entries = ledger.entries();
    for ( const auto &entry : entries )
    {
      std::cout << "Type: "
                << ( entry.get_type() == TransactionType::Debit ? "Debit"
                                                                : "Credit" )
                << ", From: " << entry.get_origin().account_number
                << ", To: " << entry.get_destination().account_number
                << ", Amount: " << entry.get_amount()
                << ", Description: " << entry.get_description() << "\n";
    }
  }
  else
  {
    std::cerr << "Unknown command: " << args.command << "\n";
    print_help();
    return 1;
  }

  return 0;
};