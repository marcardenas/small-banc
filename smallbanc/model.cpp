

class Account {
public:
  Account() = delete;
  Account(const Account &) = delete;
  Account &operator=(const Account &) = delete;
  Account(Account &&) = delete;
  Account &operator=(Account &&) = delete;

  Account create();
};