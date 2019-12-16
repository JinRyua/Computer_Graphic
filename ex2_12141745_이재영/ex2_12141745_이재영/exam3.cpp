#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;

void resize(int width, int height);

void init() {
	/*화면의 기본색으로 black 설정 */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	//다른 인자로 바꾸어 변화가 있는지 확인해 볼 것
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//단위행렬초기화
	gluLookAt(7, 5, 8, 0, 0, 0, 0, 1, 0);	//(7,5,8)에서 (0,0,0)을 (0,1,0)업벡터로 보기

	glTranslatef(0,1, 0);	//Modeling trasform
	glColor3f(1.0f, 0, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(3, -2, 1);
	glVertex3f(-5, 3, -1);
	glVertex3f(0, 3, -1);
	glEnd();

	glFlush();
	glutSwapBuffers();

}


void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 600 - y);
	glutPostRedisplay();
}



int main(int argc, char** argv) {
	/* Windows 초기화 */
	int submenu1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);	//window size = 800,600
	glutInitWindowPosition(300, 300);
	glutCreateWindow("My First GL Program");
	init();


	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutReshapeFunc(resize);
	glutMainLoop();

	return 0;
}


void resize(int width, int height) {
	glViewport(0, 0, width, height);	//viewport를 0,0에서 800,600
	glMatrixMode(GL_PROJECTION);	//시점용 매트릭스 설정
	glLoadIdentity();		//단위행렬 초기화
	gluPerspective(45, 4.0f/3.0f, 1, 50);	//1~50 범위에서, aspect,fovy만큼 perspective
	glMatrixMode(GL_MODELVIEW);		//그리기용 매트릭스 설정
	printf("resize complete, width=%d, height=%d\n", width, height);
}
