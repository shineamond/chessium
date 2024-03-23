#pragma once

#include "CoreFunctions.h"
#include "WrappedTexture.h"



class ChessClock
{
    private:
        int time_limit_;
        int white_time_left_;
        int black_time_left_;
        bool is_running_;
        _CHESS_PIECE_COLORS side_to_move_;

    public:
        ChessClock(const int input_time_limit = 0);
        void StartClock();
        void StopClock();
        void RunClock();
        void SetSideToMove(const _CHESS_PIECE_COLORS side_to_move);
        pair<string, string> ConvertTime();
        void RenderTime();
};
