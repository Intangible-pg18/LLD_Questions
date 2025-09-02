#include "middleware/handlers/SimpleHandler.h"
#include <iostream>
using namespace std;
void SimpleHandler::handle(Request* req, Response* res) {
    cout << "[" << name << "] executed for " << req->path << endl;
    AbstractHandler::handle(req, res);
}