#include "middleware/handlers/AuthHandler.h"
using namespace std;
void AuthHandler::handle(Request* req, Response* res) {
    auto it = req->headers.find("Authorization");
    if (it == req->headers.end() || it->second != "Bearer valid-token") {
        res->status = 401;
        res->body = "Unauthorized";
        return;
    }
    AbstractHandler::handle(req, res);
}