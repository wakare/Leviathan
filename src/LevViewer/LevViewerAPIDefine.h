#pragma once

#ifdef LEV_VIEWER_API_EXPORT
#define LEV_VIEWER_API __declspec(dllexport)
#else
#define LEV_VIEWER_API __declspec(dllimport)
#endif