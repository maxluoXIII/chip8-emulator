module;

#include <cstdint>
#include <fstream>

module Chip8;

namespace Chip8 {
    Chip8::Chip8()
    : mMemory {}, mRegisters {}, mStack {}, mDisplay {}, mProgramCounter {}, mIndexRegister {} {

    }

    bool Chip8::loadProgram() {

    }

    bool Chip8::execute() {
        uint16_t nextInstBytes = mMemory[mProgramCounter];
        mProgramCounter += 2; // Instructions are 2 bytes
        Instruction nextInst = pDecodeInstruction(nextInstBytes);
        int vx = nextInstBytes & 0x0F00;
        int vy = nextInstBytes & 0x00F0;
        int n = nextInstBytes & 0x000F;
        int nn = nextInstBytes & 0x00FF;
        int nnn = nextInstBytes & 0x0FFF;
        switch (nextInst) {
            case Instruction::ClearScreen:
                pClearScreen();
                break;
            case Instruction::Jump:
                mProgramCounter = nnn;
                break;
            case Instruction::SetScalar:
                mRegisters[vx] = nn;
                break;
            case Instruction::AddScalar:
                mRegisters[vx] += nn;
                break;
            case Instruction::SetIndex:
                mIndexRegister = nnn;
                break;
            case Instruction::Display:
                int height = n;
                pDisplay(vx, vy, height);
        }

        return true;
    }

    const std::array<std::bitset<DISPLAY_HEIGHT>, DISPLAY_WIDTH>& Chip8::getDisplay() const {
        return mDisplay;
    }

    Instruction Chip8::pDecodeInstruction(uint16_t bytes) {
        if (bytes == 0x00E0) {
            return Instruction::ClearScreen;
        } if ((bytes & 0xF000) ==  0x1000) {
            return Instruction::Jump;
        } else if ((bytes & 0xF000) == 0x6000) {
            return Instruction::SetScalar;
        } else if ((bytes & 0xF000) == 0x7000) {
            return Instruction::AddScalar;
        } else if ((bytes & 0xF000) == 0xA000) {
            return Instruction::SetIndex;
        } else if ((bytes & 0xF000) == 0xD000) {
            return Instruction::Display;
        } else {
            return Instruction::Load;
        }
    }

    void Chip8::pClearScreen() {
        for (auto& row : mDisplay) {
            row.reset();
        }
    }

    void Chip8::pDisplay(int x, int y, int height) {
        mRegisters[0xF] = 0;
        for (int i = 0; i < height && y+i < DISPLAY_HEIGHT; ++i) {
            uint8_t sprite = mIndexRegister;
            for (int j = 0; j < 8 && x+j < DISPLAY_WIDTH; ++j) {
                bool spriteBit = (sprite & (0b1000000 >> j)) > 0;
                if (mDisplay[x+j][y+i]) {
                    mRegisters[0xF] = 1;
                }
                mDisplay[x+j][y+i] = mDisplay[x+j][y+i] ^ spriteBit;
            }
        }
    }

}

