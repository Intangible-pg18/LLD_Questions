#include <string>
#include <move.h>

class Player {
    string name;
    public:
        Player(string name) {
            this->name = name;
        }

        string getName() {
            return name;
        }

        virtual Move makeMove() = 0;
};