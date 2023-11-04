#include "pch.h"

bool CommandHandler::HandleCommand(std::string command) {
    std::vector<std::string> args = {};

    std::stringstream stream(command);
    std::string word;
    while (stream >> word)
        args.push_back(word);

    if (args.size() <= 0)
        return false;

    std::string cmdArg = args.at(0);
    if (cmdArg.empty() || cmdArg.front() != COMMAND_PREFIX)
        return false;

    std::string commandName = cmdArg.substr(1);
    Command* commandData = GetCommand(commandName);

    if (commandData == nullptr) {
        GameAPI::Log("Command does not exist");
        return true;
    }

    auto commandArgs = args;
    commandArgs.erase(commandArgs.begin());

    auto callback = *commandData->callback;
    CommandResult* ret = callback(commandArgs);

    if (!ret->result)
        GameAPI::Log(ret->error);

    return true;
}

bool CommandHandler::RegisterCommand(std::string name, CommandCallback callback) {
    if (DoesCommandExist(name))
        return false;

    if (callback == nullptr)
        return false;

    Command* cmd = new Command();
    cmd->callback = callback;
    cmd->name = name;

    this->commands.push_back(cmd);

    return true;
}

void CommandHandler::DestroyAllCommands() {
    this->commands.clear();
}   

bool CommandHandler::DoesCommandExist(std::string name) {
    for (auto cmd = this->commands.begin(); cmd != this->commands.end(); ++cmd)
        if (name == (*cmd)->name)
            return true;
    return false;
}

Command* CommandHandler::GetCommand(std::string name) {
    for (auto cmd = this->commands.begin(); cmd != this->commands.end(); ++cmd)
        if (name == (*cmd)->name)
            return *cmd;
    return nullptr;
}
