#include "smallbanc/client.hpp"
#include "smallbanc/ledger.hpp"
#include "smallbanc/model.hpp"

namespace smallbanc
{

namespace actions
{

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

class AddEntryAction : public IAction
{
public:
  AddEntryAction( smallbanc::model::Entry &entry,
    std::shared_ptr<smallbanc::ledger::LedgerWriter> writer )
      : m_entry( entry ), m_writer( writer )
  {
  }

  void execute() override
  {
    if( !m_writer->exists() )
    {
      m_writer->initialize();
    }
    m_writer->insert( m_entry );
    m_writer->write();
  }

private:
  smallbanc::model::Entry &m_entry;
  std::shared_ptr<smallbanc::ledger::LedgerWriter> m_writer;
};

}

}