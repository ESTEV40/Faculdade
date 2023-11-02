#include <GL/glut.h>
#include <stdio.h>

int numVertices;
int verticesX[100];
int verticesY[100];

void rasterizarDDA(void) {
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  for (int i = 0; i < numVertices; i++) {
    int x1 = verticesX[i];
    int y1 = verticesY[i];
    int x2 = verticesX[(i + 1) % numVertices];
    int y2 = verticesY[(i + 1) % numVertices];
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;
    float x = x1;
    float y = y1;
    
    for (int j = 0; j <= steps; j++) {
      glVertex2i((int) x, (int) y);
      x += xIncrement;
      y += yIncrement;
    }
  }
  glEnd();
}

void rasterizarPontoMedio(void) {
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
  for (int i = 0; i < numVertices; i++) {
    int x1 = verticesX[i];
    int y1 = verticesY[i];
    int x2 = verticesX[(i + 1) % numVertices];
    int y2 = verticesY[(i + 1) % numVertices];
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int x, y, p, incE, incNE;
    
    if (x1 < x2) {
      x = x1;
      y = y1;
    } else {
      x = x2;
      y = y2;
      x2 = x1;
      y2 = y1;
    }
    
    glVertex2i(x, y);
    
    if (dx > dy) {
      p = 2 * dy - dx;
      incE = 2 * dy;
      incNE = 2 * (dy - dx);
      while (x < x2) {
        x++;
        if (p < 0) {
          p += incE;
        } else {
          y++;
          p += incNE;
        }
        glVertex2i(x, y);
      }
    } else {
      p = 2 * dx - dy;
      incE = 2 * dx;
      incNE = 2 * (dx - dy);
      while (y < y2) {
        y++;
        if (p < 0) {
          p += incE;
        } else {
          x++;
          p += incNE;
        }
        glVertex2i(x, y);
      }
    }
  }
  glEnd();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  
  glLineWidth(2.0);
  glBegin(GL_LINES);
  glVertex3i(0, 0, 0.0);
  glVertex3i(0, 10, 0.0);
  glVertex3i(0, 0, 0.0);
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
  
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(10.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < numVertices; i++) {
    glVertex3i(verticesX[i], verticesY[i], 0.0);
  }
  glEnd();
  
  rasterizarDDA();
  rasterizarPontoMedio();
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 640);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Rasterização de Polígonos");
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glOrtho(-2, 12, -2, 12, -1, 1);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  printf("Digite o número de vértices do polígono: ");
  scanf("%d", &numVertices);
  for (int i = 0; i < numVertices; i++) {
    printf("Digite as coordenadas do vértice %d (x y): ", i + 1);
    scanf("%d %d", &verticesX[i], &verticesY[i]);
    verticesX[i] = verticesX[i] < 0 ? 0 : (verticesX[i] > 10 ? 10 : verticesX[i]);
    verticesY[i] = verticesY[i] < 0 ? 0 : (verticesY[i] > 10 ? 10 : verticesY[i]);
  }
  glutMainLoop();
  return 0;
}