#pragma once

#include <chrono>
#include <string>

enum class TransactionType
{
  Unknown = -1,
  Debit,
  Credit
};

struct Client
{
  unsigned int id;
  std::string name;
  std::string email;
  bool is_active;
};

struct Transaction
{
  unsigned int source_id;
  unsigned int destination_id;
  double amount;
  std::chrono::system_clock::time_point timestamp;
};

struct Account
{
  unsigned int account_number;
  std::string account_type;
  double balance;
  Client owner;
  std::vector<Transaction> transactions;
};

class Entry
{
public:
  Entry( TransactionType type, const Account &origin,
    const Account &destination, double amount, const std::string &description,
    const std::chrono::system_clock::time_point &timestamp )
      : type( type ), origin( origin ), destination( destination ),
        amount( amount ), description( description ), m_timestamp( timestamp )
  {
  }

  TransactionType get_type() const { return type; }
  const Account &get_origin() const { return origin; }
  const Account &get_destination() const { return destination; }
  double get_amount() const { return amount; }
  const std::string &get_description() const { return description; }
  std::chrono::system_clock::time_point get_timestamp() const
  {
    return m_timestamp;
  }

  void set_timestamp() { m_timestamp = std::chrono::system_clock::now(); }

private:
  TransactionType type;
  Account origin;
  Account destination;
  double amount;
  std::string description;
  std::chrono::system_clock::time_point m_timestamp;
};