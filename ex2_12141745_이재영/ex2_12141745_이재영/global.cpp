#include"global.h"
using namespace std;

vec unitvec[2];
bool antialiase_on = false;
int modestate = 2;
int startcount = 1;
int tankcount = 1;
int motorcount = 1;
int motorangle = 0;
int num = 0;
double tankangle = 0;
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

 GLuint texname[1];
 GLuint g_nCubeTex;
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