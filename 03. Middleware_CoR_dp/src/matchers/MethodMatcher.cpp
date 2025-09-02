#include "middleware/matchers/MethodMatcher.h"
using namespace std;
bool MethodMatcher::matches(Request* req) {
    if (!req) return false;
    return req->method == method;
}