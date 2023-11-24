#ifndef SHADER_H
#define SHADER_H

#include <C:\OPENGL\content\glad\glad.h>
#include <C:\OPENGL\content\Include\glm\glm\glm.hpp>
#include <C:\OPENGL\content\Include\glm\glm\gtc\matrix_transform.hpp>
#include <C:\OPENGL\content\Include\glm\glm\gtc\type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace WIP_Polygon {
	class Shader {
	public:
		unsigned int ID;
		const char* vertexPath;
		const char* fragmentPath;

		Shader();
		Shader(const char* _vertexPath, const char* _fragmentPath);
		void InitializeShader();		
		void use(); 
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec3(const std::string& name, glm::vec3 value) const;
		void setVec4(const std::string& name, glm::vec4 value) const;
		void setMat4(const std::string& name, glm::mat4 value) const;
	};
}
#endif