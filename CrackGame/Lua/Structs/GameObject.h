#pragma once

class GameObject {
	Unity::CGameObject* m_pGameObject;
public:
	GameObject(Unity::CGameObject* pGameObject);

	void SetActive(bool bActive);
	bool GetActive();

	Transform GetTransform();

	std::string GetName();
};
