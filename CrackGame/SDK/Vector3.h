#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(UnityEngine_Vector3_o unityVector);
	Vector3(Unity::Vector3 unityVector);
	Vector3(float x, float y, float z);

	UnityEngine_Vector3_o ToEngine();
	Unity::Vector3* ToUnity();

	float distanceTo(Vector3 other) {
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	// Get the normalized vector between our position and the target position
	Vector3 normalized(Vector3 target) {
		Vector3 direction = target - *this;
		float distance = this->distanceTo(target);
		return Vector3(direction.x / distance, direction.y / distance, direction.z / distance);
	}

	Vector3 lerp(Vector3 target, float t) {
		return Vector3(x + (target.x - x) * t, y + (target.y - y) * t, z + (target.z - z) * t);
	}

	#pragma region Operators
	Vector3 operator+(Vector3 vec) {
		return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	Vector3 operator+(int val) {
		return Vector3(this->x + val, this->y + val, this->z + val);
	}

	Vector3 operator-(Vector3 vec) {
		return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	Vector3 operator-(int val) {
		return Vector3(this->x - val, this->y - val, this->z - val);
	}

	Vector3 operator*(Vector3 vec) {
		return Vector3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	Vector3 operator*(int val) {
		return Vector3(this->x * val, this->y * val, this->z * val);
	}

	Vector3& operator+=(const Vector3& vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	Vector3& operator+=(int val) {
		this->x += val;
		this->y += val;
		this->z += val;
		return *this;
	}

	Vector3& operator-=(const Vector3& vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	Vector3& operator-=(int val) {
		this->x -= val;
		this->y -= val;
		this->z -= val;
		return *this;
	}

	Vector3& operator*=(const Vector3& vec) {
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		return *this;
	}

	Vector3& operator*=(int val) {
		this->x *= val;
		this->y *= val;
		this->z *= val;
		return *this;
	}
	#pragma endregion
};
