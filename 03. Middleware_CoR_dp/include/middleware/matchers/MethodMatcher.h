#pragma once
#include "middleware/core/IMatcher.h"
#include <string>
using namespace std;
class MethodMatcher : public IMatcher {
public:
    string method;
    MethodMatcher(const string& m):method(m){}
    bool matches(Request* req) override;
};