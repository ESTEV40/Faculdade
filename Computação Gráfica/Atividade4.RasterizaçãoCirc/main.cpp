#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

void displayPM(void);
void iniciarPM(void);
void keyboard(unsigned char key, int x, int y);
void drawCircle(int raio);

int DDA, PM, PMC;    // Variáveis das janelas gráficas
int RaioCirculo = 0; // Raio do círculo
int CentroCirX = 0;  // Coordenada X do centro do círculo
int CentroCirY = 0;  // Coordenada Y do centro do círculo

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Estabelece contato com sistema de janelas
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Cores dos pixels serão expressos em RGB

    cout << "Insira o raio do círculo: " << endl;
    cin >> RaioCirculo;

    iniciarPM();
    glutKeyboardFunc(keyboard); // Chamada sempre que uma tecla for precionada
    glutMainLoop();             // Depois de registradas as callbacks, o controle é entregue ao sistema de janelas
    return 0;
}

void iniciarPM(void)
{

    glutInitWindowSize(800, 640);     // Posição inicial do canto superior esquerdo da janela a ser criada
    glutInitWindowPosition(1000, 10); // Estabelece o tamanho (em pixels) da janela a ser criada
    PM = glutCreateWindow("Ponto Médio Circular");
    glClearColor(1.0, 1.0, 1.0, 0.0); // selecionar cor de fundo (Branco)
    glOrtho(-2, 12, -2, 12, -1, 1);
    glutDisplayFunc(displayPM); // Função callback chamada para fazer o desenho
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

    glColor3f(0.0, 0.0, 1.0); // Cor azul para o círculo
    drawCircle(RaioCirculo);

    glFlush(); ////Executa os comandos OpenGL para renderização
}

void drawCircle(int Raio)
{
    glPointSize(10.0);
    glBegin(GL_POINTS);

    int x = Raio;
    int y = 0;
    int ErRaio = 1 - x;

    while (x >= y)
    {
        // Plot os pontos em todos os quadrantes
        glVertex2i(y,x);
        glVertex2i(x,y);

        glVertex2i((-y),x);
        glVertex2i((-x),y);

        glVertex2i(y,(-x));
        glVertex2i(x,(-y));

        glVertex2i((-y),(-x));
        glVertex2i((-x),(-y));

        y++;

        if (ErRaio < 0)
        {
            ErRaio += 2 * y + 1;
        }
        else
        {
            x--;
            ErRaio += 2 * (y - x + 1);
        }
    }

    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    }
}