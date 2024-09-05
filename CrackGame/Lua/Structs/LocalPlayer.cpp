#include "pch.h"

Vector3 LocalPlayer::GetPosition() {
	auto myPos = Vector3(reinterpret_cast<Unity::CTransform*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerCam)->GetPosition());
	return myPos;
}

Vector3 LocalPlayer::GetRotation() {
	return Vector3(reinterpret_cast<Unity::CTransform*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerCam)->GetRotation().ToEuler());
}

int LocalPlayer::GetNumber() {
	return this->manager->fields.playerNumber;
}

bool LocalPlayer::IsDead() {
	return this->manager->fields.dead;
}

std::string LocalPlayer::GetName() {
	auto username = reinterpret_cast<Unity::System_String*>(this->manager->fields.username);
	return username->ToString().substr(0, this->manager->fields.username->fields.m_stringLength);
}