#include "middleware/MiddlewareManager.h"
#include "middleware/LoggingHandler.h"
#include "middleware/AuthHandler.h"
#include "middleware/CompressionHandler.h"
#include "middleware/SimpleHandler.h"
#include "middleware/RoutingHandler.h"
#include "middleware/Request.h"
#include "middleware/Response.h"
#include <iostream>
using namespace std;
int main() {
    MiddlewareManager mgr;
    LoggingHandler* log1 = new LoggingHandler();
    AuthHandler* auth1 = new AuthHandler();
    RoutingHandler* route1 = new RoutingHandler();
    log1->setNext(auth1);
    auth1->setNext(route1);
    mgr.addChain("static", log1);

    LoggingHandler* log2 = new LoggingHandler();
    CompressionHandler* comp2 = new CompressionHandler();
    RoutingHandler* route2 = new RoutingHandler();
    log2->setNext(comp2);
    comp2->setNext(route2);
    mgr.addChain("api", log2);

    AuthHandler* auth3 = new AuthHandler();
    RoutingHandler* route3 = new RoutingHandler();
    auth3->setNext(route3);
    mgr.addChain("admin", auth3);

    SimpleHandler* profilerA = new SimpleHandler("Profiler");
    mgr.insertAfter("api", "Logging", profilerA);

    SimpleHandler* profilerB = new SimpleHandler("Profiler");
    mgr.insertAfter("admin", "Auth", profilerB);

    SimpleHandler* monitor = new SimpleHandler("Monitor");
    mgr.insertAfter("api", "Compression", monitor);

    Request* req = new Request();
    req->path = "/api/data";
    req->method = "GET";
    req->headers["Authorization"] = "Bearer valid-token";
    Response* res = new Response();
    IHandler* chain = mgr.getChain("api");
    if (chain) chain->handle(req, res);
    cout << "Final response: " << res->status << " " << res->body << endl;

    mgr.removeHandler("api", "Profiler");

    Request* req2 = new Request();
    req2->path = "/api/data";
    req2->method = "GET";
    req2->headers["Authorization"] = "Bearer valid-token";
    Response* res2 = new Response();
    IHandler* chain2 = mgr.getChain("api");
    if (chain2) chain2->handle(req2, res2);
    cout << "Final response after removal: " << res2->status << " " << res2->body << endl;

    return 0;
}
