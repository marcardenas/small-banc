#pragma once

#include <string>

namespace smallbanc
{
namespace ledger
{

class Ledger
{
public:
  static Ledger create(const std::string &filename);
  static Ledger from_file(const std::string filename);

  /**
   * @brief Save current ledager state to loaded file
   *
   */
  void store();

private:
  Ledger() = default;
  Ledger(const Ledger &) = delete;
  Ledger &operator=(const Ledger &) = delete;
  Ledger(Ledger &&) = default;
  Ledger &operator=(Ledger &&) = delete;
};

} // namespace ledger
} // namespace smallbanc
