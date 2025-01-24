//
// Created by kibbe on 1/18/2025.
//

#ifndef CONFIG_H
#define CONFIG_H

using json = nlohmann::json;

class Config {
public:
    template <typename T>
    static T* getConfig(const std::string& key, T defaultValue);

    template<typename T>
    static T get(const std::string& key, T defaultValue);

    static void newFrame();

    static void loadConfig(const json& newConfig);
    static void loadConfig(const std::string& name);
    static void saveConfig(const std::string& name);

    static void printJson();

private:
    struct TrackedValueBase {
        virtual ~TrackedValueBase() = default;
        virtual void updateJson(json& value) = 0;
        std::vector<std::string> path;
    };

    template <typename T>
    struct TrackedValue : TrackedValueBase {
        T value;
        TrackedValue(const T& initialValue) : value(initialValue) {}

        void updateJson(json& jsonValue) override {
            if (value != jsonValue.get<T>()) {
                jsonValue = value;
            }
        }
    };

    static json& getJsonByPath(const std::vector<std::string>& path, bool createPath = false);
    static std::vector<std::string> parsePath(const std::string& key);
    static void ensurePath(const std::vector<std::string>& path);

    static std::map<std::string, std::unique_ptr<TrackedValueBase>> changes;
    static json currentConfig;
};

template <typename T>
T* Config::getConfig(const std::string& key, T defaultValue) {
    auto path = parsePath(key);

    // First try to get the value without creating the path
    try {
        json& value = getJsonByPath(path, false);

        // If we got here, the path exists
        if (!value.is_null()) {
            auto tracked = std::make_unique<TrackedValue<T>>(value.get<T>());
            tracked->path = path;
            T* ptr = &tracked->value;
            changes[key] = std::move(tracked);
            return ptr;
        }
    }
    catch (...) {
        // Path doesn't exist or has wrong type, we'll create it
    }

    // Create/overwrite the path with our new value
    json& value = getJsonByPath(path, true);
    value = defaultValue;

    auto tracked = std::make_unique<TrackedValue<T>>(value.get<T>());
    tracked->path = path;
    T* ptr = &tracked->value;
    changes[key] = std::move(tracked);
    return ptr;
}

// Get the untracked config value
template <typename T>
T Config::get(const std::string& key, T defaultValue) {
    auto path = parsePath(key);

    try {
        json& value = getJsonByPath(path, false);

        if (!value.is_null()) {
            // Ensure the type matches before returning
            return value.get<T>();
        }
    }
    catch (const std::out_of_range&) {
        // Path doesn't exist
        if (!false) {
            throw;
        }
    }
    catch (const nlohmann::json::type_error&) {
        // Path exists but has the wrong type
    }
    catch (const std::exception& e) {
        // Log or handle unexpected exceptions
        throw;
    }

    // Optionally create the path with the default value
    json& value = getJsonByPath(path, false);
    value = defaultValue;
    return value.get<T>();
}

#endif //CONFIG_H
