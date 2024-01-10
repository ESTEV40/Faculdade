#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
// Estêvão Sousa Vieira - 202210345
using namespace std;

void displayDDA(void);
size_t SIGN(size_t x);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
void keyboard(unsigned char key, int x, int y);
void RastDDA(const vector<pair<int,int>> vert);
void RastPM(const vector<pair<int,int>> vert);

int DDA, PM, PMC; // Variáveis das janelas gráficas

vector<pair<int,int>> Vert;

int main(int argc, char **argv)
{

    int numVert;
    cout << "Digite o número de vértices do polígono (máx. 10): ";
    while(cin >> numVert && (numVert > 10 || numVert <= 0)){
        cout << "Quantidade de Vértices inválidos, insira novamente(laele):";
    };

    cout << "Digite as coordenadas dos vértices (1 a 10):" << endl;
    for (int i = 0; i < numVert; i++) {
        int x, y;
        cout << "Vértice " << i + 1 << ": " << endl;

        cout << "X: ";
        cin >> x; 

        cout << "Y: ";
        cin>> y;
        Vert.push_back(make_pair(x, y));
    }

    glutInit(&argc, argv);                       // Estabelece contato com sistema de janelas
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Cores dos pixels serão expressos em RGB
    iniciarDDA();
    iniciarPM();
    glutKeyboardFunc(keyboard); // Chamada sempre que uma tecla for precionada
    glutMainLoop();             // Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
    return 0;
}

void iniciarDDA(void)
{
    glutInitWindowSize(640, 640);   // Posição inicial do canto superior esquerdo da janela a ser criada
    glutInitWindowPosition(10, 10); // Estabelece o tamanho (em pixels) da janela a ser criada
    DDA = glutCreateWindow("DDA");
    glClearColor(1.0, 1.0, 1.0, 0.0); // selecionar cor de fundo (Branco)
    glOrtho(-2, 12, -2, 12, -1, 1);
    glutDisplayFunc(displayDDA); // Função callback chamada para fazer o desenho
}

void iniciarPM(void)
{
    glutInitWindowSize(640, 640);     // Posição inicial do canto superior esquerdo da janela a ser criada
    glutInitWindowPosition(1000, 10); // Estabelece o tamanho (em pixels) da janela a ser criada
    PM = glutCreateWindow("Ponto Medio");
    glClearColor(1.0, 1.0, 1.0, 0.0); // selecionar cor de fundo (Branco)
    glOrtho(-2, 12, -2, 12, -1, 1);
    glutDisplayFunc(displayPM); // Função callback chamada para fazer o desenho
}

void displayDDA(void)
{
    glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
    glColor3f(0.0, 0.0, 0.0);
    // Desenhando os eixos
    // Definindo a espessura da linha
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
    glEnd();
    // Desenhando as pontas dos eixos
    glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    // Triangulo do eixo X
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
    glEnd();
    // Desenhando os pontos (cor: vermelha)
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(25.0);
    glBegin(GL_POINTS);
    RastDDA(Vert);
    glEnd();// Rasteriza o polígono usando o algoritmo do Ponto Médio

    glFlush();
}

void displayPM(void)
{
    glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
    glColor3f(0.0, 0.0, 0.0);
    // Desenhando os eixos
    // Definindo a espessura da linha
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
    glEnd();
    // Desenhando as pontas dos eixos
    glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    // Triangulo do eixo X
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
    glEnd();
    // Desenhando os pontos (cor: vermelha)
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(25.0);
    glBegin(GL_POINTS);
    RastPM(Vert);
    glEnd();// Rasteriza o polígono usando o algoritmo do Ponto Médio
    
    glFlush();

}

void RastDDA(const vector<pair<int,int>> vert){
    for(int i = 0; i < vert.size(); i++){

        int j = (i+1)%vert.size();// pega o indice do vertice seguinte
        int x1 = vert[i].first;
        int y1 = vert[i].second;
        int x2 = vert[j].first;
        int y2 = vert[j].second;

        //Peguei a diferença pro code ficar bntinho
        int x3 = (x2-x1);
        int y3 = (y2-y1);

        int length = abs(x3) > abs(y3) ? abs(x3) : abs(y3);

        float Dx = (float) x3 / (float) length;
        float Dy = (float) y3 / (float) length;

        float x = x1;
        float y = y1;

        for(int K = 0 ; K < length; K++){
            glVertex2i(floor(x), floor(y));
            x+= Dx;
            y+= Dy;
        }
    }
}

void RastPM(const vector<pair<int,int>> vert){

    for(int i = 0; i< vert.size(); i++){
        int j = (i+1)%vert.size();// pega o indice do vertice seguinte
        int x1 = vert[i].first;
        int y1 = vert[i].second;
        int x2 = vert[j].first;
        int y2 = vert[j].second;

        int Dx = abs(x2 - x1);
        int Dy = abs(y2 - y1);
        
        int SinalX = ((x2 <= x1) ? -1 : 1);
        int SinalY = ((y2 <= y1) ? -1 : 1); 

        int x = x1;
        int y = y1;

        bool interchange = Dy > Dx;

        int baduntis = interchange ? 2 * (Dx-Dy) : 2 * (Dy-Dx);

        for(int i = 0; i < max(Dx,Dy); i++){
           glVertex2i(x, y);

            if(interchange){
                y = y + SinalY;
                baduntis += 2 * Dx;
            }
            else {
                x += SinalX;
                baduntis += 2 * Dy;
            }
            if ((interchange && baduntis >= 0) || (!interchange && baduntis >= Dx)) {
                if (interchange) {
                    x += SinalX;
                } else {
                        y += SinalY;
                }
                baduntis -= 2 * (interchange ? Dy : Dx);
        }
        }
    }

}

void keyboard(unsigned char key,int x, int y )
{
    switch (key)
    {
    case 27: 
    case 'q':
        exit(0);
    }
}