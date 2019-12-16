#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H
#include<GL/freeglut.h>
#include<stdio.h>
#include"global.h"
#include"calculate.h"
#include<fstream>

void arrow(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void resize(int width, int height);
void sub_menu_function(int option);
void main_menu_function(int option);


#endif