/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#include "wsk.h"

namespace Models {
	
	Wsk wsk;
	
	Wsk::Wsk() {
		vertices=WskInternal::vertices;
		normals=WskInternal::normals;
		vertexNormals=WskInternal::vertexNormals;
		texCoords=WskInternal::texCoords;
		colors=WskInternal::colors;
		vertexCount=WskInternal::vertexCount;
	}
	
	Wsk::~Wsk() {
	}
	
	void Wsk::drawSolid() {
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(4,GL_FLOAT,0,vertices);
		//glColorPointer(4,GL_FLOAT,0,colors);
		glNormalPointer(GL_FLOAT,sizeof(float)*4,vertexNormals);
		glTexCoordPointer(2,GL_FLOAT,0,texCoords);
		
		glDrawArrays(GL_TRIANGLES,0,vertexCount);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	
	
	namespace WskInternal {
		
		unsigned int vertexCount=12;
		float vertices[]={
			0.2f, 0.0f, 0.0f, 1.0f,
			0.2f, 0.0f, 6.0f, 1.0f,
			-0.2f, 0.0f, 6.0f, 1.0f,
			
			0.2f, 0.0f, 0.0f, 1.0f,
			-0.2f, 0.0f, 0.0f, 1.0f,
			-0.2f, 0.0f, 6.0f, 1.0f,
		
			0.0f, 0.0f, 5.0f, 1.0f,
			0.4f, 0.0f, 7.0f, 1.0f,
			-0.4f, 0.0f, 7.0f, 1.0f,
			
			0.0f, 0.0f, 8.0f, 1.0f,
			-0.4f, 0.0f, 7.0f, 1.0f,
			0.4f, 0.0f, 7.0f, 1.0f
		};
		float normals[]={
			
		};
		float vertexNormals[]={
			
		};
		float texCoords[]={
				
		};
		float colors[]={

		};
	}
}