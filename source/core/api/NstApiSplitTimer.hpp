////////////////////////////////////////////////////////////////////////////////////////
// hypr-Nestopia - Split timer
////////////////////////////////////////////////////////////////////////////////////////

#ifndef NST_API_SPLIT_TIMER_H
#define NST_API_SPLIT_TIMER_H

#include "string"
#include "vector"
#include "NstApiSplitTimer.hpp"

#ifndef NST_BASE_H
#include "../NstBase.hpp"
#endif

#ifdef NST_PRAGMA_ONCE
#pragma once
#endif

typedef unsigned long long time_ms ;

std::string format_split_ms_string(time_ms split_time);

namespace Nes
{
    namespace Api
    {
        class SplitTimer
        {
            public:
                SplitTimer();
                ~SplitTimer();

                bool isTimerRunning();
                void startTimer();
                void stopTimer();
                void Reset();
                time_ms duration();
                time_ms lastSplit();
                std::string lastSplitString();
                std::vector<time_ms>* getSplits();
            private:
                bool timerActive;
                time_ms startTime;
                time_ms stopTime;
                std::vector<time_ms> splits;
        };
    }
}

#endif