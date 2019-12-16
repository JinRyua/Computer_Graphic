#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
#include "ObjParser.h"
#include"bmpfuncs.h"
#include<fstream>
using namespace std;

bool antialiase_on = false;
int point[200][2] = { {0,0}, };
int posta[200]{ 0, };
int num = 0;
double angle = 0;
int ast = 0;
void idle(void);

int mx, my,mstat;

int s='1';
int c=1;
//60 60
float pi = 3.14;
float se = 60 * pi / 180;
float fi = 60 * pi / 180;
float r = 7;
void resize(int width, int height);
void draw_axis(void);
void arrow(int key, int x, int y);
void cubeTextureMapping();
float tx, ty, tz,trot;

GLuint texname[2];

struct block {
	int name;
	int color;
	GLfloat matrix[16];
};

GLfloat temp_matrix[16];
vector<block> a;

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

int position = 0;

void init() {
	/*ȭ���� �⺻������ black ���� */
	mx = my = mstat = 0;		//���콺 �� �ʱ�ȭ
	tx = ty = tz = trot = 0;	//�⺻ ��� �ʱ�ȭ
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
	//�ٸ� ���ڷ� �ٲپ� ��ȭ�� �ִ��� Ȯ���� �� ��
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

	cubeTextureMapping();
	glEnable(GL_TEXTURE_2D);

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

void draw_string(void *font, const char* str, int x, int y) {
	unsigned int i;
	glRasterPos2i(x, y);
	for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
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
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//��������ʱ�ȭ

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (se > 180 * pi / 180 && se <= 360 * pi / 180)	//180~360�� �϶� ������ �ݴ��
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, -1, 0);
	else
		gluLookAt(r*sin(se)*cos(fi), r*cos(se), r*sin(se)*sin(fi), 0, 0, 0, 0, 1, 0);
	
	draw_axis();

	for (int i = 0; i < a.size(); i++) {
		GLfloat tempm[16];					//�����ʿ�
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


void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 500 - y);
	if (state == 0) {
		point[num][0] = x;
		point[num][1] = 500 - y;

	}
	if (button == 3 && state == 1)		//���� ����� �� Ȯ��
		if (r > 5)
			r -= 0.2;
	if (button == 4 && state == 1)		//���� �о��� �� ���
		if (r < 15)
			r += 0.2;
	if (button == 0)					//��Ŭ������ �巡�׸� �����Ҷ�
		if (state == 0) {		
			mstat = 1;					//��� flag����
			mx = x;						//Ŭ���� ��ǥ ����
			my = 500 - y;
		}
		else {
			mstat = mx = my = 0;		//�巡�װ� ������ ��
		}
	glutPostRedisplay();
}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, 500 - y);		
	int temp = 500 - y;
	if (mstat == 1) {	//�巡�� �� ��ġ�� �巡�װ� �Ǳ��� ��ġ�� ����ŭ ������ ��ȯ
		fi = fi + ((x - mx)/10)*pi / 180;		
		se = se + ((temp - my)/10)*pi / 180;
		mx = x;			//�巡�� �Ǳ� �� ��ġ ����
		my = temp;

		if (fi > 360 * pi / 180)	//���� �� ����
			fi = 1 * pi / 180;
		else if (fi <= 0)
			fi = 360 * pi / 180;

		if (se > 360 * pi / 180)
			se = 1 * pi / 180;			
		else if (se <= 0)
			se = 360 * pi / 180;
	}
	printf("se=%f, fi=%f\n", se / pi * 180, fi / pi * 180);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);
	if (key == 9) {
		se = 60 * pi / 180;
		fi = 60 * pi / 180;
		r = 7;
	}
	if (key == 'a')
		tx-=1;
	if (key == 's')
		tz+= 1;
	if (key == 'w')
		tz-= 1;
	if (key == 'd')
		tx+= 1;
	if (key == 'z')
		ty += 1;
	if (key == 'c')
		ty -= 1;
	if (key == 'q')
		if (trot <360)
			trot += 90;
		else
			trot = 0;
	if (key == 32) {
		block temp = { s,c};
		for (int i = 0; i < 16; i++)
			temp.matrix[i] = temp_matrix[i];
		a.push_back(temp);
		tx = ty = tz = trot = 0;
	}
	if (key == 'r')
		if(!a.empty())
			a.pop_back();
	printf("x=%f, y=%f, z=%f, angle=%f\n", tx, ty, tz, trot);
	if (key == 'e') {
		ofstream outFile("output.txt");
		for (int i = 0; i < a.size(); i++) {
			outFile << a.at(i).name<<' '<<a.at(i).color;
			for (int j = 0; j < 16; j++)
				outFile<<' ' << a.at(i).matrix[j];
			outFile << endl;
		}
		outFile.close();
	}
	if (key == 'l') {
		ifstream inFile("output.txt");
		while (!inFile.eof()) {
			block k;
			int tname, tcolor;
			GLfloat tMatrix[16];
			inFile >> k.name >> k.color;
			for (int j = 0; j < 16; j++)
				inFile>>k.matrix[j];
			a.push_back(k);
		}
		inFile.close();
	}
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
	/* Windows �ʱ�ȭ */
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

	glutPostRedisplay();
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//������ ��Ʈ���� ����
	glLoadIdentity();		//������� �ʱ�ȭ
	gluPerspective(45, (float)width / (float)height, 1, 300);	//1~300 ��������, ������ �����츸ŭ ������ ����
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
		c = 1;			//360�� �̻��϶�, ���� 1���� �����ϰ� ��
	else if (c <= 0)
		c = 8;

	if (fi > 360 * pi / 180)
		fi = 1 * pi / 180;
	else if (fi <= 0)
		fi = 360 * pi / 180;

	if (se > 360 * pi / 180)
		se = 1 * pi / 180;			//360�� �̻��϶�, ���� 1���� �����ϰ� ��
	else if (se <= 0)
		se = 360 * pi / 180;
	printf("se=%f, fi=%f, r=%f\n", se / pi * 180, fi / pi * 180,r);
	glutPostRedisplay();

}