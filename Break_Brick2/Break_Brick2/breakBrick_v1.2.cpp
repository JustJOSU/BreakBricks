//					//
//		수정중		//
//					//

#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct point {
	double x, y;
};
int Width = 800, Height = 800; // 윈도우 창 크기 지정
int xScale = 50, yScale = 10; // paddle의 가로길이
int bWidth = 75, bHeight = 25; // 벽돌의 가로길이와 세로길이
int radius = 7;
GLfloat brickColor[][3] = { {1.0, 0.1, 0.0},
							{0.7, 0.2, 0.0 },
							{0.7, 0.3, 0.1},
							{0.7, 0.4, 0.2 },
							{1.0, 1.0, 1.0} };;
int bCountArray[5][6];

class brick {
public:
	point pBrick;
	int brickCount;
	brick() {

	}
	void buildBrick(point p) {
		pBrick = p;
		switch (brickCount)
		{
		case 5:
			glColor3fv(brickColor[0]);
			break;
		case 4:
			glColor3fv(brickColor[1]);
			break;
		case 3:
			glColor3fv(brickColor[2]);
			break;
		case 2:
			glColor3fv(brickColor[3]);
			break;
		case 1:
			glColor3fv(brickColor[4]);
			break;
		default:
			break;
		}

		glBegin(GL_QUADS);
		glVertex2d(pBrick.x, pBrick.y);
		glVertex2d(pBrick.x + bWidth, pBrick.y);
		glVertex2d(pBrick.x + bWidth, pBrick.y - bHeight);
		glVertex2d(pBrick.x, pBrick.y - bHeight);
		glEnd();

		glFlush();
	}
};
brick setbrick[5][6];
int breakerA[5][6];

float brickPointX = 100, brickPorintY = 700; //벽돌이 생성될 첫 위치
double x = 400, y = 50; // 공의 위치
double padX = 400, padY = 25; // paddle 위치 
float spdX = 0 ,spdY = 0; // 공의 x축 y축 방향 속도
const int leftBound = 0, topBound = 800, rightBound = 800, lowerBound = -10; // 윈도우 창과의 충돌 범위
bool leftPressed = false, rightPressed = false;


void brickGen();
void keyRelease(int, int, int);
void keyPressed(int, int, int);
void drawBall();

void moveBall() {
	if (x+radius == rightBound) { spdX *= -1.0; }
	if (x+radius == leftBound) { spdX = 0.5; }
	if (y+radius == topBound) { spdY *= -1.0; }
	if (y == lowerBound) { spdX = 0; spdY = 0; x = 400; y = 50; }
	if (x >= padX - 50 && x <= padX + 50 && y == padY + 10) {
		spdY *= -1;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (breakerA[i][j] == 1) {
				//top
				if (x + radius >= (brickPointX * (j + 1)) && x + radius <= (brickPointX * (j + 1)) + bWidth && (y - radius) == (brickPorintY - (50 * i))) {
					spdY *= -1;
					setbrick[i][j].brickCount--;
					if (setbrick[i][j].brickCount == 0) breakerA[i][j] = 0;
				}
				//bottom
				if (x + radius >= (brickPointX * (j + 1)) && x + radius<= (brickPointX * (j + 1)) + bWidth && (y + radius) == (brickPorintY - (50 * i)) - bHeight) {
					spdY *= -1;
					setbrick[i][j].brickCount--;
					if (setbrick[i][j].brickCount == 0) breakerA[i][j] = 0;
				}
				//left
				if ((x + radius) == (brickPointX * (j + 1)) && y + radius >= (brickPorintY - (50 * i)) - bHeight && y + radius<= (brickPorintY - (50 * i))) {
					spdX *= -1;
					setbrick[i][j].brickCount--;
					if (setbrick[i][j].brickCount == 0) breakerA[i][j] = 0;
				}
				//right
				if ((x - radius) == (brickPointX * (j + 1)) + bWidth && y + radius >= (brickPorintY - (50 * i)) - bHeight && y + radius <= (brickPorintY - (50 * i))) {
					spdX *= -1;
					setbrick[i][j].brickCount--;
					if (setbrick[i][j].brickCount == 0) breakerA[i][j] = 0;
				}
			}
		}
	}
	x += spdX;
	y += spdY;
}

void brickGen() {

	point st;
	st.x = 100;
	st.y = 700;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {

			if (breakerA[i][j] == 1) {
				setbrick[i][j].buildBrick(st);
			}
			st.x += 100;
		}
		st.x = 100;
		st.y -= 50;
	}
}
void drawBall() {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	for (float deg = 0; deg < (10); deg += 0.01)
	{
		glVertex2f((x + sin(deg) * radius), (y + (cos(deg)) * radius));
	}
	glEnd();
	glFlush();
}

void keyPressed(int key, int i, int t) {

	switch (key) {

	case GLUT_KEY_LEFT:
		leftPressed = true;
		if (rightPressed == false && padX != 20) {
			padX = padX - 50;
			cout << padX;
			break;
		}
		else break;

	case GLUT_KEY_RIGHT:
		rightPressed = true;
		if (leftPressed == false && padX != 620) {
			padX = padX + 50;
			cout << padX;
			break;
		}
		else break;


	case GLUT_KEY_UP:
		spdX = 0.5;
		spdY = 0.5;
		break;

	case GLUT_KEY_F1:
		xScale = 300;
		break;
	case GLUT_KEY_F2:
		xScale = 50;
		break;
	}
}


void keyRelease(int key, int i, int t) {
	switch (key) {

	case GLUT_KEY_LEFT:
		leftPressed = false;
		break;

	case GLUT_KEY_RIGHT:
		if (padX + xScale >= 800) {
			padX = 750;
		}
		rightPressed = false;
		break;
	}
}

void drawPaddle() {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2d(padX, padY);
	glVertex2d(padX + xScale, padY);
	glVertex2d(padX + xScale, padY + yScale);
	glVertex2d(padX - xScale, padY + yScale);
	glVertex2d(padX - xScale, padY);
	glEnd();
	glFlush();
}


void init() {
	srand((unsigned int)time(0));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			bCountArray[i][j] = (rand() % 5) + 1;
			setbrick[i][j].brickCount = (bCountArray[i][j]);
			breakerA[i][j] = rand() % 2;
			cout << breakerA[i][j];
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	brickGen();
	drawPaddle();
	drawBall();
	moveBall();
	glutSwapBuffers();
	
	glutPostRedisplay();
}
void Reshape(int w, int h) {
	glViewport(0, 0, Width, Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);
}
void mouseMotion(int x, int y) {
	padX = x;
}
void initGame() {
	init();
	x = 400;
	y = 50;
	spdX = 0;
	spdY = 0;
}
void keyBoard(unsigned char key, int kx, int ky) {
	switch (key)
	{
	case 'r':
		initGame();
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bricks");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(keyPressed);
	glutSpecialUpFunc(keyRelease);
	glutPassiveMotionFunc(mouseMotion);
	glutMainLoop();
}