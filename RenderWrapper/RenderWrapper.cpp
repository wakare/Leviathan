#include "RenderWrapper.h"
#include <Algorithm>

void RenderWrapper::PreInit()
{
	// Build and compile our shader program
	// Vertex shader
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//// Check for compile time errors
	//GLint success;
	//GLchar infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//// Fragment shader
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//// Check for compile time errors
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//// Link shaders
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//// Check for linking errors
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//// Set up vertex data (and buffer(s)) and attribute pointers
	////GLfloat vertices[] = {
	////  // First triangle
	////   0.5f,  0.5f,  // Top Right
	////   0.5f, -0.5f,  // Bottom Right
	////  -0.5f,  0.5f,  // Top Left 
	////  // Second triangle
	////   0.5f, -0.5f,  // Bottom Right
	////  -0.5f, -0.5f,  // Bottom Left
	////  -0.5f,  0.5f   // Top Left
	////}; 
	//GLfloat vertices[] = {
	//	0.5f,  0.5f, 0.0f,  // Top Right
	//	0.5f, -0.5f, 0.0f,  // Bottom Right
	//	-0.5f, -0.5f, 0.0f,  // Bottom Left
	//	-0.5f,  0.5f, 0.0f   // Top Left 
	//};
	//GLuint indices[] = {  // Note that we start from 0!
	//	0, 1, 3,  // First Triangle
	//	1, 2, 3   // Second Triangle
	//};
	//GLuint VBO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	//// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	//glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO


	//					  // Uncommenting this call will result in wireframe polygons.
	//					  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_bPreInited = true;
}

void RenderWrapper::Render()
{
	if (!m_bPreInited)
	{
		PreInit();
	}

	if (!m_pWindow)
	{
		throw "RenderWrapper::Render() --> Render window is invalid";
		return;
	}

	// Set Global state
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render subProcess
	for (auto& pGLPass : m_GLPasses)
	{
		if (!pGLPass->Init())
		{
			throw "RenderWrapper::Render() --> GLPass Init failed.";
			return;
		}

		pGLPass->Render();
	}

	//glUseProgram(shaderProgram);
	//glBindVertexArray(VAO);
	////glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	
	glfwSwapBuffers(m_pWindow);
}

bool RenderWrapper::AddGLPass(std::shared_ptr<GLPass> _GLPass)
{
	auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), _GLPass);
	if (findResult != m_GLPasses.end())
	{
		return false;
	}

	m_GLPasses.push_back(_GLPass);
	return true;
}

bool RenderWrapper::DelGLPass(std::shared_ptr<GLPass> _GLPass)
{
	auto findResult = std::find(m_GLPasses.begin(), m_GLPasses.end(), _GLPass);
	if (findResult == m_GLPasses.end())
	{
		return false;
	}

	m_GLPasses.erase(findResult);
	return true;
}
