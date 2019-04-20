#pragma once

#include <map>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class OpenGLObject;
		class OpenGLLight;
		class OpenGLCamera;

		typedef int OpenGLResourceHandle;
		class OpenGLResourceMgr
		{
		public:
			OpenGLResourceMgr();

			bool AddGLObject(OpenGLResourceHandle handle, LPtr<OpenGLObject> pObject);
			bool AddLight(OpenGLResourceHandle handle, LPtr<OpenGLLight> pLight);
			bool AddCamera(OpenGLResourceHandle handle, LPtr<OpenGLCamera> pCamera);

			bool RemoveResource(OpenGLResourceHandle handle);

		private:
			bool _removeObject(OpenGLResourceHandle handle);
			bool _removeLight(OpenGLResourceHandle handle);
			bool _removeCamera(OpenGLResourceHandle handle);

			std::map<OpenGLResourceHandle, LPtr<OpenGLObject>> m_objects;
			std::map<OpenGLResourceHandle, LPtr<OpenGLLight>> m_lights;
			std::map<OpenGLResourceHandle, LPtr<OpenGLCamera>> m_cameras;
		};
	}
}