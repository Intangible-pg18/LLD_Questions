#include "middleware/handlers/RoutingHandler.h"
using namespace std;
void RoutingHandler::handle(Request* req, Response* res) {
    if (req->path == "/") {
        res->status = 200;
        res->body = "Welcome Home";
        return;
    }
    if (req->path == "/api/data") {
        res->status = 200;
        res->body = "{\"data\":\"value\"}";
        res->headers["Content-Type"] = "application/json";
        return;
    }
    res->status = 404;
    res->body = "Not Found";
}