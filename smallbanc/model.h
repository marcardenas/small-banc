#pragma once

#include <chrono>
#include <string>

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