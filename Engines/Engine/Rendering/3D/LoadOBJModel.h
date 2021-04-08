#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include <sstream>
#include "Mesh.h"
#include "../../FX/MaterialLoader.h"

class LoadOBJModel{
public:
	LoadOBJModel();
	~LoadOBJModel();

	void LoadModel(const std::string& objfilePath_, const std::string& mtlFilePath_);
	std::vector<SubMesh> GetSubMeshes();

private:
	void PostProcessing();
	void LoadModel(const std::string& filePath_);
	void LoadMaterial(const std::string& matName_);
	void LoadMaterialLibrary(const std::string& matFilePath_);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<unsigned int> indices, normalIndices, textureIndices;
	std::vector<Vertex> meshVerticies;
	std::vector<SubMesh> subMeshes;
	
	Material currentMaterial;
};

#endif // !LOADOBJMODEL_H