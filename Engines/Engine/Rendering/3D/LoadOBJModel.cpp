#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVerticies(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material()){
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVerticies.reserve(200);
	subMeshes.reserve(200);
}

LoadOBJModel::~LoadOBJModel(){
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVerticies.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_){
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes(){
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing(){
	for (unsigned int i = 0; i < indices.size() ; i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVerticies.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVerticies;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVerticies.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_){
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;

	glm::vec3 maxVertX, maxVertY, minVertX, minVertY;
	maxVertX = maxVertY = minVertX = minVertY = glm::vec3();

	while (std::getline(in, line)) {		

		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

			glm::vec3 vertex = vertices.back();

			//Get boundginBox verticies
			if (vertex.x > maxVertX.x){
				maxVertX = vertex;
			}
			if(vertex.x < minVertX.x){
				minVertX = vertex;
			}
			if (vertex.y > maxVertY.y) {
				maxVertY = vertex;
			}
			if (vertex.y < minVertY.y) {
				minVertY = vertex;
			}
		}
		//NORMAL DATA
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//TEXTURE DATA
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		//FACE DATA
		else if (line.substr(0, 2) == "f ") {
			std::stringstream v(line.substr(2));
			unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
			char useless;

			//Tried to format this, this was the only solution i could find so the "/" in the face data doesnt get in the way
			v >> vertexIndex[0] >> useless >> textureIndex[0] >> useless >> normalIndex[0]
			  >> vertexIndex[1] >> useless >> textureIndex[1] >> useless >>  normalIndex[1]		
			  >> vertexIndex[2] >> useless >> textureIndex[2] >> useless >> normalIndex[2];

			//Subtract by 1 here so i can have the correct position in the vector
			indices.push_back(vertexIndex[0] - 1);
			indices.push_back(vertexIndex[1] - 1);
			indices.push_back(vertexIndex[2] - 1);
			textureIndices.push_back(textureIndex[0] - 1);
			textureIndices.push_back(textureIndex[1] - 1);
			textureIndices.push_back(textureIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
		
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_){
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_){
	MaterialLoader::LoadMaterial(matFilePath_);
}
