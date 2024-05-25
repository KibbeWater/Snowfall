#include "pch.h"

Transform::Transform(Unity::CTransform* pTransform) {
	this->m_pTransform = pTransform;
}

void Transform::SetPosition(Vector3 position) {
	this->m_pTransform->SetPosition(*position.ToUnity());
}

Vector3 Transform::GetPosition() {
	return Vector3(this->m_pTransform->GetPosition());
}
