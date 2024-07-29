#include "MeshImports.h"
namespace WIP_Polygon {
	OBJMesh MeshImports::test_cube = OBJImporter::Import("C:/OPENGL/models/testbox/testbox.obj");
	OBJMesh MeshImports::unit_cube = OBJImporter::Import("C:/OPENGL/models/UnitCube/UnitCube.obj");
	OBJMesh MeshImports::little_ship = OBJImporter::Import("C:/OPENGL/models/LittleShip/LittleShip.obj");

}