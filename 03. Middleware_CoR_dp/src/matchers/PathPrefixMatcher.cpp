#include "middleware/matchers/PathPrefixMatcher.h"
using namespace std;
bool PathPrefixMatcher::matches(Request* req) {
    if (!req) return false;
    if (req->path.size() < prefix.size()) return false;
    return req->path.compare(0, prefix.size(), prefix) == 0;
}