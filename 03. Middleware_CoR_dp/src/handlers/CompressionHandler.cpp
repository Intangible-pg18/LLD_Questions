#include "middleware/handlers/CompressionHandler.h"
using namespace std;
void CompressionHandler::handle(Request* req, Response* res) {
    AbstractHandler::handle(req, res);
    res->headers["Content-Encoding"] = "gzip";
}