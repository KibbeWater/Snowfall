#include "pch.h"

Packet::Packet(Packet_o* packet) {
	this->packet = packet;
	this->readPos = 0;
}

long Packet::ReadLong() {
	long value = *reinterpret_cast<long*>(&this->packet->fields.readableBuffer->m_Items + this->readPos);
	this->readPos += sizeof(long);
	return value;
}

void Packet::WriteLong(long value) {
	if (this->packet->fields.readableBuffer->max_length < this->readPos + sizeof(long)) return;
	
	*reinterpret_cast<long*>(&this->packet->fields.readableBuffer->m_Items + this->readPos) = value;
	this->readPos += sizeof(long);
}

int Packet::ReadInt() {
	int value = *reinterpret_cast<int*>(&this->packet->fields.readableBuffer->m_Items + this->readPos);
	this->readPos += sizeof(int);
	return value;
}

void Packet::WriteInt(int value) {
	if (this->packet->fields.readableBuffer->max_length < this->readPos + sizeof(int)) return;
	
	*reinterpret_cast<int*>(&this->packet->fields.readableBuffer->m_Items + this->readPos) = value;
	this->readPos += sizeof(int);
}

float Packet::ReadFloat() {
	float value = *reinterpret_cast<float*>(&this->packet->fields.readableBuffer->m_Items + this->readPos);
	this->readPos += sizeof(float);
	return value;
}

void Packet::WriteFloat(float value) {
	if (this->packet->fields.readableBuffer->max_length < this->readPos + sizeof(float)) return;
	
	*reinterpret_cast<float*>(&this->packet->fields.readableBuffer->m_Items + this->readPos) = value;
	this->readPos += sizeof(float);
}

Vector3 Packet::ReadVector3() {
	Vector3 value(0,0,0);
	value.x = this->ReadFloat();
	value.y = this->ReadFloat();
	value.z = this->ReadFloat();
	return value;
}

void Packet::WriteVector3(Vector3 value) {
	this->WriteFloat(value.x);
	this->WriteFloat(value.y);
	this->WriteFloat(value.z);
}

void Packet::Skip(int bytes) {
	this->readPos += bytes;
}

void Packet::SetPos(int pos) {
	this->readPos = pos;
}
