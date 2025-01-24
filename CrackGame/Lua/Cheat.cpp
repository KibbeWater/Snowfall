#include "pch.h"

void Cheat::on(Callbacks::Event event, const sol::protected_function& func) {
    G::oCallbackManager->register_callback(event, func);
}

bool Cheat::getBool(std::string path, bool defaultValue) {
	return Config::get(path, defaultValue);
}

std::string Cheat::getString(std::string path, std::string defaultValue) {
	return Config::get(path, defaultValue);
}

int Cheat::getInt(std::string path, int defaultValue) {
	return Config::get(path, defaultValue);
}

float Cheat::getFloat(std::string path, float defaultValue) {
	return Config::get(path, defaultValue);
}

void Cheat::setBool(std::string path, bool value) {
	auto cfg = Config::getConfig(path, value);
	*cfg = value;
}

void Cheat::setString(std::string path, std::string value) {
	auto cfg = Config::getConfig(path, value);
	*cfg = value;
}

void Cheat::setInt(std::string path, int value) {
	auto cfg = Config::getConfig(path, value);
	*cfg = value;
}

void Cheat::setFloat(std::string path, float value) {
	auto cfg = Config::getConfig(path, value);
	*cfg = value;
}
