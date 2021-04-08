#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "../Graphics/TextureHandler.h"
#include "../Graphics/MaterialHandler.h"
#include <sstream>

class MaterialLoader
{
public:
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	MaterialLoader() = delete;
	~MaterialLoader();

	static void LoadMaterial(std::string filePath_);

private:
	static GLuint LoadTexture(std::string fileName_);
};
#endif