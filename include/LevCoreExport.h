#pragma once

#ifdef LEV_CORE_API_EXPORT
#define LEV_CORE_API __declspec(dllexport)
#else
#define LEV_CORE_API __declspec(dllimport)
#endif