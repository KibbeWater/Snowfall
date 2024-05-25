#include "pch.h"

void Cheat::on(Callbacks::Event event, const sol::protected_function& func) {
    G::oCallbackManager->register_callback(event, func);
}
