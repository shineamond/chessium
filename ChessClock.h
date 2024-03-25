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
        int extra_time_after_each_move_;

    public:
        ChessClock();
        ChessClock(const int time_limit, const int extra_time_after_each_move);
        void StartClock();
        void StopClock();
        void RunClock();
        void SetSideToMove(const _CHESS_PIECE_COLORS side_to_move);
        pair<string, string> ConvertTime();
        void RenderTime();
        int GetTimeLeft(const _CHESS_PIECE_COLORS side) const;
        int GetTimeLimit() const;
        void AddExtraTime();
        //void ResetClock();
};
