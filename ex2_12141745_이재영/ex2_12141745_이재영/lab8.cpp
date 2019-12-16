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

float pi = 3.14;
float se = 45 * pi / 180;
float fi = 45 * pi / 180;
float r = 15;
void resize(int width, int height);
void draw_axis(void);
void arrow(int key, int x, int y);

GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
GLfloat specularLight[] = { 0.9f,0.9f,0.9f,1.0f };
GLfloat specularMaterial[] = { 1.0f,1.0f,1.0f,1.0f };



float m_RotateAngle = 0;

void init() {
	/*ȭ���� �⺻������ black ���� */

	glClearDepth(1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 20);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//depth-test enable
	glFrontFace(GL_CW); 
	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT, GL_LINE);		//���� wire��

	glEnable(GL_CULL_FACE);				//culiing
	glCullFace(GL_FRONT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//�ٸ� ���ڷ� �ٲپ� ��ȭ�� �ִ��� Ȯ���� �� ��
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}


void draw() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	draw_axis();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);*/
	if (se > 180 * pi / 180 && se <= 360 * pi / 180)	//180~360�� �϶� ������ �ݴ��
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, -1, 0);
	else
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		glRotatef(m_RotateAngle, 0, 1, 0);
		GLdouble eq[4] = { -1.0,0.0,0.0,0.0 };
		glClipPlane(GL_CLIP_PLANE0, eq);
		glEnable(GL_CLIP_PLANE0);
	glPopMatrix();

	
	glColor3f(1.0f, 1.0f, 0);
	glutSolidTeapot(5);	//TEAPOT �׸���
	draw_axis();		//��ǥ�� �׸���

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
	if (ast == 0)
		angle = angle + 0.5;
	if (angle > 360) angle -= 360;
	m_RotateAngle += 0.5;
	if (m_RotateAngle > 360) m_RotateAngle -= 360;
	glutPostRedisplay();
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//������ ��Ʈ���� ����
	glLoadIdentity();		//������� �ʱ�ȭ
	gluPerspective(45, (float)width / (float)height, 10, 20);	//10~300 ��������, ������ �����츸ŭ ������ ����
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


