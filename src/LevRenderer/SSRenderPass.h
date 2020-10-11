#pragma once

#include "ISRShader.h"
#include "LSPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		class SSRenderPass
		{
		public:
			SSRenderPass()
				: m_vertexShader(nullptr)
				, m_fragmentShader(nullptr)
			{
				
			}

			bool IsValid() const
			{
				return m_vertexShader.Get() && m_fragmentShader.Get();
			}


		private:
			LSPtr<ISRShaderVertex> m_vertexShader;
			LSPtr<ISRShaderFragment> m_fragmentShader;
		};
	}
}
