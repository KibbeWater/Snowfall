#include "pch.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* ofs = static_cast<std::ofstream*>(userp);
    size_t totalSize = size * nmemb;
    ofs->write(static_cast<const char*>(contents), totalSize);
    return totalSize;
}

std::string FS::GetCheatPath() {
    // Retrieve the %appdata% directory path
    char* appdataPath = nullptr;
    size_t len = 0;

    if (_dupenv_s(&appdataPath, &len, "APPDATA") != 0 || appdataPath == nullptr) {
        throw std::runtime_error("Failed to get APPDATA environment variable.");
    }

    // Construct the target directory path: %appdata%\Snowfall
    std::string snowfallPath = std::string(appdataPath) + "\\Snowfall\\CrabGame";
    free(appdataPath); // Free the memory allocated by _dupenv_s

    // Ensure the directory exists
    std::filesystem::create_directories(snowfallPath);

    return snowfallPath;
}

std::string FS::GetAsset(std::string filename)
{
	auto path = GetCheatPath() + "\\assets";
    std::filesystem::create_directories(path);
    return path + (filename.empty() ? "" : ("\\" + filename));
}

std::string FS::GetLuaFile(std::string filename)
{
	auto path = GetCheatPath() + "\\lua";
	std::filesystem::create_directories(path);
    return path + (filename.empty() ? "" : ("\\" + filename));
}

std::string FS::GetConfig(std::string filename)
{
	auto path = GetCheatPath() + "\\config";
	std::filesystem::create_directories(path);
	return path + (filename.empty() ? "" : ("\\" + filename));
}

bool FS::DownloadAsset(std::string url, std::string filename, bool ignoreExisting)
{
	auto path = GetAsset(filename);

	if (!ignoreExisting && std::filesystem::exists(path)) {
		return true;
	}

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL\n";
        return false;
    }

    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) {
        std::cerr << "Failed to open output file\n";
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ofs);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << "\n";
        return false;
    } else {
		std::cout << "[Asset] Downloaded " << filename << " successfully" << std::endl;
    }

    curl_easy_cleanup(curl);
    ofs.close();

    return true;
}
