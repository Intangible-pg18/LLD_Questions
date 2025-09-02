#include "middleware/handlers/LoggingHandler.h"
#include "middleware/handlers/AbstractHandler.h"
#include <iostream>
using namespace std;
void LoggingHandler::handle(Request* req, Response* res) {
    cout << "[LOG] " << req->method << " " << req->path << endl;
    AbstractHandler::handle(req, res);
}