#pragma once
#include <string>
#include <unordered_map>
using namespace std;
class Response {
public:
    int status;
    string body;
    unordered_map<string,string> headers;
    Response() { status = 200; }
};