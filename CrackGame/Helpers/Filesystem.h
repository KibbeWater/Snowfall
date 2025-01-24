#pragma once

namespace FS {
	std::string GetCheatPath();

	std::string GetAsset(std::string filename);
	std::string GetLuaFile(std::string filename);
	std::string GetConfig(std::string filename);

	bool DownloadAsset(std::string url, std::string filename, bool ignoreExisting = false);
}