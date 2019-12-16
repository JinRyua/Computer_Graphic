#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;

bool antialiase_on = false;
int point[200][2] = { {0,0}, };
int posta[200]{ 0, };
int num = 0;
int stat = 1;
double angle = 0;
int ast = 0;
void idle(void);

float earth_gong = 0;
float earth_rot = 0;
float mars_gong = 0;
float mars_rot = 0;
float moon_gong = 0;
float moon_rot = 0;
float jupiter_gong = 0;
float jupiter_rot = 0;



float pi = 3.14;
float se = 45 * pi / 180;
float fi = 45 * pi / 180;
float r = 15;
void resize(int width, int height);
void draw_axis(void);
void arrow(int key, int x, int y);

GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };

GLfloat ambient_sun[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat diffuse_sun[] = { 1.0f,0.0f,0.0f,1.0f };
GLfloat specular_sun[] = { 1.0f,1.0f,1.0f,1.0f };

GLfloat light_position[] = { 0.0,0.0,0.0,1.0 };

int position = 0;

void init() {
	/*화면의 기본색으로 black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);

	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight);

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_sun); 
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_sun);
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

}

void draw_string(void *font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);
	for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//단위행렬초기화

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0);

	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "12141745", 20, 20);
	


	glPushMatrix();
	glTranslatef(10, 0, 0);
	glLightfv(GL_LIGHT4, GL_POSITION, light_position);
	glPopMatrix();

	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	GLfloat emission[] = { 0.0f,0.0f,0.0f,1.0f };

	if (position == '1')
		emission[0] = 1.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glColor3f(1, 0, 0);
	glutSolidSphere(4, 100, 100);		//태양
	//draw_axis();
	emission[0]= emission[1]= emission[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	glPushMatrix();

	glRotatef(earth_gong, 0, 1, 0);	//공전
	//draw_axis();
	glTranslatef(20, 0, 0);			//태양과 지구 거리
	//draw_axis();
	glRotatef(earth_rot, 0, 1, 0);	//자전
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);

	if (position == '2')
		emission[2] = 1.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glColor3f(0, 0, 1);
	glutSolidSphere(1.5, 100, 100);		//지구
	emission[0] = emission[1] = emission[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	//draw_axis();

	glRotatef(moon_gong, 0, 1, 0);	//달의 공전
	glTranslatef(4, 0, 0);
	glRotatef(moon_rot, 0, 1, 0);	//달의 자전


	glLightfv(GL_LIGHT3, GL_POSITION, light_position);

	if (position == '3') {
		emission[2] = 1.0f;
		emission[1] = 0.5f;
	}
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glColor3f(0, 0.5, 1);
	glutSolidSphere(1, 100, 100);;		//달
	emission[0] = emission[1] = emission[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	//draw_axis();

	//실습2
	glPopMatrix();
	glPushMatrix();

	glRotatef(mars_gong, 0, 1, 0);	//공전
	glTranslatef(16, 0, 0);			//태양과 화성거리
	glRotatef(mars_rot, 0, 1, 0);	//자전

	glColor3f(0, 1, 1);
	glutSolidSphere(2, 100, 100);;		//화성
//	draw_axis();

	glPopMatrix();


	glRotatef(jupiter_gong, 0, 1, 0);	//공전
	glTranslatef(10, 0, 0);			//태양과 목성거리
	glRotatef(jupiter_rot, 0, 1, 0);	//자전

	glColor3f(1, 0, 1);
	glutSolidSphere(3, 100, 100);		//목성
	//draw_axis();

	glFlush();
	glutSwapBuffers();



}


void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 500 - y);
	if (state == 0) {
		point[num][0] = x;
		point[num][1] = 500 - y;
		posta[num] = stat;
		num++;
	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, 500 - y);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);
	if (key >= '0', key <= '4') {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		position = key;
	}
	switch (key) {
	case '0':
		glEnable(GL_LIGHT0);
		break;
	case '1':
		glEnable(GL_LIGHT1);
		break;
	case '2':
		glEnable(GL_LIGHT2);
		break;
	case '3':
		glEnable(GL_LIGHT3);
		break;
	case '4':
		glEnable(GL_LIGHT4);
		break;
	}
	if (key == 'a')
		antialiase_on = !antialiase_on;
	if (key == 'z')
		ast = !ast;

	glutPostRedisplay();
}

void sub_menu_function(int option) {
	printf("Submenu %d has been selected\n", option);
	if (option == 1)
		stat = 1;
	if (option == 2)
		stat = 2;
	if (option == 3)
		stat = 3;
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH);
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
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//시점용 매트릭스 설정
	glLoadIdentity();		//단위행렬 초기화
	gluPerspective(45, (float)width / (float)height, 10, 300);	//10~300 범위에서, 변경한 윈도우만큼 시점을 변경
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