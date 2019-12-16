#include"calculate.h"
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

