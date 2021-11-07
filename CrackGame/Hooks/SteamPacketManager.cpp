#include "pch.h"

void __stdcall Hook::SteamPacketManager::hkSendPacket(SteamworksNative_CSteamID_o steamId, Packet_o* p, int32_t p2pSend, int32_t channel, const MethodInfo* method)
{
	static auto oSendPacket = static_cast<decltype(&hkSendPacket)>(pSendPacket);

	auto s = steamId.fields.m_SteamID;

	oSendPacket(steamId, p, p2pSend, channel, method);
}
