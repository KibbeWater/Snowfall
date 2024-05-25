#pragma once
class LocalPlayer {
    PlayerManager_o* manager;
public:
    LocalPlayer(PlayerManager_o* engineManager) {
        this->manager = engineManager;
    }

	Vector3 GetPosition();

    int GetNumber();

    bool IsDead();

    std::string GetName();
};
