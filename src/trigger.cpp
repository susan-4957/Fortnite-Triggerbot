#include <windows.h>
#include <thread>

#include "trigger.h"
#include "config.h"

void Triggerbot::Loop() {
    while (running) {
        if (Config::trigger_enabled && OnTarget()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(Config::trigger_delay));
            if (OnTarget()) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                std::this_thread::sleep_for(std::chrono::milliseconds(8));
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
}

bool Triggerbot::OnTarget() {
    Vec2 center = Overlay::ScreenCenter();
    int hits = Overlay::CountColor(center, Config::trigger_zone, Config::enemy_color);
    return hits > 6;
}
