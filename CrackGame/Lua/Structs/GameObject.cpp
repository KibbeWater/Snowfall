#include "pch.h"

GameObject::GameObject(Unity::CGameObject* pGameObject) {
	this->m_pGameObject = pGameObject;
}

void GameObject::SetActive(bool bActive) {
	this->m_pGameObject->SetActive(bActive);
}

bool GameObject::GetActive() {
	return this->m_pGameObject->GetActive();
}

Transform GameObject::GetTransform() {
	auto transform = this->m_pGameObject->GetTransform();
	return Transform(transform);
}

std::string GameObject::GetName() {
	auto name = this->m_pGameObject->GetName();
	return name->ToString().substr(0, name->m_iLength);
}
