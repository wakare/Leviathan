#pragma once

#include "LPtr.h"
#include "LevSceneAPIDefine.h"
#include <map>

namespace Leviathan
{
	namespace Scene
	{
		enum LevFrameAttachmentType
		{
			ELFAT_COLOR_ATTACHMENT0		= 0x1,
			ELFAT_COLOR_ATTACHMENT1		= 0x2,
			ELFAT_COLOR_ATTACHMENT2		= 0x4,
			ELFAT_COLOR_ATTACHMENT3		= 0x8,
			ELFAT_COLOR_ATTACHMENT4		= 0x16,
			ELFAT_COLOR_ATTACHMENT5		= 0x32,
			ELFAT_COLOR_ATTACHMENT6		= 0x64,
			ELFAT_COLOR_ATTACHMENT7		= 0x128,
			ELFAT_DEPTH_ATTACHMENT0		= 0x256,
			ELFAT_STENCIL_ATTACHMENT0	= 0x512,
		};

		class LevAttachment;

		class LEV_SCENE_API LevFrameBufferObject
		{
		public:
			LevFrameBufferObject();

			unsigned GetID() const;
			bool Attach(LevFrameAttachmentType attach_type, LPtr<LevAttachment> attachment);
			const std::map<LevFrameAttachmentType, LPtr<LevAttachment>>& GetAttachments() const;

		private:
			const unsigned m_id;
			std::map<LevFrameAttachmentType, LPtr<LevAttachment>> m_attachments;
		};
	}

}


