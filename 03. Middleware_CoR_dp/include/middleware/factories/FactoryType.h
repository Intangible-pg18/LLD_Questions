#pragma once
#include <optional>
using namespace std;

enum class FactoryType {
    Unknown,
    Admin,
    Api,
    Static
};

inline string to_string(FactoryType t) {
    switch (t) {
    case FactoryType::Admin:  return "Admin";
    case FactoryType::Api:    return "Api";
    case FactoryType::Static: return "Static";
    default: return "Unknown";
    }
}

inline optional<FactoryType> from_string(const string& s) {
    if (s == "Admin")  return FactoryType::Admin;
    if (s == "Api")    return FactoryType::Api;
    if (s == "Static") return FactoryType::Static;
    return nullopt;
}