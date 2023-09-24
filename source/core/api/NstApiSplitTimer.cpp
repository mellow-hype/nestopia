////////////////////////////////////////////////////////////////////////////////////////
// hypr-Nestopia - Split timer
////////////////////////////////////////////////////////////////////////////////////////

#include "chrono"
#include "string"
#include <time.h>
#include "NstApiSplitTimer.hpp"

// Return a formatted time string
const std::string return_current_time() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    return buf;
}

// Return a formatted date and time string
const std::string return_current_time_and_date() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X_%Y-%m-%d", &tstruct);
    return buf;
}

// Return a formatted date string
const std::string return_current_date_iso() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

// Format a split in milliseconds to a timestamp string
const std::string format_split_ms_string(time_ms split_time) {
    int decimal_precision = 1000;
    float total_seconds = (float)split_time / 1000.00;

    int secs_int = int(total_seconds);
    int fract_secs = ((int) (total_seconds * decimal_precision) % decimal_precision);
    unsigned int seconds = (time_ms)total_seconds % 60;
    unsigned int minutes = total_seconds / 60;

    char time_s[64] = {0};
    sprintf(time_s, "%.2u:%.2u.%i", minutes, seconds, fract_secs);
    return time_s;
}

// Get time since epoch in milliseconds
unsigned long long timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


namespace Nes
{
    namespace Api
    {
        SplitTimer::SplitTimer():
            timerActive (false),
            startTime (0),
            stopTime (0)
        {}

        SplitTimer::~SplitTimer() {
            if (timerActive) {
                stopTimer();
            }
        }

        // check Timer status
        bool SplitTimer::isTimerRunning() {
            return timerActive;
        }

        // Reset the timer
        void SplitTimer::Reset() {
            timerActive = false;
            startTime = 0;
            stopTime = 0;
            splits.clear();
        }

        // start the timer
        void SplitTimer::startTimer() {
            timerActive = true;
            startTime = timeSinceEpochMillisec();
        }

        // stop the timer
        void SplitTimer::stopTimer() {
            stopTime = timeSinceEpochMillisec();
            timerActive = false;
            splits.push_back(duration());
        }

        time_ms SplitTimer::lastSplit() {
            return splits.back();
        };

        std::string SplitTimer::lastSplitString() {
            return format_split_ms_string(lastSplit());
        };

        time_ms SplitTimer::duration() {
            return stopTime - startTime;
        }

        std::vector<time_ms>* SplitTimer::getSplits() {
            return &splits;
        }
    }

}
