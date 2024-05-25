#include "pch.h"

std::vector<GameObject> Game::GetGameObjects() {
	Unity::il2cppClass* m_pSystemTypeClass = IL2CPP::Class::Find("UnityEngine.GameObject");
	auto m_pSystemType = IL2CPP::Class::GetSystemType(m_pSystemTypeClass);
	auto m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(m_pSystemType);

	std::vector<GameObject> m_vGameObjects = {};
	for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u) {
		Unity::CGameObject* m_pObject = m_pObjects->At(u);
		if (!m_pObject) continue;
		m_vGameObjects.push_back(GameObject(m_pObject));
	}

    return m_vGameObjects;
}
