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
	/*화면의 기본색으로 black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*화면 좌표 정보 설정*//*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);*/


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//다른 인자로 바꾸어 변화가 있는지 확인해 볼 것
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}
//void draw_point(void) {
//	//점의 색을 blue로 설정
//	glColor3f(0.0f, 0.0f, 1.0f);
//	//점의 크기를 설정
//	glPointSize(8.0f);
//	//점 그리기
//	glBegin(GL_POINTS);
//		glVertex2i(5, 5);
//		glVertex2i(200, 200);
//		glVertex2i(450, 300);
//	glEnd();
//
//}
//
//void draw_line(void) {
//	//선의 굵기 설정
//	glLineWidth(5.0f);
//	//선의 패턴화 허용
//	glEnable(GL_LINE_STIPPLE);
//	//선의 패턴을 설정
//	glLineStipple(5, 0x00FF);
//
//	/*선의 색상을 빨간색으로*/
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
//	//면의 색상을 빨간색으로
//	//면에 효과를 주는 면과 방식 결정
//	//glPolygonMode(GL_FRONT, GL_LINE);
//	//면의 방향을 결정
//	//glFrontFace(GL_CW);
//	glBegin(GL_TRIANGLES);
//		//면의 색상을 하늘색으로
//		glColor4f(0.0f, 1.0f, 1.0f, 0.75);
//		glVertex2i(450, 50);
//		glVertex2i(450, 450);
//		glVertex2i(200, 250);
//		//면의 색상을 노란색으로
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
	glLoadIdentity();	//단위행렬초기화
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	glColor3f(1, 0, 0);
	glutWireSphere(1.3,50,50);		//태양
	draw_axis();
	
	glPushMatrix();

	glRotatef(earth_gong, 0, 1, 0);	//공전
	draw_axis();
	glTranslatef(6, 0, 0);			//태양과 지구 거리
	draw_axis();
	glRotatef(earth_rot, 0, 1, 0);	//자전
	
	glColor3f(0, 0, 1);
	glutWireSphere(1, 50, 50);		//지구
	draw_axis();

	glRotatef(moon_gong, 0, 1, 0);	//달의 공전
	glTranslatef(2, 0, 0);
	glRotatef(moon_rot, 0, 1, 0);	//달의 자전

	glColor3f(0, 0.5, 1);			
	glutWireSphere(1, 15, 15);		//달
	draw_axis();			

	//실습2
	glPopMatrix();
	glPushMatrix();

	glRotatef(mars_gong, 0, 1, 0);	//공전
	glTranslatef(8, 0, 0);			//태양과 화성거리
	glRotatef(mars_rot, 0, 1, 0);	//자전

	glColor3f(0, 1, 1);
	glutWireSphere(1, 30, 30);		//화성
	draw_axis();

	glPopMatrix();

	glRotatef(jupiter_gong, 0, 1, 0);	//공전
	glTranslatef(10, 0, 0);			//태양과 목성거리
	glRotatef(jupiter_rot, 0, 1, 0);	//자전

	glColor3f(1, 0, 1);
	glutWireSphere(1, 30, 30);		//목성
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
	/* Windows 초기화 */
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
	glMatrixMode(GL_PROJECTION);	//시점용 매트릭스 설정
	glLoadIdentity();		//단위행렬 초기화
	gluPerspective(45, (float)width / (float)height, 10, 50);	//10~300 범위에서, 변경한 윈도우만큼 시점을 변경
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