#pragma once

class Packet {
	Packet_o* packet;
	int readPos;

public:
	Packet(Packet_o* packet);

	long ReadLong();
	void WriteLong(long value);

	int ReadInt();
	void WriteInt(int value);

	float ReadFloat();
	void WriteFloat(float value);

	Vector3 ReadVector3();
	void WriteVector3(Vector3 value);

	void Skip(int bytes);
	void SetPos(int pos);
};

