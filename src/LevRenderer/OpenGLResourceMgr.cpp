#include "OpenGLResourceMgr.h"

namespace Leviathan
{
	namespace Renderer
	{

		OpenGLResourceMgr::OpenGLResourceMgr()
		{

		}

		bool OpenGLResourceMgr::AddGLObject(OpenGLResourceHandle handle, LPtr<OpenGLObject> pObject)
		{
			auto itFind = m_objects.find(handle);
			EXIT_IF_FALSE(itFind == m_objects.end());

			m_objects[handle].push_back(pObject);
			return true;
		}

		bool OpenGLResourceMgr::AddLight(OpenGLResourceHandle handle, LPtr<OpenGLLight> pLight)
		{
			auto itFind = m_lights.find(handle);
			EXIT_IF_FALSE(itFind == m_lights.end());

			m_lights[handle].push_back(pLight);
			return true;
		}

		bool OpenGLResourceMgr::AddCamera(OpenGLResourceHandle handle, LPtr<OpenGLCamera> pCamera)
		{
			auto itFind = m_cameras.find(handle);
			EXIT_IF_FALSE(itFind == m_cameras.end());

			m_cameras[handle].push_back(pCamera);
			return true;
		}

		const std::vector<LPtr<OpenGLObject>>& OpenGLResourceMgr::GetGLObjects(OpenGLResourceHandle handle) const
		{
			auto itFind = m_objects.find(handle);
			LEV_ASSERT(itFind != m_objects.end());
			return itFind->second;
		}

		const std::vector<LPtr<OpenGLLight>>& OpenGLResourceMgr::GetGLLights(OpenGLResourceHandle handle) const
		{
			auto itFind = m_lights.find(handle);
			LEV_ASSERT(itFind != m_lights.end());
			return itFind->second;
		}

		const std::vector<LPtr<OpenGLCamera>>& OpenGLResourceMgr::GetGLCameras(OpenGLResourceHandle handle) const
		{
			auto itFind = m_cameras.find(handle);
			LEV_ASSERT(itFind != m_cameras.end());
			return itFind->second;
		}

		bool OpenGLResourceMgr::RemoveResource(OpenGLResourceHandle handle)
		{
			bool _Object = _removeObject(handle);
			bool _Light = _removeLight(handle);
			bool _Camera = _removeCamera(handle);

			return _Object || _Light || _Camera;
		}

		bool OpenGLResourceMgr::_removeObject(OpenGLResourceHandle handle)
		{
			auto itFind = m_objects.find(handle);
			EXIT_IF_FALSE(itFind != m_objects.end());

			m_objects.erase(itFind);
			return true;
		}

		bool OpenGLResourceMgr::_removeLight(OpenGLResourceHandle handle)
		{
			auto itFind = m_lights.find(handle);
			EXIT_IF_FALSE(itFind != m_lights.end());

			m_lights.erase(itFind);
			return true;
		}

		bool OpenGLResourceMgr::_removeCamera(OpenGLResourceHandle handle)
		{
			auto itFind = m_cameras.find(handle);
			EXIT_IF_FALSE(itFind != m_cameras.end());

			m_cameras.erase(itFind);
			return true;
		}

	}
}
