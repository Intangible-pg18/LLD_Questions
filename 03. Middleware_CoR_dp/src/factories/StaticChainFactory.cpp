#include "middleware/factories/StaticChainFactory.h"
#include "middleware/handlers/LoggingHandler.h"
#include "middleware/handlers/RoutingHandler.h"
using namespace std;
unique_ptr<IHandler> StaticChainFactory::create() {
    auto l = make_unique<LoggingHandler>();
    auto r = make_unique<RoutingHandler>();
    l->setNext(move(r));
    return l;
}