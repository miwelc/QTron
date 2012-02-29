#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Cara {
    int a;
    int b;
    int c;
};

struct Vertice {
    float x;
    float y;
    float z;
};

int main(int argc, char *argv[]) {
	ofstream PLY;
	vector<Vertice> vertices;
	vector<Cara> caras;
	
	if(argc < 3)
		exit(-1);
	
	//Leemos archivos
	for(int i = 2; i < argc; i++) {
		ifstream entrada;
		char c;
		int nVertice;
		Cara cara;
		Vertice vertice;
		int nVerticesAnteriores = vertices.size();
		
		entrada.open(argv[i]);
		while(entrada >> c) {			
			if(c == 'v') {
				entrada >> nVertice;
				entrada >> vertice.x; entrada >> vertice.y; entrada >> vertice.z;
				vertices.push_back(vertice);
			}
			else {
				entrada >> cara.a; entrada >> cara.b; entrada >> cara.c;
				cara.a += -1 + nVerticesAnteriores;
				cara.b += -1 + nVerticesAnteriores;
				cara.c += -1 + nVerticesAnteriores;
				caras.push_back(cara);
			}
		}
		
		entrada.close();
	}
	
	//Generamos PLY
	PLY.open(argv[1]);
	
	PLY << "ply\nformat ascii 1.0\nelement vertex "<< vertices.size() <<"\nproperty float x\nproperty float y\nproperty float z\nelement face "<< caras.size() <<"\nproperty list uchar int vertex_indices\nend_header\n";

	for(int i = 0; i < vertices.size(); i++)
		PLY << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << "\n";
	
	for(int i = 0; i < caras.size(); i++)
		PLY << "3 " << caras[i].a << " " << caras[i].b << " " << caras[i].c << "\n";
	
	PLY.close();
	
	return 1;
}
