#include"global.h"
using namespace std;

bool antialiase_on = false;
int num = 0;
double angle = 0;
int ast = 0;
 int mx, my, mstat;
 int s = '1';
 int c = 1;
 float pi = 3.14;
 float se = 60 * pi / 180;
 float fi = 60 * pi / 180;
 float r = 7;
 float tx, ty, tz, trot;
 int g_nSkySize = 500;
// struct vec {
//	float x;
//	float y;
//	float z;
//};
 GLuint texname[1];
 GLuint g_nCubeTex;
// struct block {
//	int name;
//	int color;
//	GLfloat matrix[16];
//	vec crash[2];
//};
 GLfloat temp_matrix[16];

 vector<block> a;

 float co[9][3] = { {0,0,0}, {1.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f}
				   , {0.0f,0.0f,1.0f}, {1.0f,1.0f,0.0f}, {1.0f,0.0f,1.0f}
			   , {0.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f} };
 GLfloat ambientLight[4] = { 0.4f,0.4f,0.4f,1.0f };
 GLfloat diffuseLight[4] = { 1.0f,1.0f,1.0f,1.0f };
 GLfloat specularLight[4] = { 1.0f,1.0f,1.0f,1.0f };
 GLfloat ambient_sun[4] = { 0.2f,0.2f,0.2f,1.0f };
 GLfloat diffuse_sun[4] = { 1.0f,1.0f,1.0f,1.0f };
 GLfloat specular_sun[4] = { 1.0f,1.0f,1.0f,1.0f };
 GLfloat light_position[4] = { 0.0f,0.0f,0.0f,1.0f };
 int position = 0;