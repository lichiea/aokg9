#include "GameObjectFactory.h"

bool GameObjectFactory::init(std::string filename)
{
	std::ifstream in;
	in.open(filename);
	std::string jsonString;
	std::getline(in, jsonString, static_cast<char>(0));
	in.close();

	rapidjson::Document document;
	document.Parse(jsonString.c_str());
	if (document.GetParseError() != 0) {
		return 0;
	}

	for (auto& obj : document.GetObject())
	{
		Mesh tempMesh;
		PhongMaterial tempMaterial;
		tempMesh.load(obj.value["mesh"].GetString());
		auto mat = obj.value["material"].GetObjectW();
		tempMaterial.setAmbient(glm::vec4(mat["ambient"][0].GetFloat(), mat["ambient"][1].GetFloat(), mat["ambient"][2].GetFloat(), mat["ambient"][3].GetFloat()));
		tempMaterial.setDiffuse(glm::vec4(mat["diffuse"][0].GetFloat(), mat["diffuse"][1].GetFloat(), mat["diffuse"][2].GetFloat(), mat["diffuse"][3].GetFloat()));
		tempMaterial.setEmission(glm::vec4(mat["emission"][0].GetFloat(), mat["emission"][1].GetFloat(), mat["emission"][2].GetFloat(), mat["emission"][3].GetFloat()));
		tempMaterial.setShininess(mat["shininess"].GetFloat());
		tempMaterial.setSpecular(glm::vec4(mat["specular"][0].GetFloat(), mat["specular"][1].GetFloat(), mat["specular"][2].GetFloat(), mat["specular"][3].GetFloat()));
		
		materials.push_back(std::make_shared<PhongMaterial>(tempMaterial));
		meshes.push_back(std::make_shared<Mesh>(tempMesh));
	}

	return 1;
}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	GraphicObject tempGraphicObject;
	std::shared_ptr<GameObject> tempPtr;
	tempGraphicObject.setMesh(meshes[static_cast<int>(type)]);
	tempGraphicObject.setMaterial(materials[static_cast<int>(type)]);
	tempGraphicObject.setPosition(glm::vec3(x - 10, 0, y - 10));
	tempPtr = std::make_shared<GameObject>(tempGraphicObject);
	tempPtr->setPosition(x, y);
	return tempPtr;
}
