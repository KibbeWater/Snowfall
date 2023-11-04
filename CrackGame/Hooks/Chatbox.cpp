#include "pch.h"

void __stdcall Hook::Chatbox::hkSendMsg(Chatbox_o* pThis, Unity::System_String* message, const MethodInfo* pMethod) {
	static auto oSendMessage = static_cast<decltype(&hkSendMsg)>(pSendMsg);

	//GameAPI::AppendMessage(GameAPI::GetSteamID(), message, IL2CPP::String::New("You"));
	//GameAPI::SendChatMessage(message->ToString());

	oSendMessage(pThis, message, pMethod);
}
