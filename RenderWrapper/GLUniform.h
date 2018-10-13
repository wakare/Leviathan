#pragma once

#include <gl/glew.h>
#include <string>
#include <memory>

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

class GLUniform
{
	enum UniformType 
	{
		TYPE_FLOAT_MAT4 = GL_FLOAT_MAT4, 
	};

public:
	GLUniform(const char* uniformName, UniformType type);

	bool SetData(float* data, unsigned dataArrayCount);
	bool SetData(double* data, unsigned dataArrayCount);

	bool SetUniformVar(GLuint program);
private:
	bool _checkDataInited();

	const char* m_uniformName;
	UniformType m_uniformType;

	std::shared_ptr<UniformArray<float>> m_fUniformArray;
	std::shared_ptr<UniformArray<double>> m_dUniformArray;
};