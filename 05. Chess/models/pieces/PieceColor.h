#include <string>
using namespace std;

enum class PieceColor {
    WHITE,
    BLACK
};

string toString(PieceColor color) {
    switch (color) {
        case PieceColor::WHITE:
            return "WHITE";
        case PieceColor::BLACK:
            return "BLACK";
        default:
            return "UNKNOWN_COLOR";
    }
}