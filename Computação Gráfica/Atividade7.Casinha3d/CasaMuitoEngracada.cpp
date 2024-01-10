#include <GL/glut.h>

#include <cmath>

//Estêvão Sousa Vieira => 202210345

/*

        Era uma casa        Ninguém podia
        Muito engraçada     Fazer pipi
        Não tinha teto      Porque penico
        Não tinha nada      Não tinha ali

        Ninguém podia       Mas era feita
        Entrar nela, não    Com muito esmero
        Porque na casa      Na Rua dos Bobos
        Não tinha chão      Número zero

        Ninguém podia
        Dormir na rede
        Porque na casa
        Não tinha parede

        obs: EU FIZ DIFERENTE -> M e N aumenta e diminui o zoom. Pressionar o botão direito e arrastar move a figura.
        
*/
float Angulo = 1.0f;            // Ângulo inicial de rotação
float VelocidadeRotacao = 0.01f;   // Velocidade de rotação
int mouseX, mouseY; 
float zoom = 3.0f;             // Fator de zoom
float observadorX = 4;
float observadorZ = 4;          // Coordenadas do último clique do mouse

float visao[3]={4.0,2.0,4.0};

float Largura = 800, Altura = 640;

void Casinha(void);
void Iniciar(void);
void Casinha(void);
void Teclado(unsigned char key, int x, int y);

void Casinha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   // glClear(GL_COLOR_BUFFER_BIT);
    Iniciar();
    glEnable(GL_DEPTH_TEST);
    glBegin( GL_LINES ); //Eixos
    glColor3f(1.0f,.0f,0.0f);// vermelho é o x
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.7f,0.0f,0.0f);
    glColor3f(0.0f,1.0f,0.0f);// verde é o y
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.5f,0.0f);
    glColor3f(0.0f,0.0f,1.0f);//azul é o z
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.7f);
  glEnd();
  glBegin( GL_POLYGON ); //Parede de trás
    glColor3f(0.6f,0.0f,0.0f); //Vermelha
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.2f,0.0f);
    glVertex3f(0.2f,0.3f,0.0f);
    glVertex3f(0.4f,0.2f,0.0f);
    glVertex3f(0.4f,0.0f,0.0f);
  glEnd();
  glBegin( GL_QUADS ); //Parede esquerda
    glColor3f(0.0f,0.0f,0.6f); //Azul
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.4f);
    glVertex3f(0.0f,0.2f,0.4f);
    glVertex3f(0.0f,0.2f,0.0f);
  glEnd();
  glBegin( GL_QUAD_STRIP ); //Telhado com sobra
    glColor3f(0.5f,0.3f,0.0f); //Verde

    glVertex3f(0.0f,0.2f,-0.05f);
    glVertex3f(0.0f,0.2f,0.45f);
    glVertex3f(0.2f,0.3f,-0.05f);
    glVertex3f(0.2f,0.3f,0.45f);
    glVertex3f(0.4f,0.2f,-0.05f);
    glVertex3f(0.4f,0.2f,0.45f);

  glEnd();
  glBegin( GL_POLYGON ); //Parede Frente
    glColor3f(0.6f,0.6f,0.6f); //Cinza
    glVertex3f(0.0f,0.0f,0.4f);
    glVertex3f(0.4f,0.0f,0.4f);
    glVertex3f(0.4f,0.2f,0.4f);
    glVertex3f(0.2f,0.3f,0.4f);
    glVertex3f(0.0f,0.2f,0.4f);
  glEnd();
  glBegin( GL_POLYGON ); //Parede Direita
    glColor3f(0.8f,0.8f,0.0f); //Amarelo
    glVertex3f(0.4f,0.0f,0.0f);
    glVertex3f(0.4f,0.0f,0.4f);
    glVertex3f(0.4f,0.2f,0.4f);
    glVertex3f(0.4f,0.2f,0.0f);
  glEnd();

  glBegin(GL_POLYGON); //CHAO
    glColor3f(0.4,0.2,0.6);
        glVertex3f(0,0,0);
        glVertex3f(0.4,0,0);
        glVertex3f(0.4,0,0.4);
        glVertex3f(0,0,0.4);
  glEnd();

  glBegin(GL_POLYGON); //Porta
    glColor3f(0.5,0.5,0.2);
        glVertex3f(0.1,0.0,0.40001);
        glVertex3f(0.153,0.0,0.4001);
        glVertex3f(0.153,0.12,0.4001);
        glVertex3f(0.1,0.12,0.4001);
  glEnd();

  glBegin(GL_POLYGON); //Janela
    glColor3f(0.5,0.5,0.2);
        glVertex3f(0.21,0.06,0.40001);
        glVertex3f(0.283,0.06,0.4001);
        glVertex3f(0.283,0.11,0.4001);
        glVertex3f(0.21,0.11,0.4001);
  glEnd();

  glFlush();
}

void Iniciar() {

    float observadorX = zoom * cos(Angulo);
    float observadorZ = zoom * sin(Angulo);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(observadorX, visao[1], observadorZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10.0,Largura/Altura,1.0,10.0);
}

void Teclado(unsigned char key, int x, int y) {
   switch (key) {
    case 27:
        exit(0);
        break;
    case 'm': zoom *= 1.1f;
        break;
    case 'n': zoom /= 1.1f;
        break;
   }
   glutPostRedisplay();
}

void Movimento(int x, int y) {
    int deltaX = x - mouseX;
    mouseX = x;

    Angulo += static_cast<float>(deltaX) * VelocidadeRotacao;

    // Mantenha o ângulo no intervalo [0, 2*pi] para evitar overflow
    if (Angulo > 2 * M_PI) {
        Angulo -= 2 * M_PI;
    }

    glutPostRedisplay();
}

void cliqueMouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mouseX = x;
        mouseY = y;
    }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE );
   glutInitWindowSize(Largura, Altura);
   glutCreateWindow("Uma Casa muito engracada");
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glutDisplayFunc(Casinha);
   glutKeyboardFunc(Teclado);
   glutMouseFunc(cliqueMouse);
   glutMotionFunc(Movimento);
 
   glutMainLoop();
   return 0;
}