#ifndef GLOBAL_H
#define GLOBAL_H
#include<GL/freeglut.h>
#include<stdio.h>
#include<vector>
using namespace std;
struct vec {
	float x;
	float y;
	float z;
};
struct block {
	int name;
	int color;
	GLfloat matrix[16];
	vec crash[2];
};
extern vec unitvec[2];
extern int modestate;
extern int startcount;
extern int tankcount;
extern int motorcount;
extern int motorangle;
extern bool antialiase_on;
extern int num;
extern double tankangle;
extern int ast;
extern int mx, my, mstat;
extern int s;
extern int c;
extern float pi;
extern float se;
extern float fi ;
extern float r;
extern float tx, ty, tz, trot;
extern int g_nSkySize;
extern GLuint texname[1];
extern GLuint g_nCubeTex;
extern GLfloat temp_matrix[16];
extern vector<block> a;
extern float co[9][3];
extern GLfloat ambientLight[4] ;
extern GLfloat diffuseLight[4] ;
extern GLfloat specularLight[4];
extern GLfloat ambient_sun[4];
extern GLfloat diffuse_sun[4] ;
extern GLfloat specular_sun[4] ;
extern GLfloat light_position[4];
extern int position;
#endif