#include "middleware/factories/AdminChainFactory.h"
#include "middleware/handlers/AuthHandler.h"
#include "middleware/handlers/LoggingHandler.h"
#include "middleware/handlers/RoutingHandler.h"
using namespace std;
unique_ptr<IHandler> AdminChainFactory::create() {
    auto a = make_unique<AuthHandler>(); 
    auto l = make_unique<LoggingHandler>(); 
    auto r = make_unique<RoutingHandler>(); 
    l->setNext(move(r));
    a->setNext(move(l));
    return a;
}