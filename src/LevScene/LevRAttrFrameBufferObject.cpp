#include "LevRAttrFrameBufferObject.h"
#include "LevFrameBufferObject.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrFrameBufferObject::LevRAttrFrameBufferObject()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
			, m_frame_buffer_object(new LevFrameBufferObject)
		{
		}

		bool LevRAttrFrameBufferObject::SetFrameBufferObject(LSPtr<LevFrameBufferObject> frame_buffer_object)
		{
			m_frame_buffer_object = frame_buffer_object;
			return true;
		}

		LSPtr<LevFrameBufferObject> LevRAttrFrameBufferObject::GetFrameBufferObject() const
		{
			return m_frame_buffer_object;
		}
	}
}


