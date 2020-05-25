#include "MeshObjFile.h"
#include "GraphicsEngine/Application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


MeshObjFile::MeshObjFile(const char * filepath)
{
	m_filepath = Application::Instance().GetDataDirectory() + "/" + filepath;
}

void MeshObjFile::Init()
{
	Mesh::Init();
    // TODO: Task07
    //std::vector<Vector3> vertices; //init vectors for v., colors, normals e.t.c 
    //std::vector<Vector4> colors;
    //std::vector<Vector3> normals;
    //std::vector<Vector3> uv0;
    //std::vector<int> indices;//analog: MeshCube.cpp

    std::ifstream objFile;

    objFile.open(m_filepath);
    if (!objFile)
        exit(1);

    std::string line;
    while(std::getline(objFile, line)) {
        std::istringstream sline(line);
        std::string type;
        std::getline(sline, type, ' ');

        if (type == "v") {
            float x, y, z;
            sline >> x >> y >> z;
            vertices.push_back({ x, y, z });
            colors.push_back({ 0.0, 1.0, 0.0, 1.0 });
        } else 
        if (type == "vt") {
            float x, y;
            sline >> x >> y;
            float z = 0.0;
            uv0.push_back({ x, y, z });
            if (sline >> z)
                uv0.back().z = z;
        } else 
        if (type == "vn") {
            float x, y, z;
            sline >> x >> y >> z;
            normals.push_back({ x, y, z });
        } else 
        if (type == "f") {
            for (int i = 0; i < 3; i++) {
                std::string id;
                std::getline(sline, id, ' ');
                indices.push_back(stoi(id) - 1);
                //std::cout << id << " " << stoi(id) << std::endl;
            }
        }
    }
    objFile.close();

    meshImpl->SetVertices(vertices);
    meshImpl->SetColors(colors);
    meshImpl->SetNormals(normals);
    meshImpl->SetUV0(uv0);

    meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_LIST);

    meshImpl->Apply();
}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}

const std::vector<Vector3>& MeshObjFile::getMeshVertices()
{
    return vertices;
    // TODO: вставьте здесь оператор return
}
