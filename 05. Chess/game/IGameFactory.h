#pragma once

#include "BoardGame.h"
#include <memory>
#include <string>

class IGameFactory {
public:
    virtual unique_ptr<BoardGame> createGame() = 0;
    virtual ~IGameFactory() = default;
};