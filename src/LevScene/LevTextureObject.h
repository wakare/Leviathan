#pragma once

#include "LevAttachment.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevTextureType
		{
			ELTT_1D_TEXTURE,
			ELTT_2D_TEXTURE,
			ELTT_3D_TEXTURE
		};

		class LevTextureObject : public LevAttachment
		{
		public:
			LevTextureObject(LevTextureType texture_type, unsigned width, unsigned height, unsigned depth, LPtr<RAIIBufferData> data, const std::string& texture_uniform_name);
			
			unsigned GetID() const;
			unsigned GetWidth() const;
			unsigned GetHeight() const;
			unsigned GetDepth() const;

			LevTextureObject* ToLevTextureObject() override;

			LevTextureType GetTextureType() const;

			const void* GetTextureData() const;
			const std::string& GetTextureUniformName() const;

		private:
			const unsigned m_id;
			
			const unsigned m_width;
			const unsigned m_height;
			const unsigned m_depth;

			const LevTextureType m_texture_type;

			const std::string m_texture_uniform_name;
			LPtr<RAIIBufferData> m_texture_data;
		};
	}

}


