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

			ADD_RENDER_ATTRIBUTE_IMPLEMENT(LevRAttrFrameBufferObject);

			RenderAttributeType GetRenderAttributeType() const override { return ERAT_FRAME_BUFFER_OBJECT; }

			bool SetFrameBufferObject(LSPtr<LevFrameBufferObject> frame_buffer_object);
			LSPtr<LevFrameBufferObject> GetFrameBufferObject() const;

		private:
			LSPtr<LevFrameBufferObject> m_frame_buffer_object;
		};
	}
}