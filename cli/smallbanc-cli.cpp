#include "smallbanc/client.hpp"
#include <smallbanc/actions.hpp>
#include <smallbanc/argparse.hpp>
#include <smallbanc/ledger.hpp>
#include <smallbanc/model.hpp>

#include <iostream>

using namespace smallbanc::model;

int main( int argc, char *argv[] )
{
  smallbanc::argparse::Args args;

  smallbanc::argparse::Parser parser( std::ref( args ) );

  parser.set_args( argc, argv );
  parser.parse();

  if ( !args.help_command.empty() )
  {
    parser.print_help( args.help_command );
    return 0;
  }

  if ( args.command.empty() )
  {
    parser.print_help();
    return 0;
  }

  auto lr = smallbanc::ledger::LedgerReader::create( args.ledger_location );
  auto lw = smallbanc::ledger::LedgerWriter::create( args.ledger_location );

  if ( !lr.exists() )
  {
    lw.initialize();
  }

  auto ledger = lr.read();
  std::unique_ptr<IAction> action;

  // Ejecutar comando
  if ( args.command == "add-client" )
  {
    if ( args.client_name.empty() || args.account_number == 0 )
    {
      std::cerr << "Error: Missing parameters for add-client\n";
      return 1;
    }

    auto client = smallbanc::model::Client{
      args.account_number, args.client_name, "", true };
    auto writer = std::make_shared<smallbanc::client::ClientWriter>( "clients.sb" );

    action = std::make_unique<AddClientAction>( client, writer );
  }
  /*
  else if ( args.command == "add-entry" )
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
    parser.print_help();
    return 1;
  }
  */
  action->execute();

  return 0;
};