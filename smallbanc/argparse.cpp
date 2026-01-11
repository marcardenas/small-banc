#include <functional>
#include <smallbanc/argparse.h>
#include <string>

namespace smallbanc::argparse
{

Parser::Parser(std::reference_wrapper<Args> args) : args_(args) {}

void Parser::parse()
{
  for (int i = 1; i < argc_; ++i)
  {
    auto argument = std::string(argv_[i]);

    if (argument == "--help")
    {
      args_.get().help = true;
    }
    else if (argument == "--config" && i + 1 < argc_)
    {
      args_.get().configFile = std::string(argv_[++i]);
    }
    else if (argument == "--ledger" && i + 1 < argc_)
    {
      args_.get().ledger_location = std::string(argv_[++i]);
    }
  }
}

void Parser::set_args(int argc, char **argv)
{
  // Store argc and argv for later parsing
  argc_ = argc;
  argv_ = argv;
}

} // namespace smallbanc::argparse