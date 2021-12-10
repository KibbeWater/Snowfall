#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(UnityEngine_Vector3_o unityVector);
	Vector3(float x, float y, float z);

	UnityEngine_Vector3_o ToUnity();

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

	Vector3 operator+=(Vector3 vec) {
		return *this + vec;
	}

	Vector3 operator+=(int val) {
		return *this + val;
	}

	Vector3 operator-=(Vector3 vec) {
		return *this - vec;
	}

	Vector3 operator-=(int val) {
		return *this - val;
	}

	Vector3 operator*=(Vector3 vec) {
		return *this * vec;
	}

	Vector3 operator*=(int val) {
		return *this * val;
	}
	#pragma endregion
};

