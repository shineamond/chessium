#pragma once

#include "CoreFunctions.h"
#include "ClassicChessBoard.h"
#include "ChessClock.h"
#include "WrappedTexture.h"



class ClassicChessGame
{
    private:
        ClassicChessBoard board_;
        ChessClock clock_;
        _CHESS_PIECE_COLORS side_to_move_first_;
        _CHESS_PIECE_COLORS side_to_move_;
        //bool running_;
        bool game_over_;
        int white_score_;
        int black_score_;

    public:
        ClassicChessGame();
        void DrawPlayers() const;
        bool Setup();
        void Start();
        void RunGameWithTimer();
        void RunGameWithoutTimer();
        bool SetupTimer();
        void RenderScoreInMatch();
        void RenderScoreWhileSelectingTimer();
};
