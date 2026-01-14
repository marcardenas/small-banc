// ----------------------------------------------------------------------------

#pragma once

// ----------------------------------------------------------------------------

#include <chrono>
#include <string>

// ----------------------------------------------------------------------------

namespace smallbanc
{

// ----------------------------------------------------------------------------

namespace model
{

// ----------------------------------------------------------------------------

enum class TransactionType
{
  Unknown = -1,
  Debit,
  Credit
};

// ----------------------------------------------------------------------------

struct Client
{
  unsigned int id = -1;
  std::string name;
  std::string email;
  bool is_active = false;

  bool validate()
  {
    // At least name and id must be set
    if ( ( id == -1 ) | name.empty() )
    {
      return false;
    }

    return true;
  }
};

// ----------------------------------------------------------------------------

struct Transaction
{
  unsigned int source_id = -1;
  unsigned int destination_id = -1;
  double amount;
  std::chrono::system_clock::time_point timestamp;
};

struct Account
{
  unsigned int account_number = -1;
  std::string account_type;
  double balance;
  Client owner;
  std::vector<Transaction> transactions;
};

// ----------------------------------------------------------------------------

class IModelWriter
{
public:
  virtual ~IModelWriter() = default;
  virtual void write() const = 0;
  virtual void initialize() const = 0;
};

// ----------------------------------------------------------------------------

struct Entry
{

  void checkin() { m_timestamp = std::chrono::system_clock::now(); }

  bool validate()
  {
    if ( origin == 0 || destination == 0 || amount == 0.0 ||
         type == TransactionType::Unknown )
    {
      return false;
    }

    return true;
  }

  TransactionType type = TransactionType::Unknown;
  unsigned int origin = -1;
  unsigned int destination = -1;
  double amount;
  std::string description;
  std::chrono::system_clock::time_point m_timestamp;
};

// ----------------------------------------------------------------------------

} // namespace model

// ----------------------------------------------------------------------------

} // namespace smallbanc

// ----------------------------------------------------------------------------
