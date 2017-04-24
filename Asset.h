#pragma once
#include <string>
#include <functional>

using namespace std;

struct Asset
{
public:
	Asset(string key) : m_key(key)
	{

	}

	virtual string getKey()
	{
		return m_key;
	}

protected:
	string m_key;

};

struct ShaderData : Asset
{
	ShaderData(const GLchar * vertexShader, const GLchar * fragShader, const GLchar * geoShader,string key) : Asset(key), m_vertexShaderDir(vertexShader), m_fragShaderDir(fragShader), m_geoShaderDir(geoShader)
	{

	}

	const GLchar * m_vertexShaderDir, *m_fragShaderDir, *m_geoShaderDir;
};

struct ModelData : Asset
{
	ModelData(string modelDir, string key) : Asset(key), m_modelDir(modelDir)
	{

	}

	string m_modelDir;
};

struct TextureLoadingData : Asset
{
	TextureLoadingData(const GLchar *  textureDir, string key, glm::vec2 position) : Asset(key), m_textureDir(textureDir), m_position(position)
	{

	}

	const GLchar *  m_textureDir;
	glm::vec2 m_position;
};

struct TextData : Asset
{
	TextData(string message, string key, int fontSize, glm::vec2 position, glm::vec4 color) : Asset(key), m_message(message), m_fontSize(fontSize), m_position(position),m_color(color)
	{

	}

	string m_message;
	int m_fontSize;
	glm::vec2 m_position;
	glm::vec4 m_color;
};

struct TextureMeshData : Asset
{
	TextureMeshData(string dir, string key) : Asset(key), m_meshDir(dir)
	{

	}

	string m_meshDir;
};

struct SpriteData : Asset
{
	SpriteData(const GLchar *file, GLboolean alpha,string key) : Asset(key),m_file(file),m_alpha(alpha)
	{

	}
	const GLchar *m_file;
	GLboolean m_alpha;
};

