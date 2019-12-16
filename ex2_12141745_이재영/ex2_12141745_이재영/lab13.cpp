#include"bmpfuncs.h"
#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
#include "ObjParser.h"
#include"bmpfuncs.h"
using namespace std;

bool antialiase_on = false;
int point[200][2] = { {0,0}, };
int posta[200]{ 0, };
int num = 0;
double angle = 0;
int ast = 0;
void idle(void);

int wwidth, wheight;

float earth_gong = 0;
float earth_rot = 0;
float mars_gong = 0;
float mars_rot = 0;
float moon_gong = 0;
float moon_rot = 0;
float jupiter_gong = 0;
float jupiter_rot = 0;

int s = '1';
int c = 1;
//60 60
float pi = 3.14;
float se = 60 * pi / 180;
float fi = 60 * pi / 180;
float r = 14;
void resize(int width, int height);
void draw_axis(void);
void arrow(int key, int x, int y);
void cubeTextureMapping();
void sylinderTextureMapping();
void sphereTextureMapping();
void draw_sphere();

GLuint texname[6];
GLuint texname2[3];
GLuint texname3[2];

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

GLUquadricObj* m_pQuadric = gluNewQuadric();
GLUquadricObj* m_pQuadric2 = gluNewQuadric();


int position = 0;

void init() {
	/*화면의 기본색으로 black 설정 */
	glClearColor(0.1f, 0.5f, 0.5f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	gluQuadricNormals(m_pQuadric, GLU_SMOOTH);
	gluQuadricDrawStyle(m_pQuadric2, GLU_FILL);
	gluQuadricNormals(m_pQuadric2, GLU_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_sun);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_sun);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_sun);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);
	//glEnable(GL_COLOR_MATERIAL);
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
	sylinderTextureMapping();
	sphereTextureMapping();
	gluQuadricTexture(m_pQuadric, GL_TRUE);
	gluQuadricTexture(m_pQuadric2, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
}

void draw_string(void *font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);
	for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void cubeTextureMapping() {
	glGenTextures(6, texname);
	int imgwidth, imgheigt, channels;
	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, texname[i]);
		char buf[100];
		sprintf(buf, "img/TexImage%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgwidth, &imgheigt, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheigt, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void sylinderTextureMapping() {
	glGenTextures(3, texname2);
	int imgwidth, imgheigt, channels;
	glBindTexture(GL_TEXTURE_2D, texname2[1]);
	char buf[100];
	sprintf(buf, "img/coke.bmp");
	buf[strlen(buf)] = 0;
	uchar* img = readImageData(buf, &imgwidth, &imgheigt, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheigt, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texname2[0]);
	char buf1[100];
	sprintf(buf1, "img/CIDER_T.bmp");
	buf[strlen(buf1)] = 0;
	uchar* img1 = readImageData(buf1, &imgwidth, &imgheigt, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheigt, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texname2[2]);
	char buf2[100];
	sprintf(buf2, "img/CIDER_B.bmp");
	buf[strlen(buf2)] = 0;
	uchar* img2 = readImageData(buf2, &imgwidth, &imgheigt, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheigt, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void sphereTextureMapping() {
	glGenTextures(1, texname3);
	uchar* img3;
	int width, height, channels;

	glBindTexture(GL_TEXTURE_2D, texname3[0]);
	img3 = readImageData("img/EARTH.BMP", &width, &height, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void DrawLego(int index, int color) {
	char str[7];
	str[0] = index;
	str[1] = '.'; str[2] = 'o'; str[3] = 'b'; str[4] = 'j'; str[5] = 0;
	ObjParser a(str);

	glColor3fv(co[color]);

	int size = a.vertexIdx.size();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < size; i++) {
		unsigned int k = a.vertexIdx.at(i);
		glVertex3f(a.vertices.at(k - 1).x, a.vertices.at(k - 1).y,
			a.vertices.at(k - 1).z);
	}
	glEnd();


}

void draw_text() {
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Graphcis are cool!!", 10, 10);
	glColor3f(1.0f, 1.0f, 0);
	draw_string(GLUT_BITMAP_HELVETICA_10, "MUlti-Viewport Example!!", 0, 0);
}

void draw_cylinder() {
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glBindTexture(GL_TEXTURE_2D, texname2[0]);
	gluPartialDisk(m_pQuadric, 0, 0.7, 30, 3, 0, 360);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texname2[1]);
	gluCylinder(m_pQuadric, 0.7, 0.7, 2, 20, 20);

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, texname2[2]);
	gluPartialDisk(m_pQuadric, 0, 0.7, 30, 3, 0, 360);
	glPopMatrix();

}

void draw_sphere() {
	glTranslatef(-2, 0, -2);
	glColor3f(1.0, 1.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, texname3[0]);
	gluSphere(m_pQuadric2, 1.4, 100, 100);
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
	glPushMatrix();
	
	glViewport(0, wwidth / 2, wwidth / 2, wheight / 2);
	//draw_text();
	draw_axis();
	glFlush();
	glPopMatrix();
	glPushMatrix();
	glViewport(0, 0, wwidth / 2, wheight / 2);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texname[0]);
	glBegin(GL_QUADS);
	//left
	glNormal3f(-1.0, 0, 0);
	glTexCoord2f(0, 0);		glVertex3f(-3.0f, 3.0f, -3.0f);
	glTexCoord2f(1, 0);		glVertex3f(-3.0f, -3.0f, -3.0f);
	glTexCoord2f(1, 1);		glVertex3f(-3.0f, -3.0f, 3.0f);
	glTexCoord2f(0, 1);		glVertex3f(-3.0f, 3.0f, 3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texname[1]);
	glBegin(GL_QUADS);
	//right
	glNormal3f(1.0, 0, 0);
	glTexCoord2f(0, 0);		glVertex3f(3.0f, 3.0f, 3.0f);
	glTexCoord2f(1, 0);		glVertex3f(3.0f, -3.0f, 3.0f);
	glTexCoord2f(1, 1);		glVertex3f(3.0f, -3.0f, -3.0f);
	glTexCoord2f(0, 1);		glVertex3f(3.0f, 3.0f, -3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texname[2]);
	glBegin(GL_QUADS);
	//Bottom
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0);		glVertex3f(-3.0f, -3.0f, 3.0f);
	glTexCoord2f(1, 0);		glVertex3f(3.0f, -3.0f, 3.0f);
	glTexCoord2f(1, 1);		glVertex3f(3.0f, -3.0f, -3.0f);
	glTexCoord2f(0, 1);		glVertex3f(-3.0f, -3.0f, -3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texname[3]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	//Top
	glTexCoord2f(0, 0);		glVertex3f(-3.0f, 3.0f, 3.0f);
	glTexCoord2f(1, 0);		glVertex3f(3.0f, 3.0f, 3.0f);
	glTexCoord2f(1, 1);		glVertex3f(3.0f, 3.0f, -3.0f);
	glTexCoord2f(0, 1);		glVertex3f(-3.0f, 3.0f, -3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texname[4]);
	glBegin(GL_QUADS);
	//Near
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);		glVertex3f(3.0f, -3.0f, 3.0f);
	glTexCoord2f(2, 0);		 glVertex3f(-3.0f, -3.0f, 3.0f);
	glTexCoord2f(2, 2);		glVertex3f(-3.0f, 3.0f, 3.0f);
	glTexCoord2f(0, 2);		glVertex3f(3.0f, 3.0f, 3.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texname[5]);
	glBegin(GL_QUADS);
	//Far
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);			glVertex3f(3.0f, 3.0f, -3.0f);
	glTexCoord2f(1, 0);		glVertex3f(-3.0f, 3.0f, -3.0f);
	glTexCoord2f(1, 1);		glVertex3f(-3.0f, -3.0f, -3.0f);
	glTexCoord2f(0, 1);		glVertex3f(3.0f, -3.0f, -3.0f);
	glEnd();

	glFlush();
	glPopMatrix();

	glPushMatrix();
	glViewport(wwidth / 2, wheight / 2, wwidth / 2, wheight / 2);
	glTranslatef(2, 0, 2);
	glRotatef(-90, 1, 0, 0);
	draw_cylinder();
	glPopMatrix();
	glFlush();
	
	glViewport(wwidth / 2, 0, wwidth / 2, wheight / 2);
	draw_sphere();

	
	glFlush();
	glutSwapBuffers();



}




void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 500 - y);
	if (state == 0) {
		point[num][0] = x;
		point[num][1] = 500 - y;

	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, 500 - y);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);

	if (key == 'a')
		antialiase_on = !antialiase_on;
	if (key == 'z')
		ast = !ast;

	glutPostRedisplay();
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
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutSpecialFunc(arrow);
	glutMainLoop();

	return 0;
}

void idle(void) {
	//if (ast == 0)
	//	angle = angle + 0.5;
	//if (angle > 360) angle -= 360;

	earth_gong = earth_gong + 0.1;
	if (earth_gong > 360)earth_gong -= 360;
	earth_rot = earth_rot + 1;
	if (earth_rot > 360)earth_rot -= 360;
	mars_gong = mars_gong + 0.3;
	if (mars_gong > 360)mars_gong -= 360;
	mars_rot = mars_rot + 2;
	if (mars_rot > 360)mars_rot -= 360;
	moon_gong = moon_gong + 0.1;
	if (moon_gong > 360)moon_gong -= 360;
	moon_rot = moon_rot + 0.2;
	if (moon_rot > 360)moon_rot -= 360;

	jupiter_gong = jupiter_gong + 0.05;
	if (jupiter_gong > 360)jupiter_gong -= 360;
	jupiter_rot = jupiter_rot + 0.1;
	if (jupiter_rot > 360)jupiter_rot -= 360;

	glutPostRedisplay();
}

void resize(int width, int height) {
	//glViewport(0, 0, width, height);
	wwidth = width;
	wheight = height;
	glMatrixMode(GL_PROJECTION);	//시점용 매트릭스 설정
	glLoadIdentity();		//단위행렬 초기화
	gluPerspective(45, (float)width / (float)height, 1, 300);	//10~300 범위에서, 변경한 윈도우만큼 시점을 변경
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
		fi -= 1 * pi / 180;
		break;
	case GLUT_KEY_RIGHT:
		fi += 1 * pi / 180;
		break;
	case GLUT_KEY_UP:
		se += 1 * pi / 180;
		break;
	case GLUT_KEY_DOWN:
		se -= 1 * pi / 180;
		break;
	}

	if (fi > 360 * pi / 180)
		fi = 1 * pi / 180;
	else if (fi <= 0)
		fi = 360 * pi / 180;

	if (se > 360 * pi / 180)
		se = 1 * pi / 180;			//360도 이상일때, 값을 1부터 변경하게 함
	else if (se <= 0)
		se = 360 * pi / 180;
	printf("se=%f, fi=%f\n", se / pi * 180, fi / pi * 180);
	glutPostRedisplay();

}