#pragma once

typedef void(__stdcall* punchOriginal)(PunchPlayers_o* thisClass, const MethodInfo* method);

namespace Punch {
	void Init();
}