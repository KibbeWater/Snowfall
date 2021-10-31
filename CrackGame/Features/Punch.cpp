#include "Punch.h"

punchOriginal punchPlayerOriginal = NULL;

void __stdcall PunchPlayers__Punch(PunchPlayers_o* thisClass, const MethodInfo* method) {

	thisClass->fields.ready = true;
}

void Punch::Init() {
	MH_CreateHook();
}