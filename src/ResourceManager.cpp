#include "ResourceManager.h"

ResourceManager* ResourceManager::mInstance = nullptr;

ResourceManager* ResourceManager::getInstance()
{
	if (mInstance == nullptr)
		mInstance = new ResourceManager();
	return mInstance;
}

void ResourceManager::AddAssetToQueue(Asset * asset)
{
	assetQueue.push_back(asset);
}

void ResourceManager::loadAssetQueue()
{
	for (auto& asset : assetQueue)
	{
		loadAsset(asset);
	}
}
void ResourceManager::loadAsset(Asset* asset)
{
	ShaderData * shaderAsset = dynamic_cast<ShaderData*>(asset);
	ModelData * modelAsset = dynamic_cast<ModelData*>(asset);
	TextureLoadingData * textureData = dynamic_cast<TextureLoadingData*>(asset);
	TextData * textData = dynamic_cast<TextData*>(asset);
	SpriteData * spriteData = dynamic_cast<SpriteData*>(asset);
	m_currentAsset = asset->getKey();
	m_assetsLoaded++;

	if (shaderAsset)
	{
		LoadShader(shaderAsset->m_vertexShaderDir, shaderAsset->m_fragShaderDir, shaderAsset->m_geoShaderDir, shaderAsset->getKey());
	}
	if (modelAsset)
	{
		LoadModel(modelAsset->m_modelDir, modelAsset->getKey());
	}
	if (textureData)
	{
		LoadTexture(textureData->m_textureDir, textureData->getKey(), textureData->m_position);
	}
	if (textData)
	{
		LoadText(textData->m_message, textData->getKey(), textData->m_fontSize, textData->m_position, textData->m_color);
	}
	if (spriteData)
	{
		LoadSprite(spriteData->m_file, spriteData->m_alpha, spriteData->getKey());
	}
	cout << m_currentAsset << endl;
}

void ResourceManager::SetUp(SDL_Renderer* m_renderer)
{
	sdl_renderer = m_renderer;
}

Shader ResourceManager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}
Shader ResourceManager::GetShader(string name)
{
	return shaders[name];
}

void ResourceManager::LoadSprite(const GLchar * file, GLboolean alpha,std::string name)
{
	sprites[name] = LoadSpriteFromFile(file, alpha);
}

Textures ResourceManager::GetSprite(string name)
{
	return sprites[name];
}

void ResourceManager::LoadTexture(const GLchar * file, std::string name, glm::vec2 pos)
{
	textures[name] = loadTextureFromFile(file, pos);
}
SDL_Texture* ResourceManager::GetTexture(string name)
{
	return textures[name].tex;
}
SDL_Rect ResourceManager::GetTextureRect(string name)
{
	return textures[name].texRect;
}


void ResourceManager::LoadText(string message, string name, int fontSize, glm::vec2 pos, glm::vec4 color)
{
	textObjects[name] = CreateText(message, fontSize, pos,color);
}
SDL_Texture* ResourceManager::GetText(string name)
{
	return textObjects[name].tex;
}
SDL_Rect ResourceManager::GetTextRect(string name)
{
	return textObjects[name].texRect;
}

TextureData ResourceManager::loadTextureFromFile(const GLchar* path, glm::vec2 pos)
{
	gMenuImage = IMG_Load(path);

	if (gMenuImage == NULL)
	{
		cout << SDL_GetError() << endl;
	}

	backGroundTex = SDL_CreateTextureFromSurface(sdl_renderer, gMenuImage);

	SDL_QueryTexture(backGroundTex, NULL, NULL, &w, &h);

	texr.x = pos.x; texr.y = pos.y; texr.w = w; texr.h = h;

	TextureData texDat;
	texDat.tex = backGroundTex;
	texDat.texRect = texr;

	return texDat;
}

TextureData ResourceManager::CreateText(std::string message, int fontSize, glm::vec2 pos,glm::vec4 c)
{
	SDL_Texture* newTexture = NULL;
	
	TTF_Init();
	TTF_Font* m_font = NULL;
	m_font = TTF_OpenFont("font.ttf", fontSize);

	SDL_Surface *surf = TTF_RenderText_Blended(m_font, message.c_str(), SDL_Color{ (Uint8)c.x, (Uint8)c.y, (Uint8)c.z, (Uint8)c.w });

	newTexture = SDL_CreateTextureFromSurface(sdl_renderer, surf);

	SDL_QueryTexture(newTexture, NULL, NULL, &w, &h);

	texr.x = pos.x; texr.y = pos.y; texr.w = w; texr.h = h;

	SDL_FreeSurface(surf);

	TTF_CloseFont(m_font);

	TextureData texDat;
	texDat.tex = newTexture;
	texDat.texRect = texr;

	return texDat;
}


void ResourceManager::LoadModel(string path, string name)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << import.GetErrorString() << endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of("\\"));
	this->processNode(scene->mRootNode, scene, name);
	meshVal = 0;

	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		MeshData m;
		m.indices.insert(m.indices.end(),meshes[i].indices.begin(), meshes[i].indices.end());
		m.vertexes.insert(m.vertexes.end(), meshes[i].vertices.begin(), meshes[i].vertices.end());
		m.textures.insert(m.textures.end(), meshes[i].textures.begin(), meshes[i].textures.end());

		meshData = m;
		BuildMesh(name);	
	}

	meshData.indices.clear();
	meshData.vertexes.clear();
	meshData.textures.clear();

	meshes.clear();
}

void ResourceManager::processNode(aiNode * node, const aiScene * scene, string name)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene, name));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene, name);
	}
}

Mesh ResourceManager::processMesh(aiMesh * mesh, const aiScene * scene, string name)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;

		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());		

		vector<Texture> emissionMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "texture_emissive");
		textures.insert(textures.end(), emissionMaps.begin(), emissionMaps.end());

		vector<Texture> bumpMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_bump");
		textures.insert(textures.end(), bumpMaps.begin(), bumpMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

void ResourceManager::BuildMesh(string name)
{
	Mesh builtMesh = Mesh(meshData.vertexes, meshData.indices, meshData.textures);
	madeMeshes[name].push_back(builtMesh);
}

vector<Mesh> ResourceManager::GetMesh(string name)
{
	return madeMeshes[name];
}

void ResourceManager::Clear()
{
	for (auto iter : shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
}

GLuint ResourceManager::GetTextureID(string name)
{
	GLuint temp = textureList[name];
	return temp;
}

Shader ResourceManager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	string vertexCode;
	string fragmentCode;
	string geometryCode;

	try
	{
		ifstream vertexShaderFile(vShaderFile);
		ifstream fragmentShaderFile(fShaderFile);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr)
		{
			ifstream geometryShaderFile(gShaderFile);
			stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (exception e)
	{
		string s = fShaderFile;
		cout << "ERROR::SHADER: Failed to read shader files" + s << endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();;

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

	return shader;
}

vector<Texture> ResourceManager::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	GLuint h = mat->GetTextureCount(type);

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;

		for (GLuint j = 0; j < textures_loaded.size(); j++)
		{
			if (textures_loaded[j].path == str)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{

			Texture tex;
			tex.id = textureFromFile(str.C_Str(), this->directory);
			tex.type = typeName;
			tex.path = str;
			//textureList.push_back
			textures.push_back(tex);
			this->textures_loaded.push_back(tex);
		}
	}
	return textures;
}

GLuint ResourceManager::textureFromFile(const char * path, string directory)
{
	string filename = string(path);
	filename = directory + '\\' + filename;

	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}
void ResourceManager::LoadTextureMesh(const char * path,string name)
{
	string filename = string(path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	textureList[name] = textureID;

}

Textures ResourceManager::LoadSpriteFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Textures texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}