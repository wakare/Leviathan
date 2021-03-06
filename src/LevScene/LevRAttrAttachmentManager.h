#pragma once
#include "LevSceneRenderAttribute.h"
#include <vector>
#include "LSPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevAttachment;

		class LevRAttrAttachmentManager : public LevSceneRenderAttribute
		{
		public:
			LevRAttrAttachmentManager();
			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrAttachmentManager);

			RenderAttributeType GetRenderAttributeType() const override { return ERAT_ATTACHMENT_MANAGER; }

			void AddAttachment(LSPtr<LevAttachment> attachment);
			const std::vector<LSPtr<LevAttachment>>& GetAttachments() const;

		private:
			std::vector<LSPtr<LevAttachment>> m_attachments;
		};
	}
}
