#pragma once

class Transform {
	Unity::CTransform* m_pTransform;
public:
	Transform(Unity::CTransform* pTransform);

	void SetPosition(Vector3 position);
	Vector3 GetPosition();
};
