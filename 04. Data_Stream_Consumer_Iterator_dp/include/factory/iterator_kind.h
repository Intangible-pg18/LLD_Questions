#pragma once
#include <optional>
#include <string>
using namespace std;

enum class IteratorKind {
    Unknown,
    ITER_FORWARD,
    ITER_BACKWARD,
    ITER_BIDIRECTIONAL,
    ITER_JUMPER
};

inline string to_string(IteratorKind t) {
    switch (t) {
    case IteratorKind::ITER_FORWARD:  return "ITER_FORWARD";
    case IteratorKind::ITER_BACKWARD:    return "ITER_BACKWARD";
    case IteratorKind::ITER_BIDIRECTIONAL: return "ITER_BIDIRECTIONAL";
    case IteratorKind::ITER_JUMPER: return "ITER_JUMPER";
    default: return "Unknown";
    }
}

inline optional<IteratorKind> from_string(const string& s) {
    if (s == "ITER_FORWARD")  return IteratorKind::ITER_FORWARD;
    if (s == "ITER_BACKWARD")    return IteratorKind::ITER_BACKWARD;
    if (s == "ITER_BIDIRECTIONAL") return IteratorKind::ITER_BIDIRECTIONAL;
    if (s == "ITER_JUMPER") return IteratorKind::ITER_JUMPER;
    return nullopt;
}