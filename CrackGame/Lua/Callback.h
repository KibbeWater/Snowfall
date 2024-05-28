#pragma once

class Callbacks {
public:
    enum class Event {
        OnMove,
        HandleMove,
        Render,
    };

    using Callback = sol::protected_function;

private:
    std::unordered_map<Event, std::vector<Callback>> callbacks;

public:
    void register_callback(Event event, Callback callback);

    void clear_callbacks();

    template <typename ... Args>
    bool trigger_event(Event event, Args... args) {
        bool shouldBlock = false;
        auto it = callbacks.find(event);
        if (it != callbacks.end()) {
            for (auto& callback : it->second) {
                bool ret = false;
                try {
                    sol::protected_function_result ret = callback(args...);
                    if (ret.valid()) 
                        if (ret.get_type() == sol::type::boolean)
                            if (ret.get<bool>())
                                shouldBlock = ret;
                } catch (const std::exception& e) {
                    std::cerr << "Error calling Lua function: " << e.what() << std::endl;
                }
                
                if (ret) shouldBlock = true;
            }
        }
        return shouldBlock;
    }
};
