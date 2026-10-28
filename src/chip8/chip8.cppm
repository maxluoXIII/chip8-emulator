module;

#include <cstdint>

export module Chip8;

import std;

export namespace Chip8 {
    constexpr int MEMORY_SIZE = 4096;
    constexpr int GEN_REGISTER_COUNT = 16;
    constexpr int DISPLAY_WIDTH = 64;
    constexpr int DISPLAY_HEIGHT = 32;

    enum class Instruction {
        ClearScreen,            // 0x00E0
        Jump,                   // 0x1NNN
        Subroutine,             // 0x2NNN
        Return,                 // 0x00EE
        SkipIfScalarEqual,      // 0x3XNN
        SkipIfScalarNotEqual,   // 0x4XNN
        SkipIfRegEqual,         // 0x5XY0
        SkipIfRegNotEqual,      // 0x9XY0
        SetScalar,              // 0x6XNN
        AddScalar,              // 0x7XNN
        SetRegister,            // 0x8XY0
        Or,
        And,
        Xor,
        AddRegister,
        Subtract,
        SubtractReverse,
        ShiftRight,
        ShiftLeft,
        SetIndex,               // 0xANNN
        JumpWithOffset,
        Random,
        Display,                // 0xDXYN
        SkipIfKey,
        SkipIfNotKey,
        GetDelayTimer,
        SetDelayTimer,
        SetSoundTimer,
        AddToIndex,
        GetKey,
        FontCharacter,
        DecimalConversion,
        Store,
        Load
    };

    class Chip8 {
    public:
        Chip8();

        bool loadProgram(); // load program at address 0x200
        bool execute();
        const std::array<std::bitset<DISPLAY_HEIGHT>, DISPLAY_WIDTH>& getDisplay() const;

    private:
        void pClearScreen();
        void pDisplay(int x, int y, int height);
        Instruction pDecodeInstruction(uint16_t bytes);

        std::array<uint8_t, MEMORY_SIZE> mMemory;
        std::array<uint8_t, GEN_REGISTER_COUNT> mRegisters;
        std::stack<uint16_t> mStack;
        std::array<std::bitset<DISPLAY_HEIGHT>, DISPLAY_WIDTH> mDisplay;
        uint16_t mProgramCounter;
        uint16_t mIndexRegister;
        uint8_t mDelayTimer;
        uint8_t mSoundTimer;
    };

}
