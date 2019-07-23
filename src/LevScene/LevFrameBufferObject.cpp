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

		bool LevFrameBufferObject::Attach(LevFrameAttachmentType attach_type, LPtr<LevAttachment> attachment)
		{
			m_attachments[attach_type] = attachment;

			return true;
		}
	}	
}

