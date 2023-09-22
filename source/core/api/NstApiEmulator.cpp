////////////////////////////////////////////////////////////////////////////////////////
//
// Nestopia - NES/Famicom emulator written in C++
//
// Copyright (C) 2003-2008 Martin Freij
//
// This file is part of Nestopia.
//
// Nestopia is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Nestopia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Nestopia; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
////////////////////////////////////////////////////////////////////////////////////////

#include "chrono"
#include "../NstMachine.hpp"
#include "NstApiEmulator.hpp"

unsigned long long timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

namespace Nes
{
    namespace Core
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

        bool SplitTimer::isTimerRunning() {
            return timerActive;
        }

        void SplitTimer::Reset() {
            timerActive = false;
            startTime = 0;
            stopTime = 0;
        }

        void SplitTimer::startTimer() {
            timerActive = true;
            startTime = timeSinceEpochMillisec();
        }

        void SplitTimer::stopTimer() {
            stopTime = timeSinceEpochMillisec();
            timerActive = false;
        }

        unsigned long long SplitTimer::lastSplit() {
            return stopTime - startTime;
        };
    }

}


namespace Nes
{
	namespace Api
	{
		#ifdef NST_MSVC_OPTIMIZE
		#pragma optimize("s", on)
		#endif

		Emulator::Emulator()
		: machine(*new Core::Machine),
        timer()
		{
		}

		Emulator::~Emulator() throw()
		{
			delete &machine;
		}

		#ifdef NST_MSVC_OPTIMIZE
		#pragma optimize("", on)
		#endif

		Result Emulator::Execute
		(
			Core::Video::Output* video,
			Core::Sound::Output* sound,
			Core::Input::Controllers* input
		)   throw()
		{
			return machine.tracker.Execute( machine, video, sound, input );
		}

		ulong Emulator::Frame() const throw()
		{
			return machine.tracker.Frame();
		}
	}
}
