#pragma once

class GameObject {
	Unity::CGameObject* m_pGameObject;

public:
	enum GameObjectType {
		CUBE,
		SPHERE,
	};

	GameObject(Unity::CGameObject* pGameObject);
	GameObject(GameObjectType type);

	void SetActive(bool bActive);
	bool GetActive();

	bool GetBool(std::string name);
	void SetBool(std::string name, bool value);

	int GetInt(std::string name);
	void SetInt(std::string name, int value);

	float GetFloat(std::string name);
	void SetFloat(std::string name, float value);

	Transform GetTransform();

	std::string GetName();
};
