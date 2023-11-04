#pragma once

namespace Hook
{
	namespace Chatbox
	{
		inline void* pSendMsg;
		void __stdcall hkSendMsg(Chatbox_o* pThis, Unity::System_String* message, const MethodInfo* pMethod);
	}
}