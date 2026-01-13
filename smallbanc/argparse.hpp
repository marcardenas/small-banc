#pragma once

#include <functional>
#include <string>

namespace smallbanc
{

namespace argparse
{

struct Args
{
  // Define your argument variables here
  std::string help_command; // "general" or specific command, empty if no help
  std::string config_file;
  std::string ledger_location;

  // Commands
  std::string command; // "add-entry", "get-balance", "list-entries", "add-client", etc.

  // Parameters for add-entry
  unsigned int account_from = 0;
  unsigned int account_to = 0;
  double amount = 0.0;
  std::string description;
  std::string type; // "debit" or "credit"

  // Parameters for get-balance
  unsigned int account_number = 0;

  // Parameters for add-client
  std::string client_name;

  // Constructor to initialize default values if needed
  Args() = default;
};

class Parser
{
public:
  Parser( std::reference_wrapper<Args> args );
  void parse();
  void set_args( int argc, char **argv );
  void print_help( const std::string& command = "" );

private:
  std::reference_wrapper<Args> args_;
  int argc_;
  char **argv_;
};

} // namespace argparse

} // namespace smallbanc