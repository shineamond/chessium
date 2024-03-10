#pragma once

#include "CoreFunctions.h"



class ChessBoard
{
    private:
        int pieces_positions[_BOARD_SIZE][_BOARD_SIZE];

    public:
        void DrawChessBoard() const;

};
