#include"interaction.h"
#include"global.h"
#include"calculate.h"
using namespace std;


void mouse(int button, int state, int x, int y) {
	printf("Mouse button is clicked! (%d, %d, %d, %d)\n", button, state, x, 500 - y);
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
		fi = fi + ((x - mx) / 10)*pi / 180;
		se = se + ((temp - my) / 10)*pi / 180;
		mx = x;			//�巡�� �Ǳ� �� ��ġ ����
		my = temp;

		if (fi > 360 * pi / 180)	//���� �� ����
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
			tempvec = find_vec(s, i);					//�ٿ�� �ڽ� ��ǥ ��� �� ����
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