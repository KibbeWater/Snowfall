#pragma once

namespace LuaH {
	void initState(sol::state* state);
	int handleError(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description);
}