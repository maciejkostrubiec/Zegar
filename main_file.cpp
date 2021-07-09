/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie o
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <lodepng.h>
#include <time.h>
#include <windows.h>
#include <cmath>
#include "constants.h"
#include "allmodels.h"
#include "myCube.h"

using namespace glm;

float aspect=1.0f; //Aktualny stosunek szerokości do wysokości okna
float speed=1;
/////////////////////////

GLuint tex;

GLuint tex2;
/////////////////////////
//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    aspect=(float)width/(float)height; //Stosunek szerokości do wysokości okna
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS) {
      //  if (key == GLFW_KEY_LEFT) l = true;
    //    if (key == GLFW_KEY_RIGHT) p = true;
    }

    if (action == GLFW_RELEASE) {
        //if (key == GLFW_KEY_LEFT) l = false;
        //if (key == GLFW_KEY_RIGHT) p = false;
    }
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
    glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurę obsługi zmiany rozdzielczości bufora ramki
    glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury

	glClearColor(0,0,0,1); //Ustaw kolor czyszczenia ekranu

//	glEnable(GL_LIGHTING); //Włącz tryb cieniowania
	//glEnable(GL_NORMALIZE); //Włącz tryb cieniowania
	glEnable(GL_LIGHT0); //Włącz zerowe źródło światła
	//glEnable(GL_LIGHT1); //Włącz zerowe źródło światła
	glEnable(GL_DEPTH_TEST); //Włącz używanie budora głębokości
	glEnable(GL_COLOR_MATERIAL); //Włącz śledzenie kolorów przez materiał

	std::vector<unsigned char> image, image2;
    //Alokuj wektor do wczytania obrazka
    unsigned width, height, w2, h2;
    //Zmienne do których wczytamy wymiary obrazka
    //Wczytaj obrazek
	lodepng::decode(image, width, height, "text2.png");
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    lodepng::decode(image2, w2, h2, "text.png");
    glGenTextures(1,&tex2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image2.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	srand(time(NULL));
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle) {
	//************Tutaj umieszczaj kod rysujący obraz******************l

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wyczyść bufor kolorów (czyli przygotuj "płótno" do rysowania)
    mat4 P=perspective(50.0f*PI/180.0f,aspect,1.0f,10.0f); //Wylicz macierz rzutowania P
    mat4 V=lookAt( //Wylicz macierz widoku
                  vec3(1.0f,5.0f,1.0f),
                  vec3(0.0f,0.0f,0.0f),
                  vec3(0.0f,1.0f,0.0f));
    glMatrixMode(GL_PROJECTION); //Włącz tryb modyfikacji macierzy rzutowania
    glLoadMatrixf(value_ptr(P)); //Załaduj macierz rzutowania
    glMatrixMode(GL_MODELVIEW);  //Włącz tryb modyfikacji macierzy model-widok

    mat4 M=mat4(1.0f);

    mat4 W, S, R;

   /* M=mat4(1.0f);
    W=translate(M, vec3(-1.7f, 1.0f, 0.0f));
    S=scale(M, vec3(1.0f,1.0f,1.0f));
    R=rotate(M,90.0f,vec3(1.0f,0.0f,0.0f));
    Ra=rotate(M,angle*PI/10,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R*Ra));

    glShadeModel(GL_SMOOTH);
    glColor3d(1.0f,1.0f,0.2f);
    Models::moje.drawSolid();


    M=mat4(1.0f);
    W=translate(M, vec3(1.0f, 2.0f, 0.0f));
    S=scale(M, vec3(2.0f,2.0f,2.0f));
    R=rotate(M,90.0f,vec3(1.0f,0.0f,0.0f));
    Ra=rotate(M,angle*PI/(-20),vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R*Ra));

    glShadeModel(GL_SMOOTH);
    glColor3d(1.0f,1.0f,0.5f);
    Models::moje.drawSolid();

*/

    M=mat4(1.0f);
    W=translate(M, vec3(-1.0f, 0.0f, -1.0f));
    S=scale(M, vec3(1.0f,1.0f,1.0f));
    R=rotate(M,angle/(-16),vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(1.0f,1.0f,0.5f);
    Models::moje.drawSolid();

    M=mat4(1.0f);
    W=translate(M, vec3(0.3f, 0.0f, -1.5f));
    S=scale(M, vec3(0.5f,0.5f,0.5f));
    R=rotate(M,angle/8,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(1.0f,1.0f,0.2f);
    Models::moje.drawSolid();

    M=mat4(1.0f);
    W=translate(M, vec3(-0.4f, -1.0f, -1.5f));
    S=scale(M, vec3(0.5f,0.5f,0.5f));
    R=rotate(M,sin(angle)/2+PI/4,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(0.3f, 0.3f, 0.3f);
    Models::wsk.drawSolid();

    M=mat4(1.0f);
    W=translate(M, vec3(-0.4f, -1.0f, -1.5f));
    S=scale(M, vec3(0.5f,0.5f,0.5f));
    R=rotate(M,sin(angle+1.0f)/3.0f+PI/4,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(0.3f, 0.3f, 0.3f);
    Models::wsk.drawSolid();

    M=mat4(1.0f);
    W=translate(M, vec3(-1.0f, 0.1f, -1.0f));
    S=scale(M, vec3(0.1f,0.1f,0.1f));
    R=rotate(M,-1*angle,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(0.1f, 0.1f, 0.1f);
    Models::wsk.drawSolid();

    M=mat4(1.0f);
    W=translate(M, vec3(-1.0f, 0.1f, -1.0f));
    S=scale(M, vec3(0.05f,0.05f,0.05f));
    R=rotate(M,-1*angle/4,vec3(0.0f,1.0f,0.0f));
    glLoadMatrixf(value_ptr(V*M*W*S*R));

    glShadeModel(GL_SMOOTH);
    glColor3d(0.1f, 0.1f, 0.1f);
    Models::wsk.drawSolid();

    glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

    float angle=0.0f; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Wyzeruj timer


	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
	    angle+=speed*glfwGetTime(); //Oblicz przyrost kąta obrotu i zwiększ aktualny kąt
	    glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}
    Sleep(1000);
    glDeleteTextures(1,&tex);
	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
