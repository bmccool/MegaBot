#include "FCEUX.hpp"
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"
#include <stdlib.h> //system
#include <string>
#include "CT_window_manager.hpp"
#include "CS_time.hpp"  // REMOVE?
#include <chrono>
#include <thread>

Fceux::Fceux(std::string romname): rom(romname) {
    // Run FCEUX with rom
    LOG_S(INFO) << "Starting FCEUX with " << romname;
    std::string fceux_invocation = "fceux " + romname + " &";
    system(fceux_invocation.c_str());

    // Get window handle
    while (true)
    {
        window = get_nes_window();
        if (window != 0)
            break;
        // If the window isn't up yet, wait before trying again
        LOG_S(INFO) << "FCEUX app wasn't found, wait and try again";
        sleep_for_milliseconds(100);
    }
    LOG_S(INFO) << "Window handle: " << window;
}

void Fceux::press_and_release(const std::string keycode, int hold_time_ms) {
    
    send_key(keycode.c_str(), KEY_PRESS, window); // TODO return value?
    sleep_for_milliseconds(10);
    send_key(keycode.c_str(), KEY_RELEASE, window); // TODO return value?
}
