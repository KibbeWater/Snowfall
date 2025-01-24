#pragma once

enum MenuTab {
    NONE,
    COMBAT,
    VISUAL,
    MOVEMENT,
    GAMEMODE,
    ITEMS,
    LOBBY,
    MISC,
    CONFIG,
};

namespace Menu {
	inline bool bIsOpen = false;
	void Render();
}