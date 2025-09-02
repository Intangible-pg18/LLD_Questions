#include "middleware/factories/ApiChainFactory.h"
#include "middleware/handlers/LoggingHandler.h"
#include "middleware/handlers/AuthHandler.h"
#include "middleware/handlers/CompressionHandler.h"
#include "middleware/handlers/RoutingHandler.h"
using namespace std;
unique_ptr<IHandler> ApiChainFactory::create() {
    auto l = make_unique<LoggingHandler>();
    auto a = make_unique<AuthHandler>();
    auto c = make_unique<CompressionHandler>();
    auto r = make_unique<RoutingHandler>();
    c->setNext(move(r));
    a->setNext(move(c));
    l->setNext(move(a));
    return l;
}