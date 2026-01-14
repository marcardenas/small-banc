#include "smallbanc/client.hpp"
#include "smallbanc/model.hpp"

enum class Action
{
  AddClient,
  AddEntry,
  GetBalance,
  ListEntries,
};

class IAction
{
public:
  virtual ~IAction() = default;
  virtual void execute() = 0;
};

class AddClientAction : public IAction
{
public:
  AddClientAction( smallbanc::model::Client &client,
    std::shared_ptr<smallbanc::client::ClientWriter> writer )
      : m_client( client ), m_writer( writer )
  {
  }
  void execute() override
  {
    if ( !m_writer->exists() )
    {
      m_writer->initialize();
    }
    m_writer->insert( m_client );
    m_writer->write();
  };

private:
  smallbanc::model::Client &m_client;
  std::shared_ptr<smallbanc::client::ClientWriter> m_writer;
};
