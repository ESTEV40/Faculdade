#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int DDA, PM;
int numVertices = 0;
int vertices[10][2];

void displayDDA(void);
void displayPM(void);
void iniciarDDA(void);
void iniciarPM(void);
void drawPolygons();
void keyboard(unsigned char key, int x, int y);

void drawPolygonDDA();
void drawPolygonPM();
void rasterizeLineDDA(int x1, int y1, int x2, int y2);
void rasterizeLinePM(int x1, int y1, int x2, int y2);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  iniciarDDA();
  iniciarPM();

  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

void iniciarDDA(void){
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(10, 10);
  DDA = glutCreateWindow("DDA");
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho(-2, 12, -2, 12, -1, 1);
  glutDisplayFunc(displayDDA);
}

void iniciarPM(void){
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(1000, 10);
  PM = glutCreateWindow("Ponto Médio");
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho(-2, 12, -2, 12, -1, 1);
  glutDisplayFunc(displayPM);
}

void displayDDA(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);

  // Desenhando os eixos e pontas dos eixos (mesmo para "DDA" e "Ponto Médio")
  glLineWidth(2.0);
  glBegin(GL_LINES);
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
  glEnd();

  // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(10.0);
  glBegin(GL_POINTS);
    glVertex3i(2, 2, 0.0);
  glEnd();

  drawPolygons();  // Desenha os polígonos
  glFlush();
}

void displayPM(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);

  // Desenhando os eixos e pontas dos eixos (mesmo para "DDA" e "Ponto Médio")
  glLineWidth(2.0);
  glBegin(GL_LINES);
    glVertex3i(0, 0, 0.0);
    glVertex3i(0.0, 10, 0.0);
    glVertex3i(0.0, 0, 0.0);
    glVertex3i(10, 0, 0.0);
  glEnd();
  glBegin(GL_TRIANGLES);
    glVertex3f(-0.2, 10, 0.0);
    glVertex3f(0.0, 10.2, 0.0);
    glVertex3f(0.2, 10, 0.0);
    glVertex3f(10, 0.2, 0.0);
    glVertex3f(10, -0.2, 0.0);
    glVertex3f(10.2, 0.0, 0.0);
  glEnd();

  // Desenhando os pontos (cor: vermelha)
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(10.0);
  glBegin(GL_POINTS);
    glVertex3i(2, 2, 0.0);
  glEnd();

  drawPolygons();  // Desenha os polígonos
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
      break;
    case 'v':
    case 'V':
      if (numVertices < 10) {
        printf("Digite as coordenadas do vértice %d (x y): ", numVertices + 1);
        scanf("%d %d", &vertices[numVertices][0], &vertices[numVertices][1]);
        if (vertices[numVertices][0] >= 0 && vertices[numVertices][0] <= 10 &&
            vertices[numVertices][1] >= 0 && vertices[numVertices][1] <= 10) {
          numVertices++;
        } else {
          printf("Coordenadas fora do intervalo (0-10). Tente novamente.\n");
        }
      } else {
        printf("Número máximo de vértices atingido.\n");
      }
      break;
    case 'r':
    case 'R':
      glutSetWindow(DDA);
      glutPostRedisplay();
      glutSetWindow(PM);
      glutPostRedisplay();
      drawPolygons();  // Chama a função para desenhar os polígonos
      break;
  }
}

void drawPolygonDDA() {
  glLineWidth(1.0);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  for (int i = 0; i < numVertices; i++) {
    int j = (i + 1) % numVertices;
    rasterizeLineDDA(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]);
  }
  glEnd();
}

void drawPolygonPM() {
  glLineWidth(1.0);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  for (int i = 0; i < numVertices; i++) {
    int j = (i + 1) % numVertices;
    rasterizeLinePM(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]);
  }
  glEnd();
}

void drawPolygons() {
  drawPolygonDDA();
  drawPolygonPM();
}

void rasterizeLineDDA(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  float xIncrement = (float)dx / (float)steps;
  float yIncrement = (float)dy / (float)steps;
  float x = (float)x1;
  float y = (float)y1;

  glBegin(GL_POINTS);
  for (int i = 0; i <= steps; i++) {
    glVertex2i(round(x), round(y));
    x += xIncrement;
    y += yIncrement;
  }
  glEnd();
}

void rasterizeLinePM(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  int x = x1;
  int y = y1;

  glBegin(GL_POINTS);
  if (abs(dx) > abs(dy)) {
    int d = 2 * abs(dy) - abs(dx);
    int incrE = 2 * abs(dy);
    int incrNE = 2 * (abs(dy) - abs(dx));
    glVertex2i(x, y);
    while (x < x2) {
      if (d <= 0) {
        d += incrE;
      } else {
        d += incrNE;
        y += (dy >= 0 ? 1 : -1);
      }
      x++;
      glVertex2i(x, y);
    }
  }
  else {
    int d = 2 * abs(dx) - abs(dy);
    int incrE = 2 * abs(dx);
    int incrNE = 2 * (abs(dx) - abs(dy));
    glVertex2i(x, y);
    while (y < y2) {
      if (d <= 0) {
        d += incrE;
      } else {
        d += incrNE;
        x += (dx >= 0 ? 1 : -1);
      }
      y++;
      glVertex2i(x, y);
    }
  }
  glEnd();
}