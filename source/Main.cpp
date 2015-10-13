#include "Pch.hpp"
#include "Application.hpp"

#ifdef SFML_SYSTEM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <iostream>

bool ensureUserDirectory();

int main()
{
	// Check is user directory if is existent, create it if not!
	if (!ensureUserDirectory())
	{
		std::cerr << "Failed to create user directory" << std::endl;
		return -1;
	}

	// Try to read the configuration
	Configuration config{ "user/config.json" };
	if (!config.load()) return -1;

	auto app{ std::make_unique<Application>(config) };
	app->run();

	return config.save() ? 0 : -1;
}

bool ensureUserDirectory()
{
#ifdef SFML_SYSTEM_WINDOWS
	auto dwAttrib{ GetFileAttributesW(L"user") };
	if (dwAttrib == INVALID_FILE_ATTRIBUTES) return CreateDirectoryA("user", nullptr) == 1;
	return true;
#else
	return mkdir("user", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
#endif
}