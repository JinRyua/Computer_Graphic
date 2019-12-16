#include<GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<math.h>
#include "ObjParser.h"
#include"bmpfuncs.h"
#include<fstream>
#include<GL/glext.h>
#include<algorithm>
#include"global.h"
using namespace std;
//bool antialiase_on = false;
//int num = 0;
//double angle = 0;
//int ast = 0;
//int mx, my, mstat;
//int s = '1';
//int c = 1;
//float pi = 3.14;
//float se = 60 * pi / 180;
//float fi = 60 * pi / 180;
//float r = 7;
//float tx, ty, tz, trot;
//int g_nSkySize = 500;
//struct vec {
//	float x;
//	float y;
//	float z;
//};
//GLuint texname[2];
//GLuint g_nCubeTex;
//struct block {
//	int name;
//	int color;
//	GLfloat matrix[16];
//	vec crash[2];
//};
//GLfloat temp_matrix[16];
//vector<block> a;
//float co[9][3] = { {0,0,0}, {1.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f}
//				   , {0.0f,0.0f,1.0f}, {1.0f,1.0f,0.0f}, {1.0f,0.0f,1.0f}
//			   , {0.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f} };
//GLfloat ambientLight[] = { 0.4f,0.4f,0.4f,1.0f };
//GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,1.0f };
//GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };
//GLfloat ambient_sun[] = { 0.2f,0.2f,0.2f,1.0f };
//GLfloat diffuse_sun[] = { 1.0f,1.0f,1.0f,1.0f };
//GLfloat specular_sun[] = { 1.0f,1.0f,1.0f,1.0f };
//GLfloat light_position[] = { 0.0f,0.0f,0.0f,1.0f };
//int position = 0;


vec find_vec(int s, int count);
vec calculate_vec(vec input, GLfloat mat[]);
void calculate_mat();
bool check_crash();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
bool check_crash();
void resize(int width, int height);
void draw_axis(void);
void arrow(int key, int x, int y);
void cubeTextureMapping();
void mapcubeTextureMapping();
void draw_map();
void DrawLego(int index, int color);
float inner_product(vec a, vec b);
void sub_menu_function(int option);
void main_menu_function(int option);


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



void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 500 - y);
	if (button == 3 && state == 1)		//휠을 당겼을 때 확대
		if (r > 5)
			r -= 0.2;
	if (button == 4 && state == 1)		//휠을 밀었을 때 축소
		if (r < 15)
			r += 0.2;
	if (button == 0)					//좌클릭으로 드래그를 시작할때
		if (state == 0) {
			mstat = 1;					//모션 flag설정
			mx = x;						//클릭된 좌표 저장
			my = 500 - y;
		}
		else {
			mstat = mx = my = 0;		//드래그가 끝났을 때
		}
	glutPostRedisplay();
}

void motion(int x, int y) {
	printf("Mouse is moving! (%d, %d)\n", x, 500 - y);
	int temp = 500 - y;
	if (mstat == 1) {	//드래그 된 위치와 드래그가 되기전 위치의 차만큼 각도로 변환
		fi = fi + ((x - mx) / 10)*pi / 180;
		se = se + ((temp - my) / 10)*pi / 180;
		mx = x;			//드래그 되기 전 위치 갱신
		my = temp;

		if (fi > 360 * pi / 180)	//각도 값 설정
			fi = 1 * pi / 180;
		else if (fi <= 0)
			fi = 360 * pi / 180;

		if (se > 360 * pi / 180)
			se = 1 * pi / 180;
		else if (se > 85 * pi / 180)
			se = 85 * pi / 180;
	}
	printf("se=%f, fi=%f\n", se / pi * 180, fi / pi * 180);
	glutPostRedisplay();
}


vec calculate_vec(vec input, GLfloat mat[]) {
	vec temp;

	temp.x = input.x * mat[0] + input.y * mat[4]
		+ input.z * mat[8] + 1 * mat[12];
	temp.y = input.x * mat[1] + input.y * mat[5]
		+ input.z * mat[9] + 1 * mat[13];
	temp.z = input.x * mat[2] + input.y * mat[6]
		+ input.z * mat[10] + 1 * mat[14];
	float one = input.x * mat[3] + input.y * mat[7]
		+ input.z * mat[11] + 1 * mat[15];
	temp.x = temp.x / one;
	temp.y = temp.y / one;
	temp.z = temp.z / one;

	return temp;
}

vec find_vec(int s, int count) {
	vec temp;
	if (count == 1) {
		switch (s) {
		case '1':
			temp.x = 0.5;
			temp.y = 1;
			temp.z = -0.5;
			break;
		case '2':
			temp.x = 1;
			temp.y = 1;
			temp.z = -0.5;
			break;
		case '3':
			temp.x = 1.5;
			temp.y = 1;
			temp.z = -0.5;
			break;
		case '4':
		case '6':
			temp.x = 1;
			temp.y = 1;
			temp.z = -1;
			break;
		case '5':
			temp.x = 0.5;
			temp.y = 2;
			temp.z = -0.5;
			break;
		}

	}
	else {
		switch (s) {
		case '1':
		case '5':
			temp.x = -0.5;
			temp.y = 0;
			temp.z = 0.5;
			break;
		case '2':
			temp.x = -1;
			temp.y = 0;
			temp.z = 0.5;
			break;
		case '3':
			temp.x = -1.5;
			temp.y = 0;
			temp.z = 0.5;
			break;
		case '4':
		case '6':
			temp.x = -1;
			temp.y = 0;
			temp.z = 1;
			break;


		}

	}
	return temp;
}

void calculate_mat() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(tx, ty, tz);
	glRotatef(trot, 0, 1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, temp_matrix);
	glPopMatrix();
}

bool check_crash() {
	vec temp[2];
	for (int i = 0; i < 2; i++) {
		temp[i] = find_vec(s, i);
		temp[i] = calculate_vec(temp[i], temp_matrix);
	}
	for (int i = 0; i < a.size(); i++) {
		int check = 0;
		float x[2];
		block temp2 = a.at(i);
		x[0] = (max(temp[0].x, temp[1].x) - min(temp[0].x, temp[1].x)) / 2;
		x[1] = (max(temp2.crash[0].x, temp2.crash[1].x) - min(temp2.crash[0].x, temp2.crash[1].x)) / 2;
		float h1 = (max(temp[0].x, temp[1].x) + min(temp[0].x, temp[1].x)) / 2;
		float h2 = (max(temp2.crash[0].x, temp2.crash[1].x) + min(temp2.crash[0].x, temp2.crash[1].x)) / 2;
		h1 = max(h1, h2) - min(h1, h2);
		printf("%f,%f\n", h1, x[0] + x[1]);
		if (h1 < x[0] + x[1])
			check++;

		x[0] = (max(temp[0].y, temp[1].y) - min(temp[0].y, temp[1].y)) / 2;
		x[1] = (max(temp2.crash[0].y, temp2.crash[1].y) - min(temp2.crash[0].y, temp2.crash[1].y)) / 2;
		h1 = (max(temp[0].y, temp[1].y) + min(temp[0].y, temp[1].y)) / 2;
		h2 = (max(temp2.crash[0].y, temp2.crash[1].y) + min(temp2.crash[0].y, temp2.crash[1].y)) / 2;
		h1 = max(h1, h2) - min(h1, h2);
		printf("%f,%f\n", h1, x[0] + x[1]);
		if (h1 < x[0] + x[1])
			check++;

		x[0] = (max(temp[0].z, temp[1].z) - min(temp[0].z, temp[1].z)) / 2;
		x[1] = (max(temp2.crash[0].z, temp2.crash[1].z) - min(temp2.crash[0].z, temp2.crash[1].z)) / 2;
		h1 = (max(temp[0].z, temp[1].z) + min(temp[0].z, temp[1].z)) / 2;
		h2 = (max(temp2.crash[0].z, temp2.crash[1].z) + min(temp2.crash[0].z, temp2.crash[1].z)) / 2;
		h1 = max(h1, h2) - min(h1, h2);
		printf("%f,%f\n", h1, x[0] + x[1]);
		if (h1 < x[0] + x[1])
			check++;

		if (check == 3)
			return true;
	}
	return false;
}


void keyboard(unsigned char key, int x, int y) {
	printf("You pressed %c\n", key);
	if (key == 9) {
		se = 60 * pi / 180;
		fi = 60 * pi / 180;
		r = 7;
	}
	if (key == 'a') {
		tx -= 0.2;
		calculate_mat();
		if (check_crash() == true) {
			tx += 0.2;
			calculate_mat();
		}
	}
	if (key == 's') {
		tz += 0.2;
		calculate_mat();
		if (check_crash() == true) {
			tz -= 0.2;
			calculate_mat();
		}
	}
	if (key == 'w') {
		tz -= 0.2;
		calculate_mat();
		if (check_crash() == true) {
			tz += 0.2;
			calculate_mat();
		}
	}
	if (key == 'd') {
		tx += 0.2;
		calculate_mat();
		if (check_crash() == true) {
			tx -= 0.2;
			calculate_mat();
		}
	}
	if (key == 'z') {
		ty += 0.2;
		calculate_mat();
		if (check_crash() == true) {
			ty -= 0.2;
			calculate_mat();
		}
	}
	if (key == 'c') {
		ty -= 0.2;
		calculate_mat();
		if (check_crash() == true) {
			ty += 0.2;
			calculate_mat();
		}
	}
	if (key == 'q')
		if (trot < 360)
			trot += 90;
		else
			trot = 0;
	if (key == 32) {
		block temp = { s,c };
		for (int i = 0; i < 16; i++)
			temp.matrix[i] = temp_matrix[i];

		vec tempvec, tempvec2;
		for (int i = 0; i < 2; i++) {
			tempvec = find_vec(s, i);					//바운딩 박스 좌표 계산 및 저장
			tempvec2 = calculate_vec(tempvec, temp_matrix);
			temp.crash[i] = tempvec2;
		}

		a.push_back(temp);
		tx = ty = tz = trot = 0;
	}
	if (key == 'r')
		if (!a.empty())
			a.pop_back();
	printf("x=%f, y=%f, z=%f, angle=%f\n", tx, ty, tz, trot);
	if (key == 'e') {
		ofstream outFile("output.txt");
		for (int i = 0; i < a.size(); i++) {
			outFile << a.at(i).name << ' ' << a.at(i).color;
			for (int j = 0; j < 16; j++)
				outFile << ' ' << a.at(i).matrix[j];
			for (int j = 0; j < 2; j++)
				outFile << ' ' << a.at(i).crash[j].x << ' ' << a.at(i).crash[j].y
				<< ' ' << a.at(i).crash[j].z;
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
				inFile >> k.matrix[j];
			for (int j = 0; j < 2; j++)
				inFile >> k.crash[j].x >> k.crash[j].y >>
				k.crash[j].z;
			a.push_back(k);
		}
		inFile.close();
	}
	if (key == 'z')
		ast = !ast;

	glutPostRedisplay();
}