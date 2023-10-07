#ifndef TEXTURES_H
#define TEXTURES_H

namespace WIP_Polygon {
	class Textures {
	public:
		static const char* sandstone_brick_diffuse;
		static const char* pavement_diffuse;
		static const char* rock_cliff_albedo;
		
		static unsigned int loadTexture(const char* _path);
	};
}
#endif
