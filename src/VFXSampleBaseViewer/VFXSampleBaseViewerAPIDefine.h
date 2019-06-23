#pragma once

#ifdef LEV_VFX_SAMPLE_BASE_VIEWER_API_EXPORT
#define LEV_VFX_SAMPLE_BASE_VIEWER_API __declspec(dllexport)
#else
#define LEV_VFX_SAMPLE_BASE_VIEWER_API __declspec(dllimport)
#endif