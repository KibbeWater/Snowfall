#include "pch.h"

Vector3::Vector3(UnityEngine_Vector3_o unityVector) {
	this->x = unityVector.fields.x;
	this->y = unityVector.fields.y;
	this->z = unityVector.fields.z;
}

Vector3::Vector3(Unity::Vector3 unityVector) {
	this->x = unityVector.x;
	this->y = unityVector.y;
	this->z = unityVector.z;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = z;
	this->y = y;
	this->z = z;
}

UnityEngine_Vector3_o Vector3::ToEngine() {
	UnityEngine_Vector3_o newVec = {};

	newVec.fields.x = this->x;
	newVec.fields.y = this->y;
	newVec.fields.z = this->z;

	return newVec;
}

Unity::Vector3* Vector3::ToUnity() {
	auto newVec = new Unity::Vector3(this->x, this->y, this->z);

	return newVec;
}
