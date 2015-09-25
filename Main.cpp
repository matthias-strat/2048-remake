#include "stdafx.h"
#include "Application.hpp"

int main()
{
	auto app{ std::make_unique<Application>() };
	app->run();
	return 0;
}