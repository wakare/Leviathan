#pragma once
#include "LevSceneRenderAttribute.h"
#include <vector>
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevAttachment;

		class LevRAttrAttachmentManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrAttachmentManager();
			void AddAttachment(LPtr<LevAttachment> attachment);
			const std::vector<LPtr<LevAttachment>>& GetAttachments() const;

		private:
			std::vector<LPtr<LevAttachment>> m_attachments;
		};
	}
}
