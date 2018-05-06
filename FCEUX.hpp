#include <string>

class Fceux {
    private:
        std::string rom;
        unsigned long int window;
    public:
        Fceux(std::string romname);
        void press_and_release(const std::string keycode, int hold_time_ms = 10); // TODO return?
};

