#pragma once

#include "smallbanc/io.h"

#include <memory>
#include <string>

namespace smallbanc
{
namespace ledger
{

class Ledger
{
public:
  Ledger( const std::string &file );

  /**
   * @brief Reads a ledger file
   *
   * Gets the content of a ledger file. If the file doesn't exists,
   * raises an exception.
   *
   * @param filename The filename for the new ledger
   * @return Ledger The created ledger instance
   */
  void fetch();

  /**
   * @brief Save current ledager state to loaded file
   *
   */
  void store();

  void create( std::shared_ptr<smallbanc::io::IFileCreator> file_creator =
                   std::make_shared<smallbanc::io::FileCreator>() );

  /**
   * @brief Checks if the passed ledger file exists
   *
   * @param filename The filename to check
   * @return true If the file exists
   * @return false If the file does not exist
   */
  bool exists() const;

private:
  Ledger( const Ledger & ) = delete;
  Ledger &operator=( const Ledger & ) = delete;
  Ledger( Ledger && ) = default;
  Ledger &operator=( Ledger && ) = delete;

  std::string m_file;
  bool m_exists = false;
};

} // namespace ledger
} // namespace smallbanc
