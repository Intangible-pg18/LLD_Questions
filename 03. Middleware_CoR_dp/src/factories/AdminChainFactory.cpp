#include "middleware/factories/AdminChainFactory.h"
#include "middleware/handlers/AuthHandler.h"
#include "middleware/handlers/LoggingHandler.h"
#include "middleware/handlers/RoutingHandler.h"
#include <middleware/registry/ChainFactoryRegistry.h>
#include <middleware/factories/FactoryType.h>

using namespace std;
unique_ptr<IHandler> AdminChainFactory::create() {
    auto a = make_unique<AuthHandler>(); 
    auto l = make_unique<LoggingHandler>(); 
    auto r = make_unique<RoutingHandler>(); 
    l->setNext(move(r));
    a->setNext(move(l));
    return a;
}

namespace {
    static ChainFactoryRegistrar registrar_api(
        FactoryType::Admin,
        []() -> std::unique_ptr<IHandler> {
            AdminChainFactory factory;
            return factory.create();
        }
    );
}