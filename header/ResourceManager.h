#pragma once
#include <map>
#include<string>

#include <GL/glew.h>
#include <vector>
#include <assimp/Importer.hpp>
#include<assimp/material.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "SDL_image.h"
#include <SOIL.h>
#include "SDL_ttf.h"
#include "Shader.h"
#include "Textures.h"
#include "Mesh.h"
#include "ft2build.h"
#include "Asset.h"
#include "Scene.h"
#include FT_FREETYPE_H



struct MeshData {
	string name;
	vector<Texture> textures;
	vector<Vertex> vertexes;
	vector<GLuint> indices;
};

struct TextureData {
	string name;
	SDL_Texture* tex;
	SDL_Rect texRect;
	GLuint id;
};

class ResourceManager
{
public:
	ResourceManager() { }
	static ResourceManager* getInstance();
	vector<Mesh> meshes;
	string directory;
	void AddAssetToQueue(Asset * asset);
	void loadAssetQueue();
	void loadAsset(Asset * asset);
	int meshVal;

	std::map<std::string, Shader> shaders;

	MeshData meshData;

	std::map<std::string, TextureData> textures;
	std::map<std::string, TextureData> textObjects;
	std::map<std::string, vector<Mesh>> madeMeshes;
	std::map<std::string, Textures> sprites;
	

	std::map < string, GLuint>textureList;

	void SetUp(SDL_Renderer * m_renderer);

	Shader LoadShader(const GLchar* vShaderFile, const GLchar *fShaderFile, const GLchar * gShaderFile, std::string name);
	Shader GetShader(string name);

	void LoadSprite(const GLchar * file, GLboolean alpha, std::string name);
	Textures GetSprite(string name);

	void LoadTexture(const GLchar * file, std::string name, glm::vec2 pos);

	SDL_Texture* GetTexture(string name);
	SDL_Rect GetTextureRect(string name);

	void LoadText(string message, string name, int fontSize, glm::vec2 pos, glm::vec4 color);

	SDL_Texture * GetText(string name);
	SDL_Rect GetTextRect(string name);

	TextureData loadTextureFromFile(const GLchar * path, glm::vec2 pos);
	TextureData CreateText(std::string message, int fontSize, glm::vec2 pos,glm::vec4 color);

	void LoadModel(string path, string name);

	void processNode(aiNode * node, const aiScene * scene, string name);

	Mesh processMesh(aiMesh * mesh, const aiScene * scene, string name);

	void BuildMesh(string name);

	vector<Texture> textures_loaded;

	SDL_Texture* backGroundTex;
	SDL_Texture* buttonTex;
	SDL_Texture* textTexture;

	SDL_Rect texr;
	SDL_Rect buttonTexr;

	int x;
	int y;
	int w;
	int h;

	SDL_Window* m_Win;
	SDL_Renderer* sdl_renderer;
	SDL_Surface* gMenuImage;
	SDL_Surface* gScreenSurface;

	vector<Mesh> GetMesh(string name);
	int m_assetsLoaded = 0;
	void Clear();
	GLuint GetTextureID(string name);
	void LoadTextureMesh(const char * path,string name);
	Textures LoadSpriteFromFile(const GLchar * file, GLboolean alpha);
	vector<Asset *> assetQueue;
private:
	Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	//static Textures loadTextureFromFile(const GLchar *file, GLboolean alpha);
	vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName);
	static ResourceManager* mInstance;
	string m_currentAsset;
	

	GLuint textureFromFile(const char * path, string directory);
	
};
