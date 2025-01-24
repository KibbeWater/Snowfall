#pragma once

class Cheat {
public:
    static void on(Callbacks::Event event, const sol::protected_function& func);

	static bool getBool(std::string path, bool defaultValue);
	static std::string getString(std::string path, std::string defaultValue);
	static int getInt(std::string path, int defaultValue);
	static float getFloat(std::string path, float defaultValue);

	static void setBool(std::string path, bool value);
	static void setString(std::string path, std::string value);
	static void setInt(std::string path, int value);
	static void setFloat(std::string path, float value);
};