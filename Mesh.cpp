#include "Mesh.h"

Vertex::Vertex(glm::vec3 v, glm::vec2 vt, glm::vec3 vn)
{
	for (int i = 0; i < 3; i++)
	{
		coord[i] = v[i];
		normal[i] = vn[i];
	}
	texCoord[0] = vt[0];
	texCoord[1] = vt[1];
}

Mesh::Mesh()
{
	indexCount = 0;
}

void Mesh::load(std::string filename)
{
	// массив вершин
	std::vector<Vertex> vertices;
	// массив индексов
	std::vector<GLuint> indices;

	// вектор для хранения геометрических координат
	std::vector<glm::vec3> v;
	// вектор для хранения нормалей
	std::vector<glm::vec3> n;
	// вектор для хранения текстурных координат
	std::vector<glm::vec2> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	// std::vector<glm::vec3> fPoints;
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	std::map<std::string, int> vertexToIndexTable;

	int index = 0;

	glm::vec3 temp;

	std::ifstream in;
	in.open(filename);
	std::string Name;

	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> Name;
			if (Name != "v" && Name != "vn" && Name != "vt" && Name != "f")
			{
				std::getline(in, Name);
			}
			else
			{
				if (Name == "v")
				{
					in >> temp.x >> temp.y >> temp.z;
					v.push_back(temp);
				}
				else if (Name == "vn")
				{
					in >> temp.x >> temp.y >> temp.z;
					n.push_back(temp);
				}
				else if (Name == "vt")
				{
					in >> temp.x >> temp.y;
					t.push_back(temp);
				}
				else if (Name == "f")
				{
					in.get();
					std::getline(in, Name);
					glm::ivec3 tempVec {0, 0, 0};
					std::string tempStr;
					int slashCount = 0;
					for (auto& ch : Name)
					{
						switch (ch)
						{
						case '/':
							switch (slashCount)
							{
							case 0:
								tempVec[0] = (std::stoi(tempStr));
								tempStr = "";

								break;
							case 1:
								if (tempStr != "")
									tempVec[1] = (std::stoi(tempStr));
								else
									tempVec[1] = 0;
								tempStr = "";

								break;
							}

							slashCount++;

							break;
						case ' ':
						{
							slashCount = 0;
							tempVec[2] = (std::stoi(tempStr));
							tempStr = "";

							tempStr += std::to_string(tempVec[0]);
							tempStr += "/";
							tempStr += std::to_string(tempVec[1]);
							tempStr += "/";
							tempStr += std::to_string(tempVec[2]);

							std::map<std::string, int>::iterator it = vertexToIndexTable.find(tempStr);

							if (it == vertexToIndexTable.end())
							{
								vertexToIndexTable.insert(std::pair<std::string, int>(tempStr, index));

								vertices.push_back(Vertex({ v[tempVec[0] - 1] }, { t[tempVec[1] - 1] }, { n[tempVec[2] - 1] }));
								indices.push_back(index);

								index++;
							}
							else
							{
								indices.push_back(it->second);
							}
							tempVec.x = tempVec.y = tempVec.z = 0;
							tempStr = "";
						}
							break;
						default:
						{
							tempStr.push_back(ch);
						}
							break;
						}
					}
				}
			}
		}
		in.close();

		indexCount = indices.size();

		glGenBuffers(1, &bufferIds[0]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &bufferIds[1]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}



void Mesh::draw()
{
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Mesh::clear()
{

}