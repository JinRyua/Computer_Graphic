#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
#include "ObjParser.h"
#include"bmpfuncs.h"
#include<fstream>
#include<GL/glext.h>
#include<algorithm>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib");

#include"global.h"
#include"calculate.h"
#include"interaction.h"
#include"mapping.h"

using namespace std;

void draw_axis(void);
void draw_map();
void DrawLego(int index, int color);


//float inner_product(vec a, vec b);



void init() {
	/*화면의 기본색으로 black 설정 */
	mx = my = mstat = 0;		//마우스 값 초기화
	tx = ty = tz = trot = 0;	//기본 행렬 초기화
	glClearColor(0.1f, 0.5f, 0.5f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_sun); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//다른 인자로 바꾸어 변화가 있는지 확인해 볼 것
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	cubeTextureMapping();
	mapcubeTextureMapping();
	glEnable(GL_TEXTURE_2D);

}

//
//void draw_string(void *font, const char* str, int x, int y) {
//	unsigned int i;
//	glRasterPos2i(x, y);
//	for (i = 0; i < strlen(str); i++) {
//		glutBitmapCharacter(font, str[i]);
//	}
//}


void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//단위행렬초기화

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (se > 180 * pi / 180 && se <= 360 * pi / 180)	//180~360도 일때 업벡터 반대로
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, -1, 0);
	else
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, 1, 0);
	if (modestate == 0) {
		draw_axis();

		for (int i = 0; i < a.size(); i++) {
			GLfloat tempm[16];					//수정필요
			glPushMatrix();
			glMultMatrixf(a.at(i).matrix);
			if (a.at(i).name == '7') {
				glTranslatef(0, 0.5, 0);		//회전
				glRotatef(tankangle, 0, 0, -1);
				glTranslatef(0, -0.5, 0);
			}
			else if (a.at(i).name == '8') {//&&check_engine()) {				//회전
				glTranslatef(0, 0.5, 0);
				glRotatef(motorangle, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
			}
			DrawLego(a.at(i).name, a.at(i).color);
			glPopMatrix();
		}




		glPushMatrix();
		if (startcount == 1) {
			//int y = 0;
			//for (int i = 0; i < a.size(); i++)
			//	if (y <= a.at(i).crash[1].y)
			//		y = a.at(i).crash[1].y;
			//ty = y;
			calculate_mat();
			while (check_crash()) {
				tx += 0.1;
				calculate_mat();
			}
			startcount = 0;
		}
		glLoadIdentity();
		glTranslatef(tx, ty, tz);
		glRotatef(trot, 0, 1, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, temp_matrix);
		glPopMatrix();

		glPushMatrix();
		glMultMatrixf(temp_matrix);
		if (s == '7') {
			glTranslatef(0, 0.5, 0);		//회전
			glRotatef(tankangle, 0, 0, -1);
			glTranslatef(0, -0.5, 0);
		}
		else if (s == '8') {//&&check_engine()) {				//회전
			glTranslatef(0, 0.5, 0);
			glRotatef(motorangle, 1, 0, 0);
			glTranslatef(0, -0.5, 0);
		}
		DrawLego(s, c);
		glPopMatrix();


		glFlush();
		glutSwapBuffers();
	}
	else if (modestate == 1) {
		for (int i = 0; i < a.size(); i++) {
			GLfloat tempm[16];					//수정필요
			glPushMatrix();
			glMultMatrixf(a.at(i).matrix);
			if (a.at(i).name == '7') {
				glTranslatef(0, 0.5, 0);		//회전
				glRotatef(tankangle, 0, 0, -1);
				glTranslatef(0, -0.5, 0);
			}
			else if (a.at(i).name == '8') {//&&check_engine()) {				//회전
				glTranslatef(0, 0.5, 0);
				glRotatef(motorangle, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
			}
			DrawLego(a.at(i).name, a.at(i).color);
			glPopMatrix();
		}
		draw_map();
		glFlush();
		glutSwapBuffers();
	}


}

int main(int argc, char** argv) {
	PlaySound(TEXT("abc.wav"), NULL, SND_ASYNC | SND_LOOP);
	/* Windows 초기화 */
	int submenu1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init();

	//submenu1 = glutCreateMenu(sub_menu_function);
	//glutAddMenuEntry("Point", 1);
	//glutAddMenuEntry("Line", 2);
	//glutAddMenuEntry("Triangle", 3);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("CreateMode", 11);
	glutAddMenuEntry("GameMode", 10);
	glutAddMenuEntry("Quit", 999);
	//glutAddSubMenu("Sub Menu", submenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutSpecialFunc(arrow);
	glutMainLoop();

	return 0;
}



void DrawLego(int index, int color) {
	char str[7];
	str[0] = index;
	str[1] = '.'; str[2] = 'o'; str[3] = 'b'; str[4] = 'j'; str[5] = 0;
	ObjParser a(str);

	glColor3fv(co[color]);

	int size = a.vertexIdx.size();
	glBindTexture(GL_TEXTURE_2D, texname[0]);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < size; i++) {
		unsigned int k = a.vertexIdx.at(i);
		glTexCoord2f(a.textures[a.textureIdx[i] - 1].x, a.textures[a.textureIdx[i] - 1].y);
		glNormal3f(a.normal[a.normalIdx[i] - 1].x, a.normal[a.normalIdx[i] - 1].y,
			a.normal[a.normalIdx[i] - 1].z);
		glVertex3f(a.vertices.at(k - 1).x, a.vertices.at(k - 1).y,
			a.vertices.at(k - 1).z);
	}
	glEnd();


}

void draw_map() {

	glPushMatrix();
	glTranslatef(0, g_nSkySize / 10, 0);
	glColor3f(1, 1, 1);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glBegin(GL_QUADS);
	glTexCoord3d(1.0, 1.0, 1.0);
	glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0);
	glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0);
	glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0);
	glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);

	glTexCoord3d(-1.0, 1.0, 1.0);
	glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0);
	glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);


	glTexCoord3d(-1.0, 1.0, -1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, 1.0);
	glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, 1.0, -1.0);
	glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);

	glTexCoord3d(-1.0, -1.0, -1.0);
	glVertex3f(-g_nSkySize / 10, -g_nSkySize / 10, -g_nSkySize / 10);
	glTexCoord3d(-1.0, -1.0, 1.0);
	glVertex3f(-g_nSkySize / 10, -g_nSkySize / 10, g_nSkySize / 10);
	glTexCoord3d(1.0, -1.0, 1.0);
	glVertex3f(g_nSkySize / 10, -g_nSkySize / 10, g_nSkySize / 10);
	glTexCoord3d(1.0, -1.0, -1.0);
	glVertex3f(g_nSkySize / 10, -g_nSkySize / 10, -g_nSkySize / 10);

	glTexCoord3d(1.0, 1.0, 1.0);
	glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
	glTexCoord3d(1.0, -1.0, 1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, -1.0, 1.0);
	glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
	glTexCoord3d(-1.0, 1.0, 1.0);
	glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);

	glTexCoord3d(1.0, 1.0, -1.0);
	glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
	glTexCoord3d(1.0, -1.0, -1.0);
	glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, -1.0, -1.0);
	glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
	glTexCoord3d(-1.0, 1.0, -1.0);
	glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
	glEnd();
	glDisable(GL_TEXTURE_CUBE_MAP);
	glPopMatrix();
}

void draw_axis(void) {
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
	glLineWidth(1);
}


//
//float inner_product(vec a, vec b) {
//	float temp;
//	temp = a.x*b.x + a.y*b.y + a.z*b.z;
//	return temp;
//}
