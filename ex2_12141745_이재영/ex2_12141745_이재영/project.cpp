#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
#include "ObjParser.h"
#include"bmpfuncs.h"
#include<fstream>
#include<GL/glext.h>
#include<algorithm>
#include"interaction.h"
#include"global.h"
using namespace std;




bool check_crash();

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

void mapcubeTextureMapping() {
	glGenTextures(1, &g_nCubeTex);
	int width, height, channels;
	uchar* img0 = readImageData("img/img/img/512px.bmp", &width, &height, &channels);
	uchar* img1 = readImageData("img/img/img/512nx.bmp", &width, &height, &channels);
	uchar* img2 = readImageData("img/img/img/512py.bmp", &width, &height, &channels);
	uchar* img3 = readImageData("img/img/img/512ny.bmp", &width, &height, &channels);
	uchar* img4 = readImageData("img/img/img/512pz.bmp", &width, &height, &channels);
	uchar* img5 = readImageData("img/img/img/512nz.bmp", &width, &height, &channels);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);


}

void cubeTextureMapping() {
	glGenTextures(1, texname);
	int imgwidth, imgheigt, channels;
		glBindTexture(GL_TEXTURE_2D, texname[0]);
		char buf[100];
		sprintf(buf, "1.bmp", 1);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgwidth, &imgheigt, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheigt, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
//
//void draw_string(void *font, const char* str, int x, int y) {
//	unsigned int i;
//	glRasterPos2i(x, y);
//	for (i = 0; i < strlen(str); i++) {
//		glutBitmapCharacter(font, str[i]);
//	}
//}
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



void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//단위행렬초기화

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (se > 180 * pi / 180 && se <= 360 * pi / 180)	//180~360도 일때 업벡터 반대로
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, -1, 0);
	else
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, 1, 0);

	draw_axis();

	for (int i = 0; i < a.size(); i++) {
		GLfloat tempm[16];					//수정필요
		glPushMatrix();
		glMultMatrixf(a.at(i).matrix);
		DrawLego(a.at(i).name, a.at(i).color);
		glPopMatrix();
	}


	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tx, ty, tz);
	glRotatef(trot, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, temp_matrix);
	glPopMatrix();

	glPushMatrix();
	glMultMatrixf(temp_matrix);
	DrawLego(s, c);
	glPopMatrix();


	glFlush();
	glutSwapBuffers();



}

float inner_product(vec a, vec b) {
	float temp;
	temp = a.x*b.x + a.y*b.y + a.z*b.z;
	return temp;
}



void sub_menu_function(int option) {
	printf("Submenu %d has been selected\n", option);

}

void main_menu_function(int option) {
	printf("Main menu %d has benn selected\n", option);
	if (option == 11)
		num = 0;
	if (option == 999)
		exit(0);
	if (option == 10)
		antialiase_on = !antialiase_on;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	/* Windows 초기화 */
	int submenu1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init();

	submenu1 = glutCreateMenu(sub_menu_function);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("clear!", 11);
	glutAddMenuEntry("Quit", 999);
	glutAddMenuEntry("Anti", 10);
	glutAddSubMenu("Sub Menu", submenu1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	//glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutSpecialFunc(arrow);
	glutMainLoop();

	return 0;
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//시점용 매트릭스 설정
	glLoadIdentity();		//단위행렬 초기화
	gluPerspective(45, (float)width / (float)height, 1, 1000);	//1~300 범위에서, 변경한 윈도우만큼 시점을 변경
	glMatrixMode(GL_MODELVIEW);		//그리기용 매트릭스 설정
	printf("resize complete, width=%d, height=%d\n", width, height);
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

void arrow(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		c++;
		break;
	case GLUT_KEY_RIGHT:
		c--;
		break;
	case GLUT_KEY_UP:
		s++;
		break;
	case GLUT_KEY_DOWN:
		s--;
		break;
	}
	if (s > '6')
		s = '1';
	else if (s < '1')
		s = '6';

	if (c>8)
		c = 1;			//360도 이상일때, 값을 1부터 변경하게 함
	else if (c <= 0)
		c = 8;

	if (fi > 360 * pi / 180)
		fi = 1 * pi / 180;
	else if (fi <= 0)
		fi = 360 * pi / 180;

	if (se > 360 * pi / 180)
		se = 1 * pi / 180;			//360도 이상일때, 값을 1부터 변경하게 함
	else if (se <= 0)
		se = 360 * pi / 180;
	printf("se=%f, fi=%f, r=%f\n", se / pi * 180, fi / pi * 180,r);
	glutPostRedisplay();

}