#include "memory.hpp"
#include <thread>

namespace offsets {
    // client
    constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEA964;
    constexpr ::std::ptrdiff_t dwEntityList = 0x4DFFFB4;
    constexpr ::std::ptrdiff_t dwForceAttack = 0x322DDEC;
    
    //entity
    constexpr ::std::ptrdiff_t m_iHealth = 0x100;
    constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
    constexpr ::std::ptrdiff_t m_iCrosshairId = 0x11838;
    
    constexpr ::std::ptrdiff_t dwForceJump = 0x52BBD48;
    constexpr ::std::ptrdiff_t m_fFlags = 0x104;

};


int main()
{
    const auto mem = memory(L"csgo.exe");

    const auto client = mem.get_module_address(L"client.dll");
   /* std::cout << "csgo id is: " << std::dec << process_id << '\n';
    std::cout << "client.dll address is: 0x" << std::hex << std::uppercase << client << '\n';*/
    while (true) {

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        const auto local_player = mem.read<std::uintptr_t>(client + offsets::dwLocalPlayer);
        const auto local_player_flags = mem.read<std::uintptr_t>(local_player + offsets::m_fFlags);

        if (GetAsyncKeyState(VK_SPACE))
        {
            (local_player_flags & (1 << 0)) ?
                mem.write<std::uintptr_t>(client + offsets::dwForceJump, 5) :
                mem.write<std::uintptr_t>(client + offsets::dwForceJump, 4);

        }
        // fazer um glow bom pro csgo.
    }
}
