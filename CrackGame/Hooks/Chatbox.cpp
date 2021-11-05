#include "pch.h"

std::initializer_list<int> s = { 0x48, 0x31, 0xC9, 0x48, 0x85, 0xC9, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

void __stdcall Hook::Chatbox::hkSendMessage(Chatbox_o* pThis, System_String_o* message, const MethodInfo* pMethod)
{
	static auto oSendMessage = static_cast<decltype(&hkSendMessage)>(pSendMessage);
	static auto profanityFilterAddr = MEM::PatternScan("GameAssembly.dll", "48 8B 15 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 84 C0 74 4D");
	
	static bool filterOff = false;
	static bool shouldBeOn = true;
	if (filterOff != shouldBeOn && shouldBeOn) {
		for (size_t i = 0; i < s.size(); i++)
		{
			
		}
	} else if (filterOff != shouldBeOn && !shouldBeOn) {

	}

	oSendMessage(pThis, message, pMethod);
}
