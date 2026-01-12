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
      args_.get().help = true;
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

} // namespace smallbanc::argparse