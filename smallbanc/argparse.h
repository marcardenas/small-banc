#pragma once

#include <functional>
#include <string>

namespace smallbanc {
namespace argparse {

struct Args {
  // Define your argument variables here
  bool help = false;
  std::string configFile;
  std::string ledger_location;

  // Constructor to initialize default values if needed
  Args() = default;
};

class Parser {
public:
  Parser(std::reference_wrapper<Args> args);
  void parse();
  void set_args(int argc, char** argv);

private:
  std::reference_wrapper<Args> args_;
  int argc_;
  char **argv_;
};

} // namespace argparse

} // namespace smallbanc