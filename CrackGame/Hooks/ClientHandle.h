#pragma once

namespace Hook {
	namespace ClientHandle {
		inline void* pTagPlayer;
		void __stdcall hkTagPlayer(Packet_o* packet, const MethodInfo* pMethod);

		inline void* pPlayerPosition;
		void __stdcall hkPlayerPosition(Packet_o* packet, const MethodInfo* pMethod);
	}
}