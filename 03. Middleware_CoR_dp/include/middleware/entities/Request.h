#pragma once
#include <string>
#include <unordered_map>
using namespace std;
class Request {
public:
    string path;
    string method;
    string body;
    unordered_map<string,string> headers;
};