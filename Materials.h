#ifndef Materials_H
#define Materials_H

#include <C:\OPENGL\content\glad\glad.h>
#include <C:\OPENGL\content\Include\glm\glm\glm.hpp>
#include <C:\OPENGL\content\Include\glm\glm\gtc\type_ptr.hpp>
#include <C:\OPENGL\content\Include\glm\glm\gtc\matrix_access.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}

	Material() {
		ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
		specular = glm::vec3(0.0f, 0.0f, 0.0f);
		shininess = 0.0f;
	}
};

class Materials {
public:
	Material Emerald() {
		return Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 128.0f);
	}
	Material Jade() {
		return Material(glm::vec3(0.135f,0.2225f,0.1575f), glm::vec3(0.54f,0.89f,0.63f), glm::vec3(0.316228f,0.316228f,0.316228f), 0.1f * 128.0f);
	}
	Material Obsidian() {
		return Material(glm::vec3(0.05375f,0.05f,0.06625f), glm::vec3(0.18275f,0.17f,0.22525f), glm::vec3(0.332741f,0.328634f,0.346435f), 0.3f * 128.0f);
	}
	Material Pearl() {
		return Material(glm::vec3(0.25f,0.20725f,0.20725f), glm::vec3(1.0f,0.829f,0.829f), glm::vec3(0.296648f,0.296648f,0.296648f), 0.088f * 128.0f);
	}
	Material Ruby() {
		return Material(glm::vec3(0.1745f,0.01175f,0.01175f), glm::vec3(0.61424f,0.04136f,0.04136f), glm::vec3(0.727811f,0.626959f,0.626959f), 0.6f * 128.0f);
	}
	Material Turqouise() {
		return Material(glm::vec3(0.1f,0.18725f,0.1745f), glm::vec3(0.396f,0.74151f,0.69102f), glm::vec3(0.297254f,0.30829f,0.306678f), 0.1f * 128.0f);
	}
	Material Brass() {
		return Material(glm::vec3(0.329412f,0.223529f,0.027451f), glm::vec3(0.780392f,0.568627f,0.113725f), glm::vec3(0.992157f,0.941176f,0.807843f), 0.1f * 128.0f);
	}
	Material Bronze() {
		return Material(glm::vec3(0.2125f,0.1275f,0.054f), glm::vec3(0.714f,0.4284f,0.18144f), glm::vec3(0.393548f,0.271906f,0.166721f), 0.2f * 128.0f);
	}
	Material Chrome() {
		return Material(glm::vec3(0.25f,0.25f,0.25f), glm::vec3(0.4f,0.4f,0.4f), glm::vec3(0.774597f,0.774597f,0.774597f), 0.6f * 128.0f);
	}
	Material Copper() {
		return Material(glm::vec3(0.19125f,0.0735f,0.0225f), glm::vec3(0.7038f,0.27048f,0.0828f), glm::vec3(0.256777f,0.137622f,0.086014f), 0.1f * 128.0f);
	}
	Material Gold() {
		return Material(glm::vec3(0.24725f,0.1995f,0.0745f), glm::vec3(0.75164f,0.60648f,0.22648f), glm::vec3(0.628281f,0.555802f,0.366065f), 0.4f * 128.0f);
	}
	Material Silver() {
		return Material(glm::vec3(0.19225f,0.19225f,0.19225f), glm::vec3(0.50754f,0.50754f,0.50754f), glm::vec3(0.508273f,0.508273f,0.508273f), 0.4f * 128.0f);
	}
	Material BlackPlastic() {
		return Material(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.01f,0.01f,0.01f), glm::vec3(0.50f,0.50f,0.50f), 0.25f * 128.0f);
	}
	Material CyanPlastic() {
		return Material(glm::vec3(0.0f,0.1f,0.06f), glm::vec3(0.0f,0.50980392f,0.50980392f), glm::vec3(0.50196078f,0.50196078f,0.50196078f), 0.25f * 128.0f);
	}
	Material GreenPlastic() {
		return Material(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.1f,0.35f,0.1f), glm::vec3(0.45f,0.55f,0.45f), 0.25f * 128.0f);
	}
	Material RedPlastic() {
		return Material(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.5f,0.0f,0.0f), glm::vec3(0.7f,0.6f,0.6f), 0.25f * 128.0f);
	}
	Material WhitePlastic() {
		return Material(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.55f,0.55f,0.55f), glm::vec3(0.70f,0.70f,0.70f), 0.25f * 128.0f);
	}
	Material YellowPlastic() {
		return Material(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.5f,0.5f,0.0f), glm::vec3(0.60f,0.60f,0.50f), 0.25f * 128.0f);
	}
	Material BlackRubber() {
		return Material(glm::vec3(0.02f,0.02f,0.02f), glm::vec3(0.01f,0.01f,0.01f), glm::vec3(0.4f,0.4f,0.4f), .078125f * 128.0f);
	}
	Material CyanRubber() {
				return Material(glm::vec3(0.0f,0.05f,0.05f), glm::vec3(0.4f,0.5f,0.5f), glm::vec3(0.04f,0.7f,0.7f), .078125f * 128.0f);
	}
	Material GreenRubber() {
		return Material(glm::vec3(0.0f,0.05f,0.0f), glm::vec3(0.4f,0.5f,0.4f), glm::vec3(0.04f,0.7f,0.04f), .078125f * 128.0f);
	}
	Material RedRubber() {
		return Material(glm::vec3(0.05f,0.0f,0.0f), glm::vec3(0.5f,0.4f,0.4f), glm::vec3(0.7f,0.04f,0.04f), .078125f * 128.0f);
	}
	Material WhiteRubber() {
		return Material(glm::vec3(0.05f,0.05f,0.05f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.7f,0.7f,0.7f), .078125f * 128.0f);
	}
	Material YellowRubber() {
		return Material(glm::vec3(0.05f,0.05f,0.0f), glm::vec3(0.5f,0.5f,0.4f), glm::vec3(0.7f,0.7f,0.04f), .078125f * 128.0f);
	}

};

#endif