#include <functional>
#include <smallbanc/argparse.hpp>
#include <string>
#include <iostream>

namespace smallbanc::argparse
{

Parser::Parser( std::reference_wrapper<Args> args ) : args_( args ) {}

void Parser::parse()
{
  for ( int i = 1; i < argc_; ++i )
  {
    auto argument = std::string( argv_[i] );

    if ( argument == "--help" )
    {
      if ( i + 1 < argc_ && argv_[i + 1][0] != '-' )
      {
        args_.get().help_command = std::string( argv_[++i] );
      }
      else
      {
        args_.get().help_command = "general";
      }
    }
    else if ( argument == "--config" && i + 1 < argc_ )
    {
      args_.get().config_file = std::string( argv_[++i] );
    }
    else if ( argument == "--ledger" && i + 1 < argc_ )
    {
      args_.get().ledger_location = std::string( argv_[++i] );
    }
    else if ( argument == "--account-from" && i + 1 < argc_ )
    {
      args_.get().account_from = std::stoul( argv_[++i] );
    }
    else if ( argument == "--account-to" && i + 1 < argc_ )
    {
      args_.get().account_to = std::stoul( argv_[++i] );
    }
    else if ( argument == "--amount" && i + 1 < argc_ )
    {
      args_.get().amount = std::stod( argv_[++i] );
    }
    else if ( argument == "--description" && i + 1 < argc_ )
    {
      args_.get().description = std::string( argv_[++i] );
    }
    else if ( argument == "--type" && i + 1 < argc_ )
    {
      args_.get().type = std::string( argv_[++i] );
    }
    else if ( argument == "--account" && i + 1 < argc_ )
    {
      args_.get().account_number = std::stoul( argv_[++i] );
    }
    else if ( argument == "--client-name" && i + 1 < argc_ )
    {
      args_.get().client_name = std::string( argv_[++i] );
    }
    else if ( argument[0] != '-' && args_.get().command.empty() )
    {
      // First non flag is the command
      args_.get().command = argument;
    }
    else
    {
      // Unknown argument
      std::cerr << "Unknown argument: " << argument << std::endl;
    }
  }
}

void Parser::set_args( int argc, char **argv )
{
  // Store argc and argv for later parsing
  argc_ = argc;
  argv_ = argv;
}

void Parser::print_help( const std::string& command )
{
  if ( command == "add-entry" )
  {
    std::cout << "Usage: add-entry [options]\n"
              << "Options:\n"
              << "  --account-from <num>    Account from\n"
              << "  --account-to <num>      Account to\n"
              << "  --amount <double>       Amount\n"
              << "  --description <str>     Description\n"
              << "  --type <debit|credit>   Type\n";
  }
  else if ( command == "get-balance" )
  {
    std::cout << "Usage: get-balance [options]\n"
              << "Options:\n"
              << "  --account <num>         Account number\n";
  }
  else if ( command == "list-entries" )
  {
    std::cout << "Usage: list-entries\n"
              << "Lists all entries.\n";
  }
  else if ( command == "add-client" )
  {
    std::cout << "Usage: add-client [options]\n"
              << "Options:\n"
              << "  --client-name <str>     Client name\n"
              << "  --account-number <num>  Account number\n";
  }
  else
  {
    std::cout << "Available commands:\n"
              << "  add-client    Add a new client\n"
              << "  add-entry     Add a new entry\n"
              << "  get-balance   Get balance for an account\n"
              << "  list-entries  List all entries\n"
              << "Use --help <command> for more info.\n";
  }
}

} // namespace smallbanc::argparse