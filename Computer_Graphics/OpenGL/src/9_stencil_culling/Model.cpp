#include "9_stencil_culling/Model.h"

Model::Model(const char* file){
	std::string text = get_file_contents(file);

	JSON = json::parse(text);

	std::string fileStr = std::string(file);
	texPath = fileStr.substr(0, fileStr.find_last_of('/') + 1) + std::string(JSON["buffers"][0]["uri"]);

	Model::file = file;
	data = getData(); // get .bin file content

	traverseNode(0);

}

void Model::Draw(Shader& shader, Camera& camera, 
					glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
					glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
					glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)){
						
	for( unsigned int i = 0; i < meshes.size(); i++){
		meshes[i].Mesh::Draw(shader, camera, matricesMeshes[i]);
	}
}

void Model::loadMesh(unsigned int indMesh){
	// Get all accessor indices
	const char* s_MESHES = "meshes";
	const char* s_PRIMITIVES = "primitives";
	const char* s_ATTRIBUTES = "attributes";
	const char* s_ACCESSORS = "accessors";

	unsigned int posAccInd = JSON[s_MESHES][indMesh][s_PRIMITIVES][0][s_ATTRIBUTES]["POSITION"];
	unsigned int normalAccInd = JSON[s_MESHES][indMesh][s_PRIMITIVES][0][s_ATTRIBUTES]["NORMAL"];
	unsigned int texAccInd = JSON[s_MESHES][indMesh][s_PRIMITIVES][0][s_ATTRIBUTES]["TEXCOORD_0"];
	unsigned int indAccInd = JSON[s_MESHES][indMesh][s_PRIMITIVES][0]["indices"];


	std::vector<float> posVec = getFloats(JSON[s_ACCESSORS][posAccInd]);
	std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
	std::vector<float> normalVec = getFloats(JSON[s_ACCESSORS][normalAccInd]);
	std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
	std::vector<float> texVec = getFloats(JSON[s_ACCESSORS][texAccInd]);
	std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

	std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
	std::vector<GLuint> indices = getIndices(JSON[s_ACCESSORS][indAccInd]);
	std::vector<Texture> textures = getTextures();

	meshes.emplace_back(Mesh(vertices, indices, textures));
}

void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix){
	const char* s_TRANSLATION = "translation";
	const char* s_ROTATION = "rotation";
	const char* s_SCALE = "scale";
	const char* s_MATRIX = "matrix";
	const char* s_MESH = "mesh";
	const char* s_CHILDREN = "children";
	json node = JSON["nodes"][nextNode];

	//get translation if exists
	glm::vec3 translationV = glm::vec3(0.0f, 0.0f, 0.0f);
	if(node.find(s_TRANSLATION) != node.end()){
		float transValues[3];
		for(unsigned int i = 0; i < node[s_TRANSLATION].size(); i++){
			transValues[i] = node[s_TRANSLATION][i];
		}
		translationV = glm::make_vec3(transValues);
	}
	// get rotation if exists
	glm::quat rotationV = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if(node.find(s_ROTATION) != node.end()){
		//GLTF encodes x, y, z, w
		//glm encodes w, x, y, z
		float rotValues[4] = {
			node[s_ROTATION][3],
			node[s_ROTATION][0],
			node[s_ROTATION][1],
			node[s_ROTATION][2]
		};
		rotationV = glm::make_quat(rotValues);
	}
	// get scale if exists
	glm::vec3 scaleV = glm::vec3(1.0f, 1.0f, 1.0f);
	if(node.find(s_SCALE) != node.end()){
		float scaleValues[3];
		for(unsigned int i = 0; i < node[s_SCALE].size(); i++){
			scaleValues[i] = node[s_SCALE][i];
		}
		scaleV = glm::make_vec3(scaleValues);
	}
	// get matrix if exists
	glm::mat4 matNode = glm::mat4(1.0f);
	if(node.find(s_MATRIX) != node.end()){
		float matValues[16];
		for(unsigned int i = 0; i < node[s_MATRIX].size(); i++){
			matValues[i] = node[s_MATRIX][i];
		}
		matNode = glm::make_mat4(matValues);
	}

	glm::mat4 transM = glm::mat4(1.0f);
	glm::mat4 rotM = glm::mat4(1.0f);
	glm::mat4 scaM = glm::mat4(1.0f);

	
	transM = glm::translate(transM, translationV); 
	rotM = glm::mat4_cast(rotationV);
	scaM = glm::scale(scaM, scaleV);
	
	glm::mat4 matNextNode = matrix * matNode * transM * rotM * scaM; //get matrix for next node

	if(node.find(s_MESH) != node.end()){//if node has a mesh
		translationMeshes.emplace_back(translationV);
		rotationsMeshes.emplace_back(rotationV);
		scalesMeshes.emplace_back(scaleV);
		matricesMeshes.emplace_back(matNextNode);

		loadMesh(node[s_MESH]);
	}
	
	if(node.find(s_CHILDREN) != node.end()){
		for(unsigned int i = 0; i < node[s_CHILDREN].size(); i++){
			traverseNode(node[s_CHILDREN][i], matNextNode);
		}
	}


}

std::vector<unsigned char> Model::getData(){
	std::string bytesText;
	bytesText = get_file_contents(texPath.c_str());
	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

std::vector<float> Model::getFloats(json accessor){
	std::vector<float> floatVec;
	
	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	std::string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;
	if(type == "SCALAR") numPerVert = 1;
	else if(type == "VEC2") numPerVert = 2;
	else if(type == "VEC3") numPerVert = 3;
	else if(type == "VEC4") numPerVert = 4;
	else throw std::invalid_argument("Type is invalid(eg. SCALAR, VEC2, VEC3, VEC4)");

	
	unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * numPerVert;
	for(unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; ){
		unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floatVec.emplace_back(value);
	}
	return floatVec;
}

std::vector<GLuint> Model::getIndices(json accessor){
	std::vector<GLuint> indices;

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView.value("byteOffset", 0);

	unsigned int beginningOfData = byteOffset + accByteOffset;
	if(componentType == 5125){ //5125 is UNSIGNED_INT
		for(unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4;){
			unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.emplace_back((GLuint)value);
		}
	}

	else if(componentType == 5123){ // 5123 is UNSIGNED_SHORT
		for(unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2;){
			unsigned char bytes[] = {data[i++], data[i++]};
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.emplace_back((GLuint)value);
		}
	}

	else if(componentType == 5122){ // 5122 is SHORT
		for(unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2;){
			unsigned char bytes[] = {data[i++], data[i++]};
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.emplace_back((GLuint)value);
		}
	}
	return indices;
}


std::vector<Texture> Model::getTextures(){
	std::vector<Texture> textures;
	std::string texRootPath = texPath.substr(0, texPath.find_last_of("/") + 1 );
	for(unsigned int i = 0; i < JSON["images"].size(); i++){
		texPath = texRootPath +  std::string(JSON["images"][i]["uri"]);
		bool skip = false;// if texture has already been loaded
		for(unsigned int j = 0; j < loadedTexName.size(); j++){
			if(loadedTexName[j] == texPath){
				textures.emplace_back(loadedTex[j]);
				skip = true;
				break;
			}
		}

		if(!skip){
			if(texPath.find("baseColor") != std::string::npos || texPath.find("duffuse") != std::string::npos){ // if finds "baseColor" 
				Texture diffuse = Texture(texPath.c_str(), "diffuse", loadedTex.size());
				textures.emplace_back(diffuse);
				loadedTex.emplace_back(diffuse);
				loadedTexName.emplace_back(texPath);
			}
			else if(texPath.find("metallicRoughness") != std::string::npos || texPath.find("specular") != std::string::npos){
				Texture specular = Texture(texPath.c_str(), "specular", loadedTex.size());
				textures.emplace_back(specular);
				loadedTex.emplace_back(specular);
				loadedTexName.emplace_back(texPath);
			}
			
		}
	}

	return textures;
}


std::vector<Vertex> Model::assembleVertices(std::vector<glm::vec3> positions,
									std::vector<glm::vec3> normals,
									std::vector<glm::vec2> texUVs){
	std::vector<Vertex> vertices;
	for(int i = 0; i < positions.size(); i++){
		vertices.emplace_back(
			Vertex{
				positions[i],
				normals[i],
				glm::vec3(1.0f, 1.0f, 1.0f),//color, not used because it varies in 3D models
				texUVs[i]
			}
		);
	}
	return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec){
	std::vector<glm::vec2> vectors;
	for(int i = 0; i < floatVec.size(); ){
		vectors.emplace_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}
	return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec){
	std::vector<glm::vec3> vectors;
	for(int i = 0; i < floatVec.size(); ){
		vectors.emplace_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;	
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec){
	std::vector<glm::vec4> vectors;
	for(int i = 0; i < floatVec.size(); ){
		vectors.emplace_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}
	return vectors;	
}