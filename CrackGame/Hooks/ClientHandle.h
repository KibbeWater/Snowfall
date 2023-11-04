#pragma once

namespace Hook {
	namespace ClientHandle {
		inline void* pTagPlayer;
		void __stdcall hkTagPlayer(Packet_o* packet, const MethodInfo* pMethod);
	}
}