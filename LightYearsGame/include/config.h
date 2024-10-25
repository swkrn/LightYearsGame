#pragma once
#include <string>

std::string GetResouceRir()
{
#ifdef NDEBUG // release build
    return "assets/";
#else
    return "Y:/tutorials/cpp_game/LightYears/LightYearsGame/assets/";
#endif
}
