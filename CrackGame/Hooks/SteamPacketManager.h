#pragma once

namespace Hook
{
	namespace SteamPacketManager
	{
		inline void* pSendPacket;
		void __stdcall hkSendPacket(SteamworksNative_CSteamID_o steamId, Packet_o* p, int32_t p2pSend, int32_t channel, const MethodInfo* method);
	}
}