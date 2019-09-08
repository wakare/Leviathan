#include "LevFrameBufferObject.h"
#include "LevTokenDispatch.h"
#include "LevAttachment.h"

namespace Leviathan
{
	namespace Scene
	{
		LevFrameBufferObject::LevFrameBufferObject()
			: m_id(LevTokenDispatch<LevFrameBufferObject, unsigned>::GetIncrementToken())
		{

		}

		unsigned LevFrameBufferObject::GetID() const
		{
			return m_id;
		}

		bool LevFrameBufferObject::Attach(LevFrameAttachmentType attach_type, LSPtr<LevAttachment> attachment)
		{
			m_attachments[attach_type] = attachment;

			return true;
		}

		const std::map<LevFrameAttachmentType, LSPtr<LevAttachment>>& LevFrameBufferObject::GetAttachments() const
		{
			return m_attachments;
		}
	}	
}

