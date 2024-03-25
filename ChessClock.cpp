#include "ChessClock.h"



ChessClock::ChessClock()
{
    time_limit_ = 0;
    white_time_left_ = 0;
    black_time_left_ = 0;
    is_running_ = false;
    side_to_move_ = _WHITE;
    extra_time_after_each_move_ = 0;
}



ChessClock::ChessClock(const int time_limit, const int extra_time_after_each_move)
{
    time_limit_ = time_limit;
    white_time_left_ = time_limit;
    black_time_left_ = time_limit;
    extra_time_after_each_move_ = extra_time_after_each_move;
}



void ChessClock::StartClock()
{
    if (time_limit_ != 0)
    {
        is_running_ = true;
        thread clock_thread(&ChessClock::RunClock, this);
        clock_thread.detach();
    }
}



void ChessClock::StopClock()
{
    is_running_ = false;
}



void ChessClock::RunClock()
{
    while(is_running_)
    {
        auto start_time_point = high_resolution_clock::now();

        MUTEX.lock();

//        cout << "White time left: " << white_time_left_ << " seconds\n";
//        cout << "Black time left: " << black_time_left_ << " seconds\n\n";

        if (side_to_move_ == _WHITE)
        {
            white_time_left_ -= 250;
        }
        else if (side_to_move_ == _BLACK)
        {
            black_time_left_ -= 250;
        }

        if (white_time_left_ == 0 || black_time_left_ == 0)
        {
            is_running_ = false;
            return;
        }

        MUTEX.unlock();

        //this_thread::sleep_for(milliseconds(1000));

        auto end_time_point = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds> (end_time_point - start_time_point).count();

        int remaining_time = 250 - duration;
        if (remaining_time > 0)
        {
            this_thread::sleep_for(milliseconds(remaining_time));
        }
    }
}



void ChessClock::SetSideToMove(const _CHESS_PIECE_COLORS side_to_move)
{
    side_to_move_ = side_to_move;
}



pair<string, string> ChessClock::ConvertTime()
{
    int white_hours_left = white_time_left_ / (1000 * 60 * 60);
    int white_minutes_left = (white_time_left_ / (1000 * 60)) % 60;
    int white_seconds_left = (white_time_left_ % (1000 * 60)) / 1000;

    string white_time_left = "0" + to_string(white_hours_left) + ':';
    if (white_minutes_left < 10)
    {
        white_time_left += ('0' + to_string(white_minutes_left) + ':');
    }
    else
    {
        white_time_left += (to_string(white_minutes_left) + ':');
    }

    if (white_seconds_left < 10)
    {
        white_time_left += ('0' + to_string(white_seconds_left));
    }
    else
    {
        white_time_left += (to_string(white_seconds_left));
    }

    int black_hours_left = black_time_left_ / (1000 * 60 * 60);
    int black_minutes_left = (black_time_left_ / (1000 * 60)) % 60;
    int black_seconds_left = (black_time_left_ % (1000 * 60)) / 1000;

    string black_time_left = "0" + to_string(black_hours_left) + ':';
    if (black_minutes_left < 10)
    {
        black_time_left += ('0' + to_string(black_minutes_left) + ':');
    }
    else
    {
        black_time_left += (to_string(black_minutes_left) + ':');
    }

    if (black_seconds_left < 10)
    {
        black_time_left += ('0' + to_string(black_seconds_left));
    }
    else
    {
        black_time_left += (to_string(black_seconds_left));
    }

    return make_pair(white_time_left, black_time_left);
}



void ChessClock::RenderTime()
{
    pair<string, string> temp = ConvertTime();
    string white_time_left = temp.first;
    string black_time_left = temp.second;

    SDL_SetRenderDrawColor(RENDERER, 70, 70, 70, 255);
    SDL_Rect clear_area {480, 13, 98, 33}; // Black's clock area
    SDL_RenderFillRect(RENDERER, &clear_area);
    clear_area.y = 714; // White's clock area
    SDL_RenderFillRect(RENDERER, &clear_area);

    WrappedTexture black_clock_texture;
    black_clock_texture.SetupTextureFromText(24, true, black_time_left, _WHITE_COLOR);
    black_clock_texture.Render(480, 13);

    WrappedTexture white_clock_texture;
    white_clock_texture.SetupTextureFromText(24, true, white_time_left, _WHITE_COLOR);
    white_clock_texture.Render(480, 714);
}



int ChessClock::GetTimeLeft(const _CHESS_PIECE_COLORS side) const
{
    if (side == _WHITE)
    {
        return white_time_left_;
    }
    else if (side == _BLACK)
    {
        return black_time_left_;
    }

    return 0;
}



int ChessClock::GetTimeLimit() const
{
    return time_limit_;
}



void ChessClock::AddExtraTime()
{
    if (side_to_move_ == _BLACK)
    {
        black_time_left_ += extra_time_after_each_move_;
    }
    else if (side_to_move_ == _WHITE)
    {
        white_time_left_ += extra_time_after_each_move_;
    }
}



//void ChessClock::ResetClock()
//{
//    white_time_left_ = time_limit_;
//    black_time_left_ = time_limit_;
//}
