#include "middleware/matchers/HeaderMatcher.h"
using namespace std;
bool HeaderMatcher::matches(Request* req) {
    if (!req) return false;
    auto it = req->headers.find(key);
    if (it == req->headers.end()) return false;
    if (value.empty()) return true;
    return it->second == value;
}