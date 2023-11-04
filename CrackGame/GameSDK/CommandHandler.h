#pragma once

struct CommandResult;

typedef CommandResult* (*CommandCallback)(const std::vector<std::string>& args);

struct CommandResult {
	bool result;
	const char* error;
};

struct Command {
	std::string name;
	CommandCallback callback;
};

class CommandHandler {
private:
	std::vector<Command*> commands;
public:
	/*
	* Handles Commands
	* @return Should the outgoing message be blocked?
	*/
	bool HandleCommand(std::string command);

	bool RegisterCommand(std::string name, CommandCallback callback);
	// bool DestroyCommand(std::string name);
	void DestroyAllCommands();

private:
	bool DoesCommandExist(std::string name);

	Command* GetCommand(std::string name);
};

