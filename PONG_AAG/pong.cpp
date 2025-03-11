#include <GL/glut.h>
#include <cmath>
#include <iostream>

// TAMAÑO Y ESTÉTICA

	// DIMENSIONES DE VENTANA
const int VENTANA_WIDTH = 1000;
const int VENTANA_HEIGHT = 800;
	
	// DIMENSIONES DE LAS PALETAS
const float PALETA_WIDTH = 25.0f;
const float PALETA_HEIGHT = 100.0f;

	//POSICIÓN DE LAS PALETAS
float izqPaletaY = 0.0f;
float derPaletaY = 0.0f;

	// DIMENSIONES DE LA PELOTA
const float PELOTA_TAMANO = 15.0f;
float pelotaX = VENTANA_WIDTH / 2.0f;
float pelotaY = VENTANA_HEIGHT / 2.0f;
float pelotaVelX = 4.0f;
float pelotaVelY = 4.0f;
const float PELOTA_VEL_INCREMENT = 0.1f;

	// VELOCIDAD DE LA PELOTA
float velPelotaX = 10.0f;
float velPelotY = 10.0f;

	// MARCADOR DE PUNTOS
int izqPuntos = 0;
int derPuntos = 0;

// FUNCIONES
void display();
void keyboard(unsigned char, int, int);
void teclasAB(int, int, int);
void update(int);
void reshape(int, int);
void drawPaleta(float x, float y);
void drawPelota(float x, float y);
void drawTexto(float x, float y, const char* text);

// MAIN
int main(int argc, char** argv) {

	// INICIALIZACIÓN DE GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(VENTANA_WIDTH, VENTANA_HEIGHT);
	glutCreateWindow("PONG");

	// CALLBACKS 
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, update, 0);

	// COLOR VENTANA
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// LOOP GLUT
	glutMainLoop();
	return 0;
}

// DISPLAY
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	// DIBUJAR PALETAS
	drawPaleta(0.0f, izqPaletaY);
	drawPaleta(VENTANA_WIDTH - PALETA_WIDTH, derPaletaY);

	// DIBUJAR PELOTA
	drawPelota(pelotaX, pelotaY);
	glutSwapBuffers();

	// MARCADOR DE PUNTOS
	char marPuntos[100];
	sprintf_s(marPuntos, "IZQ: %d  DER: %d", izqPuntos, derPuntos);
	drawTexto(VENTANA_WIDTH / 2 - 100, VENTANA_HEIGHT - 60, marPuntos);

}

// ADAPTACIÓN A LA VENTANA
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, VENTANA_WIDTH, 0.0, VENTANA_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

// CONTROLES DEL JUEGO
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		izqPaletaY += 20.0f;
		if (izqPaletaY + PALETA_HEIGHT / 2 > VENTANA_HEIGHT)
			izqPaletaY = VENTANA_HEIGHT - PALETA_HEIGHT / 2;
			break;
	case 's':
		izqPaletaY -= 20.f;
		if (izqPaletaY - PALETA_HEIGHT / 2 < 0)
			izqPaletaY = PALETA_HEIGHT / 2;
			break;
	case 'i':
		derPaletaY += 20.0f;
		if (derPaletaY + PALETA_HEIGHT / 2 > VENTANA_HEIGHT)
			derPaletaY = VENTANA_HEIGHT - PALETA_HEIGHT / 2;
		break;
	case 'k':
		derPaletaY -= 20.0f;
		if (derPaletaY - PALETA_HEIGHT / 2 < 0)
			derPaletaY = PALETA_HEIGHT / 2;
		break;
	}
	glutPostRedisplay();
}

/*void teclasAB(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		derPaletaY += 20.0f;
		if (derPaletaY + PALETA_HEIGHT / 2 > VENTANA_HEIGHT)
			derPaletaY = VENTANA_HEIGHT - PALETA_HEIGHT / 2;
		break;
	case GLUT_KEY_DOWN:
		derPaletaY -= 20.0f;
		if (derPaletaY - PALETA_HEIGHT / 2 < 0) 
			derPaletaY = PALETA_HEIGHT / 2;
		break;
	}
	glutPostRedisplay();
}*/

// UPDATE
void update(int value) {
	// POSICIÓN PELOTA
	pelotaX += pelotaVelX;
	pelotaY += pelotaVelY;

	// PELOTA CHOCANDO  CON LA PARED
	if (pelotaY + PELOTA_TAMANO / 2 > VENTANA_HEIGHT || pelotaY - PELOTA_TAMANO / 2 < 0) {
		pelotaVelX = -pelotaVelY;
	}

	// PELOTA CHOCANDO CON LAS PALETAS
	if (pelotaX - PELOTA_TAMANO / 2 < PALETA_WIDTH && pelotaY > izqPaletaY + PALETA_HEIGHT / 2 && pelotaY < izqPaletaY + PALETA_HEIGHT / 2){
		pelotaVelX = -pelotaVelX;
		//pelotaVelX += (pelotaVelX > 0) ? PELOTA_VEL_INCREMENT : -PELOTA_VEL_INCREMENT;
	}

	if (pelotaX + PELOTA_TAMANO / 2 > VENTANA_WIDTH && pelotaY > izqPaletaY - PALETA_HEIGHT / 2 && pelotaY < izqPaletaY + PALETA_HEIGHT / 2) {
		pelotaVelX = -pelotaVelX;
	}
	
	glutPostRedisplay();
	glutTimerFunc(16, update, 0);
}

// DIBUJAR 
// PALETAS
void drawPaleta(float x, float y) {
	glBegin(GL_QUADS);
	glVertex2f(x, y - PALETA_WIDTH / 2);
	glVertex2f(x + PALETA_WIDTH, y - PALETA_HEIGHT / 2);
	glVertex2f(x + PALETA_WIDTH, y + PALETA_HEIGHT / 2);
	glVertex2f(x, y + PALETA_HEIGHT / 2);
	glEnd();
}

// PELOTA
void drawPelota(float x, float y) {
	glBegin(GL_QUADS);
	glVertex2f(x - PELOTA_TAMANO / 2, y - PELOTA_TAMANO / 2);
	glVertex2f(x + PELOTA_TAMANO / 2, y - PELOTA_TAMANO / 2);
	glVertex2f(x + PELOTA_TAMANO / 2, y + PELOTA_TAMANO / 2);
	glVertex2f(x - PELOTA_TAMANO / 2, y + PELOTA_TAMANO / 2);
	glEnd();
}

// TEXTO
void drawTexto(float x, float y, const char* texto) {
	glRasterPos2d(x, y);
	while (*texto) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto);
		texto++;
	}
}

