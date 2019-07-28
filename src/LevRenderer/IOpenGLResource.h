#pragma once

namespace Leviathan
{
	namespace Renderer
	{
		class IOpenGLUniform;
		class IOpenGLObject;

		class IOpenGLResource
		{
		public:
			virtual ~IOpenGLResource() = default;

			/*
			 * Avoid dynamic conversion
			 */

			virtual IOpenGLUniform* ToOpenGLUniform() { return nullptr; }
			virtual IOpenGLObject* ToOpenGLObject() { return nullptr; }
		};
	}
}