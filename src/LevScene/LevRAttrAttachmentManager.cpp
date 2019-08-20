#include "LevRAttrAttachmentManager.h"
#include "LevAttachment.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrAttachmentManager::LevRAttrAttachmentManager()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		void LevRAttrAttachmentManager::AddAttachment(LPtr<LevAttachment> attachment)
		{
			m_attachments.push_back(attachment);
		}

		const std::vector<LPtr<LevAttachment>>& LevRAttrAttachmentManager::GetAttachments() const
		{
			return m_attachments;
		}
	}
}