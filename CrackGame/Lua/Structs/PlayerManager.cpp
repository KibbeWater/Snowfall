#include "pch.h"

Vector3 PlayerManager::GetPosition() {
	auto playerMovement = this->manager->fields._onlinePlayerMovement_k__BackingField;
	if (playerMovement == nullptr) return Vector3(0, 0, 0);

	return Vector3(playerMovement->fields.desiredPosition);
}

void PlayerManager::SetPosition(Vector3 position) {
	auto playerMovement = this->manager->fields._onlinePlayerMovement_k__BackingField;
	if (playerMovement == nullptr) return;

	playerMovement->fields.desiredPosition = position.ToEngine();
}

int PlayerManager::GetNumber() {
	return this->manager->fields.playerNumber;
}

bool PlayerManager::IsDead() {
	return this->manager->fields.dead;
}

std::string PlayerManager::GetName() {
	auto username = reinterpret_cast<Unity::System_String*>(this->manager->fields.username);
	return username->ToString().substr(0, this->manager->fields.username->fields.m_stringLength);
}
