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

		void LevRAttrAttachmentManager::AddAttachment(LSPtr<LevAttachment> attachment)
		{
			m_attachments.push_back(attachment);
		}

		const std::vector<LSPtr<LevAttachment>>& LevRAttrAttachmentManager::GetAttachments() const
		{
			return m_attachments;
		}
	}
}