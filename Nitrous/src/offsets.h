#pragma once

#include "pch.h"

namespace localPlayer
{
	std::vector<unsigned int> health{ 0xF8 };
	std::vector<unsigned int> armor{ 0xFC };
	std::vector<unsigned int> currentAmmo{ 0x374, 0x14, 0x0 };
	std::vector<unsigned int> grendade{ 0x158 };
}