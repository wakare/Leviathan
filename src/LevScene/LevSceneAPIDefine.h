#pragma once

#ifdef LEV_SCENE_API_EXPORT
#define LEV_SCENE_API __declspec(dllexport)
#else
#define LEV_SCENE_API __declspec(dllimport)
#endif