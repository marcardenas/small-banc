#include <smallbanc/argparse.h>

#include <iostream>

void print_help() {
  std::cout << "Usage: smallbanc-cli [options]\n"
            << "Options:\n"
            << "  --help                Show this help message\n"
            << "  --config <file>       Specify configuration file\n"
            << "  --ledger <location>   Specify ledger location\n";
}

int main(int argc, char *argv[]) {
  smallbanc::argparse::Args args;

  {
    smallbanc::argparse::Parser parser(std::ref(args));

    parser.set_args(argc, argv);
    parser.parse();
  }

  if (args.help) {
    print_help();
    return 0;
  }

  return 0;
};