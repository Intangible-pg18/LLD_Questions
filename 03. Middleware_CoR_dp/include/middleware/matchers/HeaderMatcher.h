#pragma once
#include "middleware/core/IMatcher.h"
#include <string>
using namespace std;
class HeaderMatcher : public IMatcher {
public:
    string key;
    string value;
    HeaderMatcher(const string& k, const string& v = ""):key(k),value(v){}
    bool matches(Request* req) override;
};