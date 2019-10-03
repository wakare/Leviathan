#pragma once

#include "LevSceneObjectAttribute.h"

namespace Leviathan
{
	namespace Scene
	{
		enum RenderAttributeType
		{
			ERAT_UNKNOWN,
			ERAT_ATTACHMENT_MANAGER,
			ERAT_DEPTH_FUNC,
			ERAT_FRAME_BUFFER_OBJECT,
			ERAT_RENDER_OBJECT_ATTRIBUTE_BINDER,
			ERAT_RENDER_STATE_MANAGER,
			ERAT_SHADER_PROGRAM,
			ERAT_UNIFORM_MANAGER,
			ERAT_VISIBLE,
		};

		class LevRAttrAttachmentManager;
		class LevRAttrDepthFunc;
		class LevRAttrFrameBufferObject;
		class LevRAttrRenderObjectAttribute;
		class LevRAttrRenderStateManager;
		class LevRAttrShaderProgram;
		class LevRAttrUniformManager;
		class LevRAttrVisible;

#define ADD_RENDER_ATTRIBUTE_DECLARE(className)								\
	virtual className * To##className () {return nullptr;};					\
	virtual const className * To##className() const { return nullptr; }		\

#define ADD_RENDER_ATTRIBUTE_IMPLEMENT(className)							\
	virtual className * To##className() {return this;}						\
	virtual const className * To##className() const {return this;}			\

		class LEV_SCENE_API LevSceneRenderAttribute : virtual public LevSceneObjectAttribute
		{
		public:
			LevSceneRenderAttribute();
			virtual ~LevSceneRenderAttribute();

			virtual RenderAttributeType GetRenderAttributeType() const { return ERAT_UNKNOWN; }

			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrAttachmentManager);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrDepthFunc);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrFrameBufferObject);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrRenderObjectAttribute);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrRenderStateManager);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrShaderProgram);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrUniformManager);
			ADD_RENDER_ATTRIBUTE_DECLARE(LevRAttrVisible);
		};
	}
}
