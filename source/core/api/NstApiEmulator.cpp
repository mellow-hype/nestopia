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

#include "string.h"
#include "../NstMachine.hpp"
#include "NstApiEmulator.hpp"


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

        std::string Emulator::DumpDisasm() {
            return machine.cpu.DumpDisasm();
        }

        std::string Emulator::DumpRegs() {
            return machine.cpu.DumpRegisters();
        }

        std::string Emulator::DumpStack() {
            return machine.cpu.DumpStackFrame();
        }
    }
}
