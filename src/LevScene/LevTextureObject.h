#pragma once

#include "LevAttachment.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevTextureObject : public LevAttachment
		{
		public:
			LevTextureObject(unsigned width, unsigned height, LPtr<RAIIBufferData> data, const std::string& texture_uniform_name);
			unsigned GetID() const;
			unsigned GetWidth() const;
			unsigned GetHeight() const;

			const void* GetTextureData() const;
			const std::string& GetTextureUniformName() const;

		private:
			const unsigned m_id;
			
			const unsigned m_width;
			const unsigned m_height;

			const std::string m_texture_unifrom_name;
			LPtr<RAIIBufferData> m_texture_data;
		};
	}

}


