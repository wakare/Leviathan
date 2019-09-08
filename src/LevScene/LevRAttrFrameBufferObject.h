#pragma once
#include "LevSceneRenderAttribute.h"
#include "LSPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevFrameBufferObject;

		class LEV_SCENE_API LevRAttrFrameBufferObject : public LevSceneRenderAttribute
		{
		public:
			LevRAttrFrameBufferObject();
			bool SetFrameBufferObject(LSPtr<LevFrameBufferObject> frame_buffer_object);
			LSPtr<LevFrameBufferObject> GetFrameBufferObject() const;

		private:
			LSPtr<LevFrameBufferObject> m_frame_buffer_object;
		};
	}
}