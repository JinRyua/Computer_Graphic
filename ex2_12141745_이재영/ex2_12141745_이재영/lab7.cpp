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

void init() {
	/*ȭ���� �⺻������ black ���� */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*ȭ�� ��ǥ ���� ����*//*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);*/


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//�ٸ� ���ڷ� �ٲپ� ��ȭ�� �ִ��� Ȯ���� �� ��
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}
//void draw_point(void) {
//	//���� ���� blue�� ����
//	glColor3f(0.0f, 0.0f, 1.0f);
//	//���� ũ�⸦ ����
//	glPointSize(8.0f);
//	//�� �׸���
//	glBegin(GL_POINTS);
//		glVertex2i(5, 5);
//		glVertex2i(200, 200);
//		glVertex2i(450, 300);
//	glEnd();
//
//}
//
//void draw_line(void) {
//	//���� ���� ����
//	glLineWidth(5.0f);
//	//���� ����ȭ ���
//	glEnable(GL_LINE_STIPPLE);
//	//���� ������ ����
//	glLineStipple(5, 0x00FF);
//
//	/*���� ������ ����������*/
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_LINE_LOOP);
//		glVertex2i(50, 50);
//		glVertex2i(250, 450);
//		glVertex2i(300, 450);
//		glVertex2i(400, 100);
//		glVertex2i(100, 100);
//	glEnd();
//}
//
//void draw_triangle(void) {
//	//���� ������ ����������
//	//�鿡 ȿ���� �ִ� ��� ��� ����
//	//glPolygonMode(GL_FRONT, GL_LINE);
//	//���� ������ ����
//	//glFrontFace(GL_CW);
//	glBegin(GL_TRIANGLES);
//		//���� ������ �ϴû�����
//		glColor4f(0.0f, 1.0f, 1.0f, 0.75);
//		glVertex2i(450, 50);
//		glVertex2i(450, 450);
//		glVertex2i(200, 250);
//		//���� ������ ���������
//		glColor4f(1.0f, 1.0f, 0.0f,0.75f);
//		glVertex2i(50, 50);
//		glVertex2i(50, 450);
//		glVertex2i(300, 250);
//		
//	glEnd();
//}
//
//void draw_string(void* font, const char* str, int x, int y) {
//	unsigned int i;
//	glRasterPos2i(x, y);
//	/*for (i = 0; i < strlen(str); i++) {
//		glutBitmapCharacter(font, str[i]);
//	}*/
//	glutBitmapString(font, (unsigned char*)str);
//}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//��������ʱ�ȭ
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	glColor3f(1, 0, 0);
	glutWireSphere(1.3,50,50);		//�¾�
	draw_axis();
	
	glPushMatrix();

	glRotatef(earth_gong, 0, 1, 0);	//����
	draw_axis();
	glTranslatef(6, 0, 0);			//�¾�� ���� �Ÿ�
	draw_axis();
	glRotatef(earth_rot, 0, 1, 0);	//����
	
	glColor3f(0, 0, 1);
	glutWireSphere(1, 50, 50);		//����
	draw_axis();

	glRotatef(moon_gong, 0, 1, 0);	//���� ����
	glTranslatef(2, 0, 0);
	glRotatef(moon_rot, 0, 1, 0);	//���� ����

	glColor3f(0, 0.5, 1);			
	glutWireSphere(1, 15, 15);		//��
	draw_axis();			

	//�ǽ�2
	glPopMatrix();
	glPushMatrix();

	glRotatef(mars_gong, 0, 1, 0);	//����
	glTranslatef(8, 0, 0);			//�¾�� ȭ���Ÿ�
	glRotatef(mars_rot, 0, 1, 0);	//����

	glColor3f(0, 1, 1);
	glutWireSphere(1, 30, 30);		//ȭ��
	draw_axis();

	glPopMatrix();

	glRotatef(jupiter_gong, 0, 1, 0);	//����
	glTranslatef(10, 0, 0);			//�¾�� �񼺰Ÿ�
	glRotatef(jupiter_rot, 0, 1, 0);	//����

	glColor3f(1, 0, 1);
	glutWireSphere(1, 30, 30);		//��
	draw_axis();
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
	/* Windows �ʱ�ȭ */
	int submenu1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
	earth_rot = earth_rot + 3;
	if (earth_rot > 360)earth_rot -= 360;
	mars_gong = mars_gong + 0.5;
	if (mars_gong > 360)mars_gong -= 360;
	mars_rot = mars_rot + 6;
	if (mars_rot > 360)mars_rot -= 360;
	moon_gong = moon_gong + 0.1;
	if (moon_gong > 360)moon_gong -= 360;
	moon_rot = moon_rot + 0.5;
	if (moon_rot > 360)moon_rot -= 360;

	jupiter_gong = jupiter_gong + 0.05;
	if (jupiter_gong > 360)jupiter_gong -= 360;
	jupiter_rot = jupiter_rot + 0.1;
	if (jupiter_rot > 360)jupiter_rot -= 360;

	glutPostRedisplay();
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//������ ��Ʈ���� ����
	glLoadIdentity();		//������� �ʱ�ȭ
	gluPerspective(45, (float)width / (float)height, 10, 50);	//10~300 ��������, ������ �����츸ŭ ������ ����
	glMatrixMode(GL_MODELVIEW);		//�׸���� ��Ʈ���� ����
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
		se = 1 * pi / 180;			//360�� �̻��϶�, ���� 1���� �����ϰ� ��
	else if (se <= 0)
		se = 360 * pi / 180;
	printf("se=%f, fi=%f\n", se / pi * 180, fi / pi * 180);
	glutPostRedisplay();

}