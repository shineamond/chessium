#pragma once

#include "CoreFunctions.h"
#include "ChessBoard.h"
#include "ChessClock.h"
#include "WrappedTexture.h"



class ClassicChessGame
{
    private:
        ChessBoard board_;
        ChessClock clock_;
        _CHESS_PIECE_COLORS side_to_move_first_;
        _CHESS_PIECE_COLORS side_to_move_;
        //bool running_;
        bool game_over_;

    public:
        ClassicChessGame();
        void DrawPlayers() const;
        void Setup();
        void Start();
        void Run();
};
