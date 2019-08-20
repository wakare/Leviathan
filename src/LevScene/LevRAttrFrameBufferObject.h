#pragma once
#include "LevSceneRenderAttribute.h"
#include "LPtr.h"

namespace Leviathan
{
	namespace Scene
	{
		class LevFrameBufferObject;

		class LEV_SCENE_API LevRAttrFrameBufferObject : public LevSceneRenderAttribute
		{
		public:
			LevRAttrFrameBufferObject();
			bool SetFrameBufferObject(LPtr<LevFrameBufferObject> frame_buffer_object);
			LPtr<LevFrameBufferObject> GetFrameBufferObject() const;

		private:
			LPtr<LevFrameBufferObject> m_frame_buffer_object;
		};
	}
}