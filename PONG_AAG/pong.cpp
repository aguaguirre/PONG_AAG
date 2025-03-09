#include <GL/glut.h>
#include <math.h>
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
const float PELOTA_WIDTH = 15.0f;
const float PELOTA_HEIGHT = 15.0f;

	// VELOCIDAD DE LA PELOTA
float velPelotaX = 10.0f;
float velPelotY = 10.0f;

	// MARCADOR DE PUNTOS
int izqPuntos = 0;
int derPuntos = 0;

// FUNCIONES
void display();
void keyboard(unsigned char, int, int);
void update(int);
void drawPaleta(float x, float y);
void drawPelota(float x, float y);
void drawTexto(float x, float y, const char* text);

int main(int argc, char** argv) {

	// INICIALIZACIÓN DE GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(VENTANA_WIDTH, VENTANA_HEIGHT);
	glutCreateWindow("PONG");

	// CALLBACKS 
	//utDisplayFunc(display);
	//utKeyboardFunc(keyboard);
}

void display() {
	drawPaleta(0.0f, izqPaletaY);
	drawPaleta(VENTANA_WIDTH - PALETA_WIDTH, derPaletaY);

	//drawPelota();

	char marPuntos[100];
	sprintf_s(marPuntos, "IZQ: %d  DER: %d", izqPuntos, derPuntos);
	drawTexto(VENTANA_WIDTH / 2 - 100, VENTANA_HEIGHT - 60, marPuntos
	);
}

