#include "pch.h"

void Callbacks::register_callback(Event event, Callback callback) {
    callbacks[event].push_back(std::move(callback));
}

void Callbacks::clear_callbacks() {
    callbacks.clear();
}
