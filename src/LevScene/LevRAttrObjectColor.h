#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevObjectColorType
		{
			ELOCT_PURE_COLOR = 0,
			ELOCT_COLOR_ARRAY = 1,
			ELOCT_UNKNOWN = 100,
		};

		struct LevObjectColorData
		{
			float pure_color[3];
			float* color_array;
			unsigned color_array_byte_size;

			LevObjectColorData()
				: color_array(nullptr)
				, color_array_byte_size(0)
			{

			}

			~LevObjectColorData()
			{
				if (color_array)
				{
					delete[] color_array;
					color_array = nullptr;
				}
			}
		}; 

		class LevRAttrObjectColor : public LevSceneRenderAttribute
		{
		public:
			LevRAttrObjectColor(LevObjectColorType type, LPtr<LevObjectColorData> pColorData);
			~LevRAttrObjectColor();

			const LevObjectColorType& GetColorType() const;
			void SetColorType(LevObjectColorType type);

			const LevObjectColorData& GetColorData() const;
			LevObjectColorData& GetColorData();

		private:
			LevObjectColorType m_colorType;
			LPtr<LevObjectColorData> m_pColorData;
		};
	}
}