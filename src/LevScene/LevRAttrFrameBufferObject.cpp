#include "LevRAttrFrameBufferObject.h"

namespace Leviathan
{
	namespace Scene
	{
		LevRAttrFrameBufferObject::LevRAttrFrameBufferObject()
			: LevSceneObjectAttribute(ELSOAT_RENDER)
		{
		}

		bool LevRAttrFrameBufferObject::SetFrameBufferObject(LPtr<LevFrameBufferObject> frame_buffer_object)
		{
			m_frame_buffer_object = frame_buffer_object;
			return true;
		}

		LPtr<LevFrameBufferObject> LevRAttrFrameBufferObject::GetFrameBufferObject() const
		{
			return m_frame_buffer_object;
		}
	}
}


