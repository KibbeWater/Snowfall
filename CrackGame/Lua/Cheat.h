#pragma once

class Cheat {
public:
    static void on(Callbacks::Event event, const sol::protected_function& func);
};