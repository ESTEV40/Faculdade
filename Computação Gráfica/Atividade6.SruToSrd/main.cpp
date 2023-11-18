#include <GL/glut.h> //O arquivo glut.h inclui, além dos protótipos das funções GLUT, os arquivos gl.h e glu.h,
#include <stdlib.h>
#include <iostream>

using namespace std;

//Estêvão Sousa Vieira - 202210345
/*
  Tentei fazer janelas mostrando o ponto em ambos sistemas
*/

void displaySRD(void);
void displaySRU(void);
void iniciarSRD(void);
void iniciarSRU(void);
void keyboard(unsigned char key, int x, int y);

int SRD, SRU; // Variáveis das janelas gráficas

float SRD_MAX, SRD_MIN;
float SRU_MAX, SRU_MIN;

float X, Y;
float x_srd, y_srd; // Valores para sistema de coordenadas do SRD
float x_sru, y_sru; // Valores para sistema de coordenadas do SRU

string origem;

int main(int argc, char** argv){
  glutInit(&argc, argv); //Estabelece contato com sistema de janelas
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB

  cout << "Informe seu sistema de Origem (U/D):";
  cin >> origem;

  cout << "Insira os Valores Mínimos e Máximos para SRU e SRD" << endl;

  cout << "SRU_MIN: ";
  cin >> SRU_MIN;
  cout << "SRU_MAX: ";
  cin >> SRU_MAX;

  cout << "SRD_MIN: ";
  cin >> SRD_MIN;
  cout << "SRD_MAX: ";
  cin >> SRD_MAX;

  cout << "Insira o ponto no sistema de origem (X e Y)" << endl;
  cout << "X: ";
  cin >> X;
  
  cout << "Y: ";
  cin >> Y;
  // Dependendo de qual é o destino vai ter Atualizações de variaveis diferentes
  if(origem == "U"){
    // Aplicar transformações de SRU para SRD
    x_srd = (X - SRU_MIN) / (SRU_MAX - SRU_MIN) * (SRD_MAX - SRD_MIN) + SRD_MIN;
    y_srd = (Y - SRU_MIN) / (SRU_MAX - SRU_MIN) * (SRD_MAX - SRD_MIN) + SRD_MIN;

    x_sru = X;
    y_sru = Y;

  }else if(origem == "D"){
    // Aplicar transformações de SRD para SRU
    x_sru = (X - SRD_MIN) / (SRD_MAX - SRD_MIN) * (SRU_MAX - SRU_MIN) + SRU_MIN;
    y_sru = (Y - SRD_MIN) / (SRD_MAX - SRD_MIN) * (SRU_MAX - SRU_MIN) + SRU_MIN;

    x_srd = X;
    y_srd = Y;
  }

  iniciarSRD();
  iniciarSRU();
  glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
  glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas

  return 0;
}

void iniciarSRD(void){
  glutInitWindowSize (800, 640); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (10, 10); //Estabelece o tamanho (em pixels) da janela a ser criada
  SRD = glutCreateWindow ("SRD");
  glClearColor(1.0, 1.0, 1.0, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (-20, 120, -20, 120, -1 ,1);
  glutDisplayFunc(displaySRD); //Função callback chamada para fazer o desenho
}

void iniciarSRU(void){
  glutInitWindowSize (800, 640); //Posição inicial do canto superior esquerdo da janela a ser criada
  glutInitWindowPosition (1000, 10); //Estabelece o tamanho (em pixels) da janela a ser criada
  SRU = glutCreateWindow ("SRU");
  glClearColor(1.0, 1.0, 1.0, 0.0); //selecionar cor de fundo (Branco)
  glOrtho (-20, 120, -20, 120, -1 ,1);
  glutDisplayFunc(displaySRU); //Função callback chamada para fazer o desenho
}

void displaySRD(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  glColor3f (0.0, 0.0, 0.0);
  // Desenhando os eixos
  // Definindo a espessura da linha
  glLineWidth(2.0);
  glBegin (GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0,0,0.0);
    glVertex3i(0.0,10,0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0,0,0.0);
    glVertex3i(10,0,0.0);
  glEnd();
  // Desenhando as pontas dos eixos
  glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2,10,0.0);
    glVertex3f(0.0,10.2,0.0);
    glVertex3f(0.2,10,0.0);
    //Triangulo do eixo X
    glVertex3f(10,0.2,0.0);
    glVertex3f(10,-0.2,0.0);
    glVertex3f(10.2,0.0,0.0);
  glEnd();
  // Desenhando os pontos (cor: VERDE)
  glColor3f(0.0,1.0,0.0);
  glPointSize(10.0);
  glBegin(GL_POINTS);
    glVertex3i(x_srd,y_srd,0.0);
  glEnd();
  glFlush(); ////Executa os comandos OpenGL para renderização
}

void displaySRU(void){
  glClear(GL_COLOR_BUFFER_BIT); ////Limpa a janela de visualização com a cor de fundo especificada
  glColor3f (0.0, 0.0, 0.0);
  // Desenhando os eixos
  // Definindo a espessura da linha
  glLineWidth(2.0);
  glBegin (GL_LINES);
    // Definindo a reta do eixo Y
    glVertex3i(0,0,0.0);
    glVertex3i(0.0,10,0.0);
    // Definindo a reta do eixo X
    glVertex3i(0.0,0,0.0);
    glVertex3i(10,0,0.0);
  glEnd();
   // Desenhando as pontas dos eixos
  glBegin(GL_TRIANGLES);
    // Triangulo do eixo Y
    glVertex3f(-0.2,10,0.0);
    glVertex3f(0.0,10.2,0.0);
    glVertex3f(0.2,10,0.0);
    //Triangulo do eixo X
    glVertex3f(10,0.2,0.0);
    glVertex3f(10,-0.2,0.0);
    glVertex3f(10.2,0.0,0.0);
  glEnd();
   // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0,0.0,0.0);
  glPointSize(10.0);
  glBegin(GL_POINTS);
    glVertex3i(2,2,0.0);
  glEnd();
  glFlush(); ////Executa os comandos OpenGL para renderização
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 27: exit(0);
  }
}