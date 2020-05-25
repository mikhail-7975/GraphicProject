#include "GL20GUI.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include <iostream>

void GL20GUI::Label(int x, int y, int w, int h, const char * pText)
{
	// http://stackoverflow.com/questions/9430852/glutbitmapcharacter-positions-text-wrong

	// TODO: Task03
	

	glRasterPos2f((GLfloat)x / (GLfloat)w, (GLfloat)y / (GLfloat)h);//Задание позиции (x, y) в окне

	for (size_t i = 0; i < strlen(pText); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)pText[i]);//вывод bitmap-символа
		//std::cout « pText[i] « std::endl;
	}
	
	//    
	
}
 
