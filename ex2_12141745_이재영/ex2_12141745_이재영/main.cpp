#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
using namespace std;

bool antialiase_on = false;
int point[200][2]={ {0,0}, };
int posta[200]{ 0, };
int num = 0;
int stat = 1;
double angle = 0;
int ast = 0;
void idle(void);

void init() {
	/*ȭ���� �⺻������ black ���� */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*ȭ�� ��ǥ ���� ����*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//�ٸ� ���ڷ� �ٲپ� ��ȭ�� �ִ��� Ȯ���� �� ��
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}
void draw_point(void) {
	//���� ���� blue�� ����
	glColor3f(0.0f, 0.0f, 1.0f);
	//���� ũ�⸦ ����
	glPointSize(8.0f);
	//�� �׸���
	glBegin(GL_POINTS);
		glVertex2i(5, 5);
		glVertex2i(200, 200);
		glVertex2i(450, 300);
	glEnd();

}

void draw_line(void) {
	//���� ���� ����
	glLineWidth(5.0f);
	//���� ����ȭ ���
	glEnable(GL_LINE_STIPPLE);
	//���� ������ ����
	glLineStipple(5, 0x00FF);

	/*���� ������ ����������*/
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(50, 50);
		glVertex2i(250, 450);
		glVertex2i(300, 450);
		glVertex2i(400, 100);
		glVertex2i(100, 100);
	glEnd();
}

void draw_triangle(void) {
	//���� ������ ����������
	//�鿡 ȿ���� �ִ� ��� ��� ����
	//glPolygonMode(GL_FRONT, GL_LINE);
	//���� ������ ����
	//glFrontFace(GL_CW);
	glBegin(GL_TRIANGLES);
		//���� ������ �ϴû�����
		glColor4f(0.0f, 1.0f, 1.0f, 0.75);
		glVertex2i(450, 50);
		glVertex2i(450, 450);
		glVertex2i(200, 250);
		//���� ������ ���������
		glColor4f(1.0f, 1.0f, 0.0f,0.75f);
		glVertex2i(50, 50);
		glVertex2i(50, 450);
		glVertex2i(300, 250);
		
	glEnd();
}

void draw_string(void* font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);
	/*for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}*/
	glutBitmapString(font, (unsigned char*)str);
}

void draw() {
	/*ȭ���� �����ϰ� �����*/
	if (antialiase_on == true)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Graphics are cool!!", 10, 10);
	glColor3f(0.5f, 1.0f, 0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "I Like Computer Graphics!!", 250, 475);

	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(250, 250, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-250, -250, 0);


	for (int i = 0; i < num; i++) {

		/*���� ������ ���� ������*/
		glColor4f(1.0f, 0.0f, 0.0f,0.75f);
		/*���� ũ�� (�ʱⰪ�� 1.0)*/
		glPointSize(20.0f);
		glBegin(GL_POINTS);
		//���϶� ����� ��ǥ�� ���� �׸��ϴ�.
		if (posta[i] == 1) {
			glVertex2i(point[i][0], point[i][1]);
		}
		glEnd();

		glLineWidth(10.0f);
		//glEnable(GL_LINE_STIPPLE);
		//glLineStipple(3, 0xAAAA);

		/*���� ������ ���������*/
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		while (1) {
			//���϶� �Էµ� ��ǥ�϶� �׸���
			if (posta[i] == 2) {
				glVertex2i(point[i][0], point[i][1]);
				//������ �������� ���̹Ƿ� ���� ��ǥ�� ���̶��
				//���� ��ǥ�� ���� �ƴҶ����� �׸���
				if (posta[i + 1] == 2&&i!=num-1)
					i++;
				else break;
			}
			//��ǥ������ ���� ������������ break;
			else break;
		}
		glEnd();

		/*���� ������ ���������*/
		glColor4f(1.0f, 1.0f, 0.0f,0.75f);
	//	glPolygonMode(GL_FRONT);
		glFrontFace(GL_CW);
		glBegin(GL_TRIANGLES);
		while (1) {
			if (posta[i] == 3) {
				glVertex2i(point[i][0], point[i][1]);
				//�ﰢ���� �������� ���̹Ƿ� ���� ��ǥ�� ���̶��
				//���� ��ǥ�� ���� �ƴҶ����� �׸���
				if (posta[i + 1] == 3&&i!=num-1)
					i++;
				else break;
			}
			//��ǥ������ ���� ������������ break;
			else break;
		}

		glEnd();
	}
	
	//�ܼ� point,line,triangle�� �׸��� �Լ�
	//draw_point();
	//draw_line();
	//draw_triangle();
	

	///* Teapot 1���� �׸��� �ӽ� ��ƾ*/
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glutWireTeapot(0.5f);
	glFlush();
	glutSwapBuffers();
}


void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x,500-y);
	if(state==0){
		point[num][0] = x;
		point[num][1] = 500-y;
		posta[num] = stat;
		num++;
	}
	glutPostRedisplay();
}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, 500-y);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);
	if (key == 'a')
		antialiase_on=!antialiase_on;
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

	glutMainLoop();

	return 0;
}

void idle(void) {
	if(ast==0)
		angle = angle + 0.5;
	if (angle > 360) angle -= 360;
	glutPostRedisplay();
}
