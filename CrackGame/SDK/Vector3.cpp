#include "pch.h"
#include "Vector3.h"

Vector3::Vector3(UnityEngine_Vector3_o unityVector)
{
	this->x = unityVector.fields.x;
	this->y = unityVector.fields.y;
	this->z = unityVector.fields.z;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = z;
	this->y = y;
	this->z = z;
}

UnityEngine_Vector3_o Vector3::ToUnity()
{
	UnityEngine_Vector3_o newVec = {};

	newVec.fields.x = this->x;
	newVec.fields.y = this->y;
	newVec.fields.z = this->z;

	return newVec;
}
