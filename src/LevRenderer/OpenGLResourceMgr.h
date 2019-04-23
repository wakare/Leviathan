#pragma once

#include <map>
#include <vector>
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

			const std::vector<LPtr<OpenGLObject>>& GetGLObjects(OpenGLResourceHandle handle) const;
			const std::vector<LPtr<OpenGLLight>>& GetGLLights(OpenGLResourceHandle handle) const;
			const std::vector<LPtr<OpenGLCamera>>& GetGLCameras(OpenGLResourceHandle handle) const;

			bool RemoveResource(OpenGLResourceHandle handle);

		private:
			bool _removeObject(OpenGLResourceHandle handle);
			bool _removeLight(OpenGLResourceHandle handle);
			bool _removeCamera(OpenGLResourceHandle handle);

			std::map<OpenGLResourceHandle, std::vector<LPtr<OpenGLObject>>> m_objects;
			std::map<OpenGLResourceHandle, std::vector<LPtr<OpenGLLight>>> m_lights;
			std::map<OpenGLResourceHandle, std::vector<LPtr<OpenGLCamera>>> m_cameras;
		};
	}
}