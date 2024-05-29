#include "pch.h"

void LuaH::initState(sol::state* state) {
	state->open_libraries(sol::lib::base, sol::lib::table, sol::lib::math, sol::lib::string);
	state->set_exception_handler(LuaH::handleError);

	// Register classes
	// Engine.*
	state->new_usertype<Engine>("Engine",
		"Teleport", &Engine::Teleport,
		"GetSteamID", &Engine::GetSteamID,
		"GetPlayers", &Engine::GetPlayers,
		"GetLocalPlayer", &Engine::GetLocalPlayer,
		"WorldToScreen", &Engine::WorldToScreen
	);
	// Chat.*
	state->new_usertype<Chat>("Chat",
		"Log", &Chat::Log
	);
	// Cheat.*
	state->new_usertype<CommandHandler>("Cheat",
		"on", &Cheat::on
	);
	// Lobby.*
	state->new_usertype<Lobby>("Lobby",
		"IsLobbyOwner", &Lobby::IsLobbyOwner,
		"GiveWeapon", &Lobby::GiveWeapon,
		"GiveAllWeapon", &Lobby::GiveAllWeapon
	);
	// Game.*
	state->new_usertype<Game>("Game",
		"GetGameObjects", &Game::GetGameObjects
	);
	// Render.*
	state->new_usertype<Render>("Render",
		"Rect", &Render::Rect,
		"RectFilled", &Render::RectFilled,
		"Triangle", &Render::Triangle,
		"TriangleFilled", &Render::TriangleFilled,
		"Quad", &Render::Quad,
		"QuadFilled", &Render::QuadFilled,
		"Circle", &Render::Circle,
		"CircleFilled", &Render::CircleFilled,
		"Line", &Render::Line,
		"Text", &Render::Text
	);

	// Register structs
	state->new_usertype<PlayerManager>("PlayerManager",
		"GetPosition", &PlayerManager::GetPosition,
		"GetNumber", &PlayerManager::GetNumber,
		"IsDead", &PlayerManager::IsDead,
		"GetName", &PlayerManager::GetName
	);

	state->new_usertype<LocalPlayer>("LocalPlayer",
		"GetPosition", &LocalPlayer::GetPosition,
		"GetNumber", &LocalPlayer::GetNumber,
		"IsDead", &LocalPlayer::IsDead,
		"GetName", &LocalPlayer::GetName
	);

	// Register util classes
	state->new_usertype<Vector3>("Vector3", sol::constructors<Vector3(float,float,float)>(),
		"x", &Vector3::x,
		"y", &Vector3::y,
		"z", &Vector3::z,
		"distance", &Vector3::distanceTo,
		"normalized", &Vector3::normalized,
		"lerp", &Vector3::lerp
	);

	state->new_usertype<Color>("Color", sol::constructors<Color(int,int,int,int)>(),
		"r", &Color::r,
		"g", &Color::g,
		"b", &Color::b,
		"a", &Color::a,
		"FromHSV", &Color::FromHSV,
		"White", &Color::White,
		"Black", &Color::Black
	);

	state->new_usertype<GameObject>("GameObject",
		"SetActive", &GameObject::SetActive,
		"GetActive", &GameObject::GetActive,
		"GetTransform", &GameObject::GetTransform,
		"GetName", &GameObject::GetName
	);

	state->new_usertype<Transform>("Transform",
		"SetPosition", &Transform::SetPosition,
		"GetPosition", &Transform::GetPosition
	);

	// Register enums
	state->new_enum("Event",
		"OnMove", Callbacks::Event::OnMove,
		"HandleMove", Callbacks::Event::HandleMove,
		"Render", Callbacks::Event::Render
	);

	state->new_enum("Weapon",
		"Rifle", WEAPON_RIFLE,
		"Pistol", WEAPON_PISTOL,
		"Revolver", WEAPON_REVOLVER,
		"Shotgun", WEAPON_SHOTGUN,
		"Bat", WEAPON_BAT,
		"Bomb", WEAPON_BOMB,
		"Katana", WEAPON_KATANA,
		"Knife", WEAPON_KNIFE,
		"Pipe", WEAPON_PIPE,
		"Snowball", WEAPON_SNOWBALL,
		"Stick", WEAPON_STICK
	);

	// Other

	// Own implementation of os.time as the library one is unsafe
	state->set_function("GetTime", []() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration);
		return seconds.count();
	});
}

int LuaH::handleError(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
	// L is the lua state, which you can wrap in a state_view if necessary
	// maybe_exception will contain exception, if it exists
	// description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
	std::cout << "An exception occurred in a function, here's what it says ";
	if (maybe_exception) {
		std::cout << "(straight from the exception): ";
		const std::exception& ex = *maybe_exception;
		std::cout << ex.what() << std::endl;
	} else {
		std::cout << "(from the description parameter): ";
		std::cout.write(description.data(), static_cast<std::streamsize>(description.size()));
		std::cout << std::endl;
	}

	std::string desc(description.data(), description.size());
	GameAPI::Log("[LUA Error] " + desc);

	// you must push 1 element onto the stack to be
	// transported through as the error object in Lua
	// note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
	// so we push a single string (in our case, the description of the error)
	return sol::stack::push(L, description);
}
