#include <string>

namespace smallbanc::args {

struct Args {
  // Define your argument variables here
  bool help = false;
  std::string configFile;

  // Constructor to initialize default values if needed
  Args() = default;
};

} // namespace smallbanc::args