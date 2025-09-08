#include <memory>
#include "models/board/Cell.h"

class Move {
    Cell& source;
    Cell& destination;
    public:
        Move(Cell& source, Cell& destination) : source(source), destination(destination) {}

        Cell& getSource() {return source;}

        Cell& getDestination() {return destination;}
};