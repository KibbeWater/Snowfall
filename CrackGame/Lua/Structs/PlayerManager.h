#pragma once

class PlayerManager {
    PlayerManager_o* manager;
public:
    PlayerManager(PlayerManager_o* engineManager) {
        this->manager = engineManager;
    }

    Vector3 GetPosition();

    int GetNumber();

    bool IsDead();
    // bool IsLocal();

    std::string GetName();
};
