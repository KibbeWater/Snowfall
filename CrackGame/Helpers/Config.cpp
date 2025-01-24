//
// Created by kibbe on 1/18/2025.
//

#include "pch.h"

using json = nlohmann::json;

json Config::currentConfig;
std::map<std::string, std::unique_ptr<Config::TrackedValueBase>> Config::changes;

void onHotkeyTriggered(const std::string& path) {
    // Placeholder for future hotkey action
    std::cout << "Hotkey triggered for path: " << path << std::endl;

    // Implement future logic here
}

void processHotkeys(const json& config, const std::string& currentPath = "") {
    for (auto it = config.begin(); it != config.end(); ++it) {
        const std::string key = it.key();
        const auto& value = it.value();

        // Construct the full path
        std::string path = currentPath.empty() ? key : currentPath + "_" + key;

        if (value.is_object()) {
            // Check if the object has "enabled" and "hotkey" keys
            if (value.contains("enabled") && value.contains("hotkey")) {
                bool enabled = value["enabled"].get<bool>();
                int hotkey = value["hotkey"].get<int>();

                if (hotkey != ImGuiKey_None && ImGui::IsKeyPressed(static_cast<ImGuiKey>(hotkey))) {
                    // Toggle the enabled state
                    auto enabledPtr = Config::getConfig(path + "_enabled", enabled);
                    *enabledPtr = !enabled;

                    // Call the placeholder function when the hotkey runs
                    onHotkeyTriggered(path);
                }
            }

            // Recurse into the object
            processHotkeys(value, path);
        }
    }
}

std::vector<std::string> Config::parsePath(const std::string& key) {
    std::vector<std::string> path;
    std::string segment;
    std::istringstream stream(key);

    while (std::getline(stream, segment, '_')) {
        path.push_back(segment);
    }

    return path;
}

void Config::ensurePath(const std::vector<std::string>& path) {
    json* current = &currentConfig;

    for (const auto& segment : path) {
        if (!current->contains(segment)) {
            (*current)[segment] = json::object();
        }
        current = &(*current)[segment];
    }
}

json& Config::getJsonByPath(const std::vector<std::string>& path, bool createPath) {
    json* current = &currentConfig;

    for (size_t i = 0; i < path.size(); ++i) {
        const auto& segment = path[i];

        if (createPath) {
            // If we're creating the path, handle the last element differently
            if (i == path.size() - 1) {
                // For the last element, we'll overwrite whatever is there
                (*current)[segment] = nullptr;
            }
            else if (!current->contains(segment)) {
                // For intermediate elements, create objects only if they don't exist
                (*current)[segment] = json::object();
            }
        }

        // This will throw if the path doesn't exist and createPath is false
        current = &(*current)[segment];
    }

    return *current;
}

void Config::newFrame() {
	processHotkeys(currentConfig);

    for (const auto& [key, tracked] : changes) {
        try {
            json& value = getJsonByPath(tracked->path, false);
            tracked->updateJson(value);
        }
        catch (...) {
            // If the path no longer exists, skip this update
        }
    }

    changes.clear();
}

void Config::loadConfig(const json& newConfig) {
    currentConfig = newConfig;
}

void Config::loadConfig(const std::string& name) {
    std::ifstream file(FS::GetConfig(name + ".json"));
    if (!file.is_open()) {
        std::cout << "File " << name << ".json does not exist." << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    auto json = json::parse(buffer);
    changes.clear();

    currentConfig = json;
}

void Config::saveConfig(const std::string& name) {
    std::ofstream out;
    out.open(FS::GetConfig(name + ".json"));

    out << currentConfig.dump(4);

    out.close();
}

void Config::printJson() {
    std::cout << currentConfig.dump() << std::endl;
}
