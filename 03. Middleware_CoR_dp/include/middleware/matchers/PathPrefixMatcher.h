#pragma once
#include "middleware/core/IMatcher.h"
#include <string>
using namespace std;
class PathPrefixMatcher : public IMatcher {
public:
    string prefix;
    PathPrefixMatcher(const string& p):prefix(p){}
    bool matches(Request* req) override;
};