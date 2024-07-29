#include "OBJImporter.h"

namespace WIP_Polygon {
	struct face_data {
		int vertex;
		int uv;
		int normal;
		face_data(int _v, int _uv, int _n) {
			vertex = --_v;
			uv = --_uv;
			normal = --_n;
		}
	};

	struct face {
		std::vector<face_data> index_set{};
		face() {
			index_set = {};
		};
	};	

	void OBJImporter::split(const std::string& in,
		std::vector<std::string>& out,
		std::string token) {
		out.clear();

		std::string temp;

		for (int i = 0; i < int(in.size()); i++)
		{
			std::string test = in.substr(i, token.size());
			//std::cout << "this is test-> " << test << "\n";
			if (test == token)
			{
				if (!temp.empty())
				{
					out.push_back(temp);
					temp.clear();
					i += (int)token.size() - 1;
				}
				else
				{
					out.push_back("");
				}
			}
			else if (i + token.size() >= in.size())
			{
				temp += in.substr(i, token.size());
				out.push_back(temp);
				break;
			}
			else
			{
				temp += in[i];
			}
		}
	}

	void TriangulateFace(face _face, std::vector<int>& triangles, std::vector<glm::vec3> _vertices) {
		int vertex_index = 1;
		for (int i = 0; i < /*6*/_face.index_set.size(); i+=3) {
			int v1 = _face.index_set[0].vertex;
			int v2 = _face.index_set[vertex_index].vertex;
			int v3 = _face.index_set[vertex_index + 1].vertex;
			triangles.push_back(v1);
			triangles.push_back(v2);
			triangles.push_back(v3);
			vertex_index += 1;
		}
	}

	OBJMesh OBJImporter::Import(std::string file_path) {
		//test file - "C:/OPENGL/models/testbox/testbox.obj"
		std::string line;
		std::ifstream myfile(file_path);
		std::vector<glm::vec3> vertices{};
		std::vector<glm::vec2> uvs{};
		std::vector<glm::vec3> normals{};
		std::vector<face> faces{};
		OBJMesh mesh{};
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				size_t s{};
				size_t e{};
				//s = line.substr(5);
				s = 0;
				e = line.find_first_of(" ", 0);
				std::string mesh_data_type = line.substr(s, e);
				std::vector<std::string> mesh_data{};
				std::string current_line = line.substr(e + 1, line.length());
				split(current_line, mesh_data, " ");
				if (mesh_data_type == "v") {
					glm::vec3 v{ stof(mesh_data[0]),stof(mesh_data[1]),stof(mesh_data[2]) };
					vertices.push_back(v);
				}
				else if (mesh_data_type == "vt") {
					glm::vec2 uv{ stof(mesh_data[0]), stof(mesh_data[1]) };
					uvs.push_back(uv);
				}
				else if (mesh_data_type == "vn") {
					glm::vec3 normal{ stof(mesh_data[0]),stof(mesh_data[1]),stof(mesh_data[2]) };
					normals.push_back(normal);
				}
				else if (mesh_data_type == "f") {
					std::vector<std::string>face_indices{};
					face face{};
					for (int i = 0; i < mesh_data.size(); i++) {
						split(mesh_data[i], face_indices, "/");
						face_data f = { stoi(face_indices[0]), stoi(face_indices[1]), stoi(face_indices[2]) };
						face.index_set.push_back(f);
					}
					faces.push_back(face);
				}
			}
			std::cout << "normals size: " << normals.size() << "\n";
			for (int i = 0; i < faces.size(); i++) {
				std::cout << "face[" << i << "]\n";
				face f = faces[i];
				std::vector<int>triangles{};
			    TriangulateFace(f, triangles, vertices);
				//TODO account for 3d meshes that don't have normals so don't get array out of bounds error
				//depth_testing.vs shader will look fucked up until then.
				for (int j = 0; j < triangles.size(); j++) {
					std::cout << "triangles[" << j << "] = " << triangles[j] << "\n";
					float vx = vertices[triangles[j]].x;
					float vy = vertices[triangles[j]].y;
					float vz = vertices[triangles[j]].z;					
					float nx = normals[i].x;
					float ny = normals[i].y;
					float nz = normals[i].z;
					float uvx = uvs[triangles[j]].x;
					float uvy = uvs[triangles[j]].y;
					mesh.mesh_data.push_back(vx);
					mesh.mesh_data.push_back(vy);
					mesh.mesh_data.push_back(vz);
					mesh.mesh_data.push_back(nx);
					mesh.mesh_data.push_back(ny);
					mesh.mesh_data.push_back(nz);
					mesh.mesh_data.push_back(uvx);
					mesh.mesh_data.push_back(uvy);
				}
			}
//#define DEBUG_OBJ_OUTPUT
#ifdef DEBUG_OBJ_OUTPUT
			std::cout << "vertices: " << "\n";
			for (int i = 0; i < vertices.size(); i++) {
				glm::vec3 v = vertices[i];
				std::cout << "\t" << v.x << "," << v.y << "," << v.z << "\n";
			}
			std::cout << "uvs: " << "\n";
			for (int i = 0; i < uvs.size(); i++) {
				glm::vec2 uv = uvs[i];
				std::cout << "\t" << uv.x << "," << uv.y << "\n";
			}
			std::cout << "normals: " << "\n";
			for (int i = 0; i < normals.size(); i++) {
				glm::vec3 n = normals[i];
				std::cout << "\t" << n.x << "," << n.y << "," << n.z << "\n";
			}
			std::cout << "faces: " << "\n";
			for (int i = 0; i < faces.size(); i++) {
				face f = faces[i];
				for (int j = 0; j < f.index_set.size(); j++) {
					std::cout << "\t" << f.index_set[j].vertex << "/" << f.index_set[j].uv << "/" << f.index_set[j].normal << " ";
				}
				std::cout << "\n";
			}
			for (int x = 0; x < mesh.mesh_data.size(); x+=5) {
				std::cout << mesh.mesh_data[x] << " ";
				std::cout << mesh.mesh_data[x + 1] << " ";
				std::cout << mesh.mesh_data[x + 2] << " ";
				std::cout << mesh.mesh_data[x + 3] << " ";
				std::cout << mesh.mesh_data[x + 4] << "\n";

			}

#endif
			myfile.close();
		}
		else {
			std::cout << "unable to open file @ " << file_path << "\n";
		}
		return mesh;
	}

}