#pragma once
#include "UI/UIManager.hpp"

namespace Big::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"Image",
		"Animated"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient,
		UserInterface::HeaderType::Image,
		UserInterface::HeaderType::Animated
	};

	inline std::size_t HeaderTypesPosition = 3;

	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};

	inline std::size_t DemoListPos = 0;
}
