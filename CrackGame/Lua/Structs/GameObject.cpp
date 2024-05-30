#include "pch.h"

GameObject::GameObject(Unity::CGameObject* pGameObject) {
	this->m_pGameObject = pGameObject;
}

GameObject::GameObject(GameObjectType type) {
	switch (type)
	{
	case GameObject::CUBE:
		this->m_pGameObject = Unity::GameObject::CreatePrimitive(Unity::GameObject::m_ePrimitiveType::Cube);
		break;
	case GameObject::SPHERE:
		this->m_pGameObject = Unity::GameObject::CreatePrimitive(Unity::GameObject::m_ePrimitiveType::Sphere);
		break;
	default:
		this->m_pGameObject = Unity::GameObject::CreatePrimitive(Unity::GameObject::m_ePrimitiveType::Cube);
		break;
	}
}

void GameObject::SetActive(bool bActive) {
	this->m_pGameObject->SetActive(bActive);
}

bool GameObject::GetActive() {
	return this->m_pGameObject->GetActive();
}

bool GameObject::GetBool(std::string name) {
	return this->m_pGameObject->GetMemberValue<bool>(name.c_str());
}

void GameObject::SetBool(std::string name, bool value) {
	this->m_pGameObject->SetMemberValue<bool>(name.c_str(), value);
}

int GameObject::GetInt(std::string name) {
	return this->m_pGameObject->GetMemberValue<int>(name.c_str());
}

void GameObject::SetInt(std::string name, int value) {
	this->m_pGameObject->SetMemberValue<int>(name.c_str(), value);
}

float GameObject::GetFloat(std::string name) {
	return this->m_pGameObject->GetMemberValue<float>(name.c_str());
}

void GameObject::SetFloat(std::string name, float value) {
	this->m_pGameObject->SetMemberValue<float>(name.c_str(), value);
}

Transform GameObject::GetTransform() {
	auto transform = this->m_pGameObject->GetTransform();
	return Transform(transform);
}

std::string GameObject::GetName() {
	auto name = this->m_pGameObject->GetName();
	return name->ToString().substr(0, name->m_iLength);
}
