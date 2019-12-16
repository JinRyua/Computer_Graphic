#include"global.h"
antialiase_on = false;
num = 0;
angle = 0;
ast = 0;

s = '1';
c = 1;
//60 60
float pi = 3.14;
float se = 60 * pi / 180;
float fi = 60 * pi / 180;
float r = 7;
//void resize(int width, int height);
//void draw_axis(void);
//void arrow(int key, int x, int y);
//void cubeTextureMapping();
//void mapcubeTextureMapping();
float tx, ty, tz, trot;
int g_nSkySize = 500;

struct vec {
	float x;
	float y;
	float z;
};
GLuint texname[2];
GLuint g_nCubeTex;



struct block {
	int name;
	int color;
	GLfloat matrix[16];
	vec crash[2];
};

GLfloat temp_matrix[16];
vector<block> a;

float co[9][3] = { {0,0,0}, {1.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f}
					, {0.0f,0.0f,1.0f}, {1.0f,1.0f,0.0f}, {1.0f,0.0f,1.0f}
				, {0.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f} };

GLfloat ambientLight[] = { 0.4f,0.4f,0.4f,1.0f };
GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };

GLfloat ambient_sun[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat diffuse_sun[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat specular_sun[] = { 1.0f,1.0f,1.0f,1.0f };

GLfloat light_position[] = { 0.0f,0.0f,0.0f,1.0f };

int position = 0;