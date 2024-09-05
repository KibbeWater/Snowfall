#pragma once
class LocalPlayer {
    PlayerManager_o* manager;
public:
    LocalPlayer(PlayerManager_o* engineManager) {
        this->manager = engineManager;
    }

	Vector3 GetPosition();
    Vector3 GetRotation();

    int GetNumber();

    bool IsDead();

    std::string GetName();
};
