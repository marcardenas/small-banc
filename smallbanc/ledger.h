#pragma once

#include <string>

class Ledger
{
public:
  Ledger create(const std::string &filename);
  Ledger from_file(const std::string filename);

  /**
   * @brief Save current ledager state to loaded file
   *
   */
  void store();

private:
  Ledger() = delete;
  Ledger(const Ledger &) = delete;
  Ledger &operator=(const Ledger &) = delete;
  Ledger(Ledger &&) = delete;
  Ledger &operator=(Ledger &&) = delete;
};