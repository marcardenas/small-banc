#include "smallbanc/model.hpp"

class IAction
{
public:
    virtual ~IAction() = default;
    virtual void execute() = 0;
};

class AddClientAction : public IAction
{
public:
    AddClientAction( smallbanc::model::Client client ) : m_client( client ) {}
    void execute() override
    {
        // Lógica para agregar cliente
    }
private:
    smallbanc::model::Client m_client;
};