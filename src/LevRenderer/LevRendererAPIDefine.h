#pragma once

#ifdef LEV_RENDERER_API_EXPORT
#define LEV_RENDERER_API __declspec(dllexport)
#else
#define LEV_RENDERER_API __declspec(dllimport)
#endif