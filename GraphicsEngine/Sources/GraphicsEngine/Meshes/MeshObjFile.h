#pragma once
#include "Mesh.h"
#include <vector>
#include "GraphicsEngine/Vector3.h"
#include <string>
#include <vector>

class MeshObjFile : public Mesh
{
public:
	MeshObjFile(const char * filepath);

	virtual void Init();
	virtual void Deinit();

	const std::vector<Vector3>& getMeshVertices();
private:
	std::string m_filepath;

	std::vector<Vector3> vertices; //init vectors for v., colors, normals e.t.c 
	std::vector<Vector4> colors;
	std::vector<Vector3> normals;
	std::vector<Vector3> uv0;
	std::vector<int> indices;//analog: MeshCube.cpp
};
