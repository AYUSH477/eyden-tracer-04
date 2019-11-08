#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		// Eyelight Shader
		// std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 0.5f, 0));

		// Eyelight Texture Shader
		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(0.5f, 0.5f, 0.5f), "../data/cb.bmp");
		
		std::vector<Vec3f> vVertexes;
		std::vector<Vec3f> nVertexes;
		std::vector<Vec2f> tVertexes;
		
		std::string line;

		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertexes.emplace_back(v);
			}
			else if (line == "f") {
				// indices to reference (v1,vt1,vn1), (v2, vt2, vn2) and (v3, vt3, vn3)
				int indices[3][3];

				std::stringstream v_vt_vn;
				std::string lookup;

				for(int i=0; i<3; i++) {
					// extract vertex[i], texture[i], and normal[i]
					ss >> lookup;
					v_vt_vn = std::stringstream(lookup);
					for(int j=0; j<3; j++) {
						getline(v_vt_vn, lookup, '/');
						indices[i][j] = stoi(lookup) - 1;
					}
				}

				// triangles with vertex normals and texture coordinates
				Add(std::make_shared<CPrimTriangleSmoothTextured>(
					vVertexes[indices[0][0]], vVertexes[indices[1][0]], vVertexes[indices[2][0]],
					nVertexes[indices[0][2]], nVertexes[indices[1][2]], nVertexes[indices[2][2]],
					tVertexes[indices[0][1]], tVertexes[indices[1][1]], tVertexes[indices[2][1]],
					pShader));

				// triangles with vertex normals
				// Add(std::make_shared<CPrimTriangleSmooth>(
				// 	vVertexes[indices[0][0]], vVertexes[indices[1][0]], vVertexes[indices[2][0]],
				// 	nVertexes[indices[0][2]], nVertexes[indices[1][2]], nVertexes[indices[2][2]],
				// 	pShader));

				// triangles with no vertex normals
				// Add(std::make_shared<CPrimTriangle>(
				// 	vVertexes[indices[0][0]], vVertexes[indices[1][0]], vVertexes[indices[2][0]],
				// 	pShader));
			}
			else if(line == "vn") {
				// vertex normals
				Vec3f v;
				for(int i=0; i < 3; i++) ss >> v.val[i];
				nVertexes.emplace_back(v);
			} else if(line == "vt") {
				// texture coordinates
				Vec2f v;
				for(int i=0; i<2; i++) ss >> v.val[i];
				tVertexes.emplace_back(v);
			}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
