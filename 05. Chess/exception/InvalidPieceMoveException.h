#include <stdexcept>
#include <string>
using namespace std;

class InvalidPieceMoveException : public runtime_error {
    public:
        InvalidPieceMoveException(string message) : runtime_error(message) {}
};