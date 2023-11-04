#include "pch.h"

static Vector3* prevPos = nullptr;
static ULONGLONG prevTick = GetTickCount64();
static float maxAccelerationThreshold = 500.0;

void __stdcall Hook::ClientSend::hkPlayerPosition(UnityEngine_Vector3_o* position, uint64_t toId, const MethodInfo* pMethod) {
	static auto oPlayerPosition = static_cast<decltype(&hkPlayerPosition)>(pPlayerPosition);
		

	if ((!(G::bRedLightFreeze && F::bRedGreenProtection) || !F::bRedGreenProtection) && !F::bLagSwitch) {
		if (!G::vPositionOverrideQueue.empty()) {
			auto pos = G::vPositionOverrideQueue[0]->ToEngine();
			G::vPositionOverrideQueue.pop_back();

			position = &pos;
		}

		if (F::bAdvancedAntiKB) {
			auto playerPos = new Vector3(*position);

			ULONGLONG currentTick = GetTickCount64();
			float deltaTime = static_cast<float>(currentTick - prevTick) / 6000.0f;

			if (prevPos && deltaTime > 0.0f) {
				float deltaDistance = playerPos->distanceTo(*prevPos);
				float acceleration = deltaDistance / (deltaTime * deltaTime);

				// if (F::bDebug) 
					// GameAPI::Log("New Pos (" + std::to_string(acceleration) + "): " + std::to_string(position->fields.x) + ", " + std::to_string(position->fields.y) + ", " + std::to_string(position->fields.z));

				if (acceleration > maxAccelerationThreshold) {
					GameAPI::Teleport(prevPos->ToEngine());
				}
			}

			prevPos = playerPos;
			prevTick = currentTick;
		}

		if (F::bGodmode)
			position->fields.y = std::max(position->fields.y, G::fKillHeight);

		oPlayerPosition(position, toId, nullptr);
	}
}

void __stdcall Hook::ClientSend::hkPlayerRotation(float x, float y, uint64_t toId, const MethodInfo* pMethod)
{
	static auto oPlayerRotation = static_cast<decltype(&hkPlayerRotation)>(pPlayerRotation);

	if ((!(G::bRedLightFreeze && F::bRedGreenProtection) || !F::bRedGreenProtection) && !F::bLagSwitch)
		oPlayerRotation(x, y, toId, pMethod);
}

void __stdcall Hook::ClientSend::hkDamagePlayer(long hurtPlayerId, int damage, UnityEngine_Vector3_o* damageDir, int itemID, int objectID, const MethodInfo* pMethod)
{
	static auto oDamagePlayer = static_cast<decltype(&hkDamagePlayer)>(pDamagePlayer);

	if (G::bAnticheatDisabler && (itemID == WEAPON_RIFLE || itemID == WEAPON_SHOTGUN))
		return;

	oDamagePlayer(hurtPlayerId, damage, damageDir, itemID, objectID, pMethod);
}

void __stdcall Hook::ClientSend::hkUseItem(int itemID, UnityEngine_Vector3_o* dir, const MethodInfo* pMethod)
{
	static auto oUseItem = static_cast<decltype(&hkUseItem)>(pUseItem);

	if (G::bAnticheatDisabler && (itemID == WEAPON_RIFLE || itemID == WEAPON_SHOTGUN))
		return;

	oUseItem(itemID, dir, pMethod);
}

void __stdcall Hook::ClientSend::hkSendChatMessage(System_String_o* message, const MethodInfo* pMethod) {
	static auto oSendChatMessage = HOOK_ORIG_FUNC(SendChatMessage);

	std::string msg = reinterpret_cast<Unity::System_String*>(message)->ToString();
	if (F::bCommandHandler)
		if (G::commandHandler->HandleCommand(msg)) // Should block?
			return;

	return oSendChatMessage(message, pMethod);
}
