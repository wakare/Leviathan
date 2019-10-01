#pragma once

#include "LevAttachment.h"
#include "LevSceneAPIDefine.h"
#include "LSPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		enum LevTextureType
		{
			ELTT_1D_COLOR_TEXTURE,
			ELTT_2D_COLOR_TEXTURE,
			ELTT_2D_DEPTH_TEXTURE,
			ELTT_3D_COLOR_TEXTURE,
			ELTT_CUBEMAP_COLOR_TEXTURE,
		};

		class LEV_SCENE_API LevTextureObject : public LevAttachment
		{
		public:
			LevTextureObject(LevTextureType texture_type, unsigned width, unsigned height, unsigned depth, LSPtr<RAIIBufferData> data);
			
			unsigned GetID() const;
			unsigned GetWidth() const;
			unsigned GetHeight() const;
			unsigned GetDepth() const;

			void SetTextureObjectData(LSPtr<RAIIBufferData> texture_data);
			const RAIIBufferData& GetTextureObjectData() const;

			LevTextureObject* ToLevTextureObject() override;
			LevTextureType GetTextureType() const;
			LevAttachmentType GetAttachmentType() const override;
			const void* GetTextureData() const;

		private:
			const unsigned m_id;
			
			const unsigned m_width;
			const unsigned m_height;
			const unsigned m_depth;

			const LevTextureType m_texture_type;
			LSPtr<RAIIBufferData> m_texture_data;
		};
	}

}


