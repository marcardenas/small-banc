#include <smallbanc/actions.hpp>
#include <smallbanc/argparse.hpp>
#include <smallbanc/client.hpp>
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

  std::unique_ptr<smallbanc::actions::IAction> action;

  // Ejecutar comando
  if ( args.command == "add-client" )
  {
    auto client = smallbanc::model::Client{
      args.account_number, args.client_name, args.email, true };

    if ( !client.validate() )
    {
      std::cerr << "Error: Missing parameters for add-client\n";
      return 1;
    }

    auto writer = smallbanc::client::ClientWriter::create( "clients.sb" );

    action =
      std::make_unique<smallbanc::actions::AddClientAction>( client, writer );
  }
  else if ( args.command == "add-entry" )
  {
    auto entry = smallbanc::model::Entry{ .amount = args.amount,
      .description = args.description,
      .destination = args.account_to,
      .origin = args.account_from,
      .type = args.type == "debit" ? smallbanc::model::TransactionType::Debit
              : args.type == "credit"
                ? smallbanc::model::TransactionType::Credit
                : smallbanc::model::TransactionType::Unknown };

    if ( !entry.validate() )
    {
      std::cerr << "Error: Missing parameters for add-entry\n";
      return 1;
    }
    auto writer = smallbanc::ledger::LedgerWriter::create( "ledger.sb" );
    action =
      std::make_unique<smallbanc::actions::AddEntryAction>( entry, writer );
  }
  /*
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
  */
  else
  {
    std::cerr << "Unknown command: " << args.command << "\n";
    parser.print_help();
    return 1;
  }

  action->execute();

  return 0;
};