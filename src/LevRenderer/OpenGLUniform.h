#pragma once

#include <gl/glew.h>
#include "LPtr.h"

namespace Leviathan
{
	namespace Renderer
	{
		// RAII Array
		template<typename T>
		class UniformArray
		{
		public:
			UniformArray(unsigned arraySize) { m_data = new T[arraySize]; };
			~UniformArray() { if (m_data) { delete[] m_data; m_data = nullptr; } };

			void SetArrayData(T* data, unsigned dataSize) { memcpy(m_data, data, dataSize); };
			T* GetArraydata() { return m_data; }

		private:
			T* m_data;
		};

		class OpenGLUniform
		{
		public:
			enum UniformType
			{
				TYPE_FLOAT_MAT4 = GL_FLOAT_MAT4,
			};

			OpenGLUniform(const char* uniformName, UniformType type);

			std::string GetUniformName() const;

			bool SetData(float* data, unsigned dataArrayCount);
			bool SetData(double* data, unsigned dataArrayCount);

			bool Apply(GLuint program);
		private:
			bool _checkDataInited();

			std::string m_uniformName;
			UniformType m_uniformType;

			LPtr<UniformArray<float>> m_fUniformArray;
			LPtr<UniformArray<double>> m_dUniformArray;
		};
	}
}