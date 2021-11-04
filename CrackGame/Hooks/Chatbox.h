#pragma once

namespace Hook
{
	namespace Chatbox
	{
		inline void* pSendMessage;
		void __stdcall hkSendMessage(Chatbox_o* pThis, System_String_o* message, const MethodInfo* pMethod);
	}
}