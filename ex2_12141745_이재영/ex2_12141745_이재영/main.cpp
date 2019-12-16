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
	/*화면의 기본색으로 black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*화면 좌표 정보 설정*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//다른 인자로 바꾸어 변화가 있는지 확인해 볼 것
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}
void draw_point(void) {
	//점의 색을 blue로 설정
	glColor3f(0.0f, 0.0f, 1.0f);
	//점의 크기를 설정
	glPointSize(8.0f);
	//점 그리기
	glBegin(GL_POINTS);
		glVertex2i(5, 5);
		glVertex2i(200, 200);
		glVertex2i(450, 300);
	glEnd();

}

void draw_line(void) {
	//선의 굵기 설정
	glLineWidth(5.0f);
	//선의 패턴화 허용
	glEnable(GL_LINE_STIPPLE);
	//선의 패턴을 설정
	glLineStipple(5, 0x00FF);

	/*선의 색상을 빨간색으로*/
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
	//면의 색상을 빨간색으로
	//면에 효과를 주는 면과 방식 결정
	//glPolygonMode(GL_FRONT, GL_LINE);
	//면의 방향을 결정
	//glFrontFace(GL_CW);
	glBegin(GL_TRIANGLES);
		//면의 색상을 하늘색으로
		glColor4f(0.0f, 1.0f, 1.0f, 0.75);
		glVertex2i(450, 50);
		glVertex2i(450, 450);
		glVertex2i(200, 250);
		//면의 색상을 노란색으로
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
	/*화면을 깨끗하게 지우기*/
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

		/*점의 색상을 붉은 색으로*/
		glColor4f(1.0f, 0.0f, 0.0f,0.75f);
		/*점의 크기 (초기값은 1.0)*/
		glPointSize(20.0f);
		glBegin(GL_POINTS);
		//점일때 저장된 좌표를 전부 그립니다.
		if (posta[i] == 1) {
			glVertex2i(point[i][0], point[i][1]);
		}
		glEnd();

		glLineWidth(10.0f);
		//glEnable(GL_LINE_STIPPLE);
		//glLineStipple(3, 0xAAAA);

		/*선의 색상을 노란색으로*/
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		while (1) {
			//선일때 입력된 좌표일때 그리기
			if (posta[i] == 2) {
				glVertex2i(point[i][0], point[i][1]);
				//선분은 연속적인 점이므로 다음 좌표도 선이라면
				//다음 좌표가 선이 아닐때까지 그리기
				if (posta[i + 1] == 2&&i!=num-1)
					i++;
				else break;
			}
			//좌표개수의 끝에 도달했을때는 break;
			else break;
		}
		glEnd();

		/*면의 색상을 노란색으로*/
		glColor4f(1.0f, 1.0f, 0.0f,0.75f);
	//	glPolygonMode(GL_FRONT);
		glFrontFace(GL_CW);
		glBegin(GL_TRIANGLES);
		while (1) {
			if (posta[i] == 3) {
				glVertex2i(point[i][0], point[i][1]);
				//삼각형은 연속적인 점이므로 다음 좌표도 면이라면
				//다음 좌표가 면이 아닐때까지 그리기
				if (posta[i + 1] == 3&&i!=num-1)
					i++;
				else break;
			}
			//좌표개수의 끝에 도달했을때는 break;
			else break;
		}

		glEnd();
	}
	
	//단순 point,line,triangle을 그리는 함수
	//draw_point();
	//draw_line();
	//draw_triangle();
	

	///* Teapot 1개를 그리는 임시 루틴*/
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

	glutMainLoop();

	return 0;
}

void idle(void) {
	if(ast==0)
		angle = angle + 0.5;
	if (angle > 360) angle -= 360;
	glutPostRedisplay();
}
