//Estêvão Sousa Vieira - 202210345

#include <GL/glut.h> 
#include <iostream>
#include <vector>

using namespace std;

typedef struct Coord{
  float x;
  float y;
}Tcoord;

//Coordenadas dos pontos para a base e o apoio do foguete
vector<Tcoord> PontosBase;
vector<Tcoord> PontosApoioBaseQuad1;
vector<Tcoord> PontosApoioBaseQuad2;
vector<Tcoord> PontosApoioBaseQuad3;
vector<Tcoord> PontosApoioBaseQuad4;
//Coordenadas dos pontos para a o corpo direito do foguete
vector<Tcoord> PontosCorpoD;
vector<Tcoord> PontosApoioD;
vector<Tcoord> PontosBicoD;
vector<Tcoord> PontosPropulsorD;
vector<Tcoord> PontosAsaD;
//Coordenadas dos pontos para a o corpo esquerdo do foguete
vector<Tcoord> PontosCorpoE;
vector<Tcoord> PontosApoioE;
vector<Tcoord> PontosBicoE;
vector<Tcoord> PontosPropulsorE;
vector<Tcoord> PontosAsaE;
//Coordenadas dos pontos para a o corpo direito do foguete
vector<Tcoord> PontosCorpoC;
vector<Tcoord> PontosBicoSupC;
vector<Tcoord> PontosCorpoBicoC;
vector<Tcoord> PontosBicoInfC;
vector<Tcoord> PontosPropulsorC;

void R_Direito(void){
  //Armazena os valores Do Corpo Direito para animação posterior
  PontosCorpoD.push_back(Tcoord {424.785,336.758});
  PontosCorpoD.push_back(Tcoord {458.198,336.758});
  PontosCorpoD.push_back(Tcoord {458.198,567.011});
  PontosCorpoD.push_back(Tcoord {424.785,567.011});

  //Armazena os valores Do Bico Direito para animação posterior
  PontosBicoD.push_back(Tcoord {424.852,336.675});
  PontosBicoD.push_back(Tcoord {426.500,330.002});
  PontosBicoD.push_back(Tcoord {428.208,324.899});
  PontosBicoD.push_back(Tcoord {429.876,321.104});
  PontosBicoD.push_back(Tcoord {432.077,317.495});
  PontosBicoD.push_back(Tcoord {434.248,315.061});
  PontosBicoD.push_back(Tcoord {436.686,313.292});
  PontosBicoD.push_back(Tcoord {436.686,313.292});
  PontosBicoD.push_back(Tcoord {438.137,312.612});
  PontosBicoD.push_back(Tcoord {441.456,311.841});
  PontosBicoD.push_back(Tcoord {444.988,312.670});
  PontosBicoD.push_back(Tcoord {446.439,313.350});
  PontosBicoD.push_back(Tcoord {448.877,315.119});
  PontosBicoD.push_back(Tcoord {451.048,317.553});
  PontosBicoD.push_back(Tcoord {453.249,321.162});
  PontosBicoD.push_back(Tcoord {454.917,324.957});
  PontosBicoD.push_back(Tcoord {456.626,330.060});
  PontosBicoD.push_back(Tcoord {458.274,336.733});

  //Armazena os valores Da Asa Direita para animação posterior
  PontosAsaD.push_back(Tcoord {458.198,491.353});
  PontosAsaD.push_back(Tcoord {458.198,567.054});
  PontosAsaD.push_back(Tcoord {476.983,567.054});

  //Armazena os valores Do Propulsor Direito para animação posterior
  PontosPropulsorD.push_back(Tcoord {430.758,567.054});
  PontosPropulsorD.push_back(Tcoord {451.967,567.054});
  PontosPropulsorD.push_back(Tcoord {458.198,572.752});
  PontosPropulsorD.push_back(Tcoord {424.785,572.752});

  //Armazena os valores Do Apoio Direito para animação posterior
  PontosApoioD.push_back(Tcoord {421.153,343.853});
  PontosApoioD.push_back(Tcoord {424.785,343.853});
  PontosApoioD.push_back(Tcoord {424.785,372.091});
  PontosApoioD.push_back(Tcoord {421.153,372.091});

  glBegin(GL_QUADS);
  glColor3ub(67,53,53);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i < PontosCorpoD.size(); i++){
    glVertex2f(PontosCorpoD[i].x, PontosCorpoD[i].y);
  }

  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3ub(27,2,49);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i < PontosAsaD.size();i++){
    glVertex2f(PontosAsaD[i].x,PontosAsaD[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(86,86,86);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i< PontosPropulsorD.size(); i++){
    glVertex2f(PontosPropulsorD[i].x, PontosPropulsorD[i].y);
  }

  glEnd();

  glBegin(GL_POLYGON);
  glColor3ub(27,2,49);
  //for que desenha de acordo com as coordenadas do vector
  for(int i = 0; i< PontosBicoD.size();i++){
    glVertex2f(PontosBicoD[i].x,PontosBicoD[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(86,86,86);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i< PontosApoioD.size(); i++){
    glVertex2f(PontosApoioD[i].x, PontosApoioD[i].y);
  }

  glEnd();
}

void R_Esquerdo(void){
  //Armazena os valores Do Corpo Direito para animação posterior
  PontosCorpoE.push_back(Tcoord {350.738,336.644});
  PontosCorpoE.push_back(Tcoord {384.140,336.644});
  PontosCorpoE.push_back(Tcoord {384.140,566.892});
  PontosCorpoE.push_back(Tcoord {350.738,566.892});

  //Armazena os valores Do Bico Direito para animação posterior
  PontosBicoE.push_back(Tcoord {350.686,336.725});
  PontosBicoE.push_back(Tcoord {352.334,330.052});
  PontosBicoE.push_back(Tcoord {354.043,324.949});
  PontosBicoE.push_back(Tcoord {355.711,321.154});
  PontosBicoE.push_back(Tcoord {357.912,317.545});
  PontosBicoE.push_back(Tcoord {360.083,315.111});
  PontosBicoE.push_back(Tcoord {362.521,313.342});
  PontosBicoE.push_back(Tcoord {363.972,312.662});
  PontosBicoE.push_back(Tcoord {367.291,311.891});

  PontosBicoE.push_back(Tcoord {370.823,312.749});
  PontosBicoE.push_back(Tcoord {372.274,313.429});
  PontosBicoE.push_back(Tcoord {374.712,315.198});
  PontosBicoE.push_back(Tcoord {376.883,317.632});
  PontosBicoE.push_back(Tcoord {379.084,321.241});
  PontosBicoE.push_back(Tcoord {380.752,325.036});
  PontosBicoE.push_back(Tcoord {382.461,330.139});
  PontosBicoE.push_back(Tcoord {384.109,336.812});

  PontosAsaE.push_back(Tcoord {350.738,491.353});
  PontosAsaE.push_back(Tcoord {350.738,566.892});
  PontosAsaE.push_back(Tcoord {331.953,566.892});

  PontosPropulsorE.push_back(Tcoord {356.709,567.054});
  PontosPropulsorE.push_back(Tcoord {377.911,567.054});
  PontosPropulsorE.push_back(Tcoord {384.140,572.752});
  PontosPropulsorE.push_back(Tcoord {350.738,572.752});

  PontosApoioE.push_back(Tcoord {384.140,343.853});
  PontosApoioE.push_back(Tcoord {387.739,343.853});
  PontosApoioE.push_back(Tcoord {387.739,372.091});
  PontosApoioE.push_back(Tcoord {384.140,372.091});

  glBegin(GL_QUADS);
  glColor3ub(67,53,53);
   //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i < PontosCorpoE.size(); i++){
    glVertex2f(PontosCorpoE[i].x, PontosCorpoE[i].y);
  }

  glEnd();
  //for que desenha de acordo com as coordenadas do vector
  glBegin(GL_TRIANGLES);
  glColor3ub(27,2,49);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i < PontosAsaE.size();i++){
    glVertex2f(PontosAsaE[i].x,PontosAsaE[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(86,86,86);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i< PontosPropulsorE.size(); i++){
    glVertex2f(PontosPropulsorE[i].x, PontosPropulsorE[i].y);
  }

  glEnd();

  glBegin(GL_POLYGON);
  glColor3ub(27,2,49);
  //for que desenha de acordo com as coordenadas do vector
  for(int i = 0; i< PontosBicoE.size();i++){
    glVertex2f(PontosBicoE[i].x,PontosBicoE[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(86,86,86);
  //for que desenha de acordo com as coordenadas do vector
  for(int i=0; i< PontosApoioE.size(); i++){
    glVertex2f(PontosApoioE[i].x, PontosApoioE[i].y);
  }

  glEnd();
}

void R_Principal(void){
  PontosCorpoC.push_back(Tcoord {387.739,215.693});
  PontosCorpoC.push_back(Tcoord {421.153,215.693});
  PontosCorpoC.push_back(Tcoord {421.153,566.687});
  PontosCorpoC.push_back(Tcoord {387.739,566.687});

  PontosCorpoBicoC.push_back(Tcoord {384.368,148.841});
  PontosCorpoBicoC.push_back(Tcoord {424.480,148.841});
  PontosCorpoBicoC.push_back(Tcoord {424.480,210.047});
  PontosCorpoBicoC.push_back(Tcoord {384.368,210.047});

  PontosBicoInfC.push_back(Tcoord {384.368,210.063 });
  PontosBicoInfC.push_back(Tcoord {424.480,210.063});
  PontosBicoInfC.push_back(Tcoord {421.157,215.709});
  PontosBicoInfC.push_back(Tcoord {384.368,215.709});

  PontosPropulsorC.push_back(Tcoord {393.713,566.685});
  PontosPropulsorC.push_back(Tcoord {414.921,566.685});
  PontosPropulsorC.push_back(Tcoord {421.153,572.561});
  PontosPropulsorC.push_back(Tcoord {387.739,572.561});

  PontosBicoSupC.push_back(Tcoord {384.425,148.777});
  PontosBicoSupC.push_back(Tcoord {385.291,145.443});
  PontosBicoSupC.push_back(Tcoord {386.323,142.031});
  PontosBicoSupC.push_back(Tcoord {387.542,138.554});
  PontosBicoSupC.push_back(Tcoord {389.234,134.708});
  PontosBicoSupC.push_back(Tcoord {391.267,131.203});
  PontosBicoSupC.push_back(Tcoord {396.081,125.908});
  PontosBicoSupC.push_back(Tcoord {397.370,124.959});
  PontosBicoSupC.push_back(Tcoord {399.078,124.068});
  PontosBicoSupC.push_back(Tcoord {401.188,123.311});
  PontosBicoSupC.push_back(Tcoord {404.240,122.809});
  PontosBicoSupC.push_back(Tcoord {404.648,122.600});
  PontosBicoSupC.push_back(Tcoord {407.701,123.311});
  PontosBicoSupC.push_back(Tcoord {409.811,124.068});
  PontosBicoSupC.push_back(Tcoord {411.518,124.959});
  PontosBicoSupC.push_back(Tcoord {412.808,125.908});
  PontosBicoSupC.push_back(Tcoord {416.526,129.717});
  PontosBicoSupC.push_back(Tcoord {417.622,131.203});
  PontosBicoSupC.push_back(Tcoord {419.654,134.708});
  PontosBicoSupC.push_back(Tcoord {421.346,138.554});
  PontosBicoSupC.push_back(Tcoord {422.565,142.031});
  PontosBicoSupC.push_back(Tcoord {423.598,145.443});
  PontosBicoSupC.push_back(Tcoord {424.464,148.777});


  glBegin(GL_QUADS);
  glColor3ub(27,2,49);

  for(int i =0; i < PontosCorpoBicoC.size();i++){
    glVertex2f(PontosCorpoBicoC[i].x, PontosCorpoBicoC[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);

  for(int i =0; i < PontosBicoInfC.size();i++){
    glVertex2f(PontosBicoInfC[i].x, PontosBicoInfC[i].y);
  }

  glEnd();

  glBegin(GL_POLYGON);

  for(int i =0; i < PontosBicoSupC.size();i++){
    glVertex2f(PontosBicoSupC[i].x, PontosBicoSupC[i].y);
  }
  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(67, 53,53);

  for(int i =0; i < PontosCorpoC.size();i++){
    glVertex2f(PontosCorpoC[i].x, PontosCorpoC[i].y);
  }

  glEnd();

  glBegin(GL_QUADS);
  glColor3ub(86,86,86);

  for(int i =0; i < PontosPropulsorC.size();i++){
    glVertex2f(PontosPropulsorC[i].x, PontosPropulsorC[i].y);
  }

  glEnd();


}

void Rocket(void){

  R_Direito();
  R_Esquerdo();
  R_Principal();

}

void SupBase(void){

  PontosApoioBaseQuad1.push_back(Tcoord {350.699, 220.608});
  PontosApoioBaseQuad1.push_back(Tcoord {458.149, 220.608});
  PontosApoioBaseQuad1.push_back(Tcoord {458.149, 309.439});
  PontosApoioBaseQuad1.push_back(Tcoord {350.699, 309.439});

  PontosApoioBaseQuad2.push_back(Tcoord {350.699, 309.439});
  PontosApoioBaseQuad2.push_back(Tcoord {458.149, 309.439});
  PontosApoioBaseQuad2.push_back(Tcoord {458.149, 397.439});
  PontosApoioBaseQuad2.push_back(Tcoord {350.699, 397.439});

  PontosApoioBaseQuad3.push_back(Tcoord {350.699, 397.439});
  PontosApoioBaseQuad3.push_back(Tcoord {458.149, 397.439});
  PontosApoioBaseQuad3.push_back(Tcoord {458.149, 486.270});
  PontosApoioBaseQuad3.push_back(Tcoord {350.699, 486.270});

  PontosApoioBaseQuad4.push_back(Tcoord {350.699, 486.270});
  PontosApoioBaseQuad4.push_back(Tcoord {458.149, 486.270});
  PontosApoioBaseQuad4.push_back(Tcoord {458.149, 575.102});
  PontosApoioBaseQuad4.push_back(Tcoord {350.699, 575.102});

  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
  glColor3ub(174,174,174);

  glVertex2f(PontosApoioBaseQuad1[0].x,PontosApoioBaseQuad1[0].y);
  glVertex2f(PontosApoioBaseQuad1[1].x,PontosApoioBaseQuad1[1].y);
  glVertex2f(PontosApoioBaseQuad1[2].x,PontosApoioBaseQuad1[2].y);
  glVertex2f(PontosApoioBaseQuad1[3].x,PontosApoioBaseQuad1[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad2[0].x,PontosApoioBaseQuad2[0].y);
  glVertex2f(PontosApoioBaseQuad2[1].x,PontosApoioBaseQuad2[1].y);
  glVertex2f(PontosApoioBaseQuad2[2].x,PontosApoioBaseQuad2[2].y);
  glVertex2f(PontosApoioBaseQuad2[3].x,PontosApoioBaseQuad2[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad3[0].x,PontosApoioBaseQuad3[0].y);
  glVertex2f(PontosApoioBaseQuad3[1].x,PontosApoioBaseQuad3[1].y);
  glVertex2f(PontosApoioBaseQuad3[2].x,PontosApoioBaseQuad3[2].y);
  glVertex2f(PontosApoioBaseQuad3[3].x,PontosApoioBaseQuad3[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad4[0].x,PontosApoioBaseQuad4[0].y);
  glVertex2f(PontosApoioBaseQuad4[1].x,PontosApoioBaseQuad4[1].y);
  glVertex2f(PontosApoioBaseQuad4[2].x,PontosApoioBaseQuad4[2].y);
  glVertex2f(PontosApoioBaseQuad4[3].x,PontosApoioBaseQuad4[3].y);

  glEnd();

  glBegin(GL_LINES);

  glVertex2f(PontosApoioBaseQuad1[0].x, PontosApoioBaseQuad1[0].y);
  glVertex2f(PontosApoioBaseQuad1[2].x, PontosApoioBaseQuad1[2].y);
  glVertex2f(PontosApoioBaseQuad1[1].x, PontosApoioBaseQuad1[1].y);
  glVertex2f(PontosApoioBaseQuad1[3].x, PontosApoioBaseQuad1[3].y);

  glEnd();
  glBegin(GL_LINES);

  glVertex2f(PontosApoioBaseQuad2[0].x, PontosApoioBaseQuad2[0].y);
  glVertex2f(PontosApoioBaseQuad2[2].x, PontosApoioBaseQuad2[2].y);
  glVertex2f(PontosApoioBaseQuad2[1].x, PontosApoioBaseQuad2[1].y);
  glVertex2f(PontosApoioBaseQuad2[3].x, PontosApoioBaseQuad2[3].y);

  glEnd();
  glBegin(GL_LINES);

  glVertex2f(PontosApoioBaseQuad3[0].x, PontosApoioBaseQuad3[0].y);
  glVertex2f(PontosApoioBaseQuad3[2].x, PontosApoioBaseQuad3[2].y);
  glVertex2f(PontosApoioBaseQuad3[1].x, PontosApoioBaseQuad3[1].y);
  glVertex2f(PontosApoioBaseQuad3[3].x, PontosApoioBaseQuad3[3].y);

  glEnd();
  glBegin(GL_LINES);

  glVertex2f(PontosApoioBaseQuad4[0].x, PontosApoioBaseQuad4[0].y);
  glVertex2f(PontosApoioBaseQuad4[2].x, PontosApoioBaseQuad4[2].y);
  glVertex2f(PontosApoioBaseQuad4[1].x, PontosApoioBaseQuad4[1].y);
  glVertex2f(PontosApoioBaseQuad4[3].x, PontosApoioBaseQuad4[3].y);

  glEnd();
}

void Base(void){

  vector<Tcoord> pontosTrapezioCinza;
  pontosTrapezioCinza.push_back(Tcoord{82.811, 640.000});
  pontosTrapezioCinza.push_back(Tcoord{116.942, 577.232});
  pontosTrapezioCinza.push_back(Tcoord{688.314, 577.232});
  pontosTrapezioCinza.push_back(Tcoord{722.343 , 640.000});

  
  glColor3ub (86,86,86);
  glBegin(GL_QUADS);
    for(int i=0; i<pontosTrapezioCinza.size(); i++) 
      glVertex2f(pontosTrapezioCinza[i].x, pontosTrapezioCinza[i].y);
  glEnd();

  glColor3f (0.6235, 0.7098, 1.0);
  vector<Tcoord> pontosQuad1;
  pontosQuad1.push_back(Tcoord{158.506, 640.0});
  pontosQuad1.push_back(Tcoord{158.506, 603.697});
  pontosQuad1.push_back(Tcoord{249.402, 603.697});
  pontosQuad1.push_back(Tcoord{249.402, 640.0});

  
  glBegin(GL_QUADS);
    for(int i=0; i<pontosQuad1.size(); i++) 
      glVertex2f(pontosQuad1[i].x, pontosQuad1[i].y);
  glEnd();

  vector<Tcoord> pontosQuad2;
  pontosQuad2.push_back(Tcoord{290.966, 640.0});
  pontosQuad2.push_back(Tcoord{290.966, 603.697});
  pontosQuad2.push_back(Tcoord{381.862, 603.697});
  pontosQuad2.push_back(Tcoord{381.862, 640.0});

  
  glBegin(GL_QUADS);
    for(int i=0; i<pontosQuad2.size(); i++) 
      glVertex2f(pontosQuad2[i].x, pontosQuad2[i].y);
  glEnd();

  vector<Tcoord> pontosQuad3;
  pontosQuad3.push_back(Tcoord{423.426, 640.0});
  pontosQuad3.push_back(Tcoord{423.426, 603.697});
  pontosQuad3.push_back(Tcoord{514.322, 603.697});
  pontosQuad3.push_back(Tcoord{514.322, 640.0});

  
  glBegin(GL_QUADS);
    for(int i=0; i<pontosQuad3.size(); i++) 
      glVertex2f(pontosQuad3[i].x, pontosQuad3[i].y);
  glEnd();

  vector<Tcoord> pontosQuad4;
  pontosQuad4.push_back(Tcoord{555.886, 640.0});
  pontosQuad4.push_back(Tcoord{555.886, 603.697});
  pontosQuad4.push_back(Tcoord{646.782, 603.697});
  pontosQuad4.push_back(Tcoord{646.782, 640.0});

  
  glBegin(GL_QUADS);
    for(int i=0; i<pontosQuad4.size(); i++) 
      glVertex2f(pontosQuad4[i].x, pontosQuad4[i].y);
  glEnd();
}

void Tela(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Base();
    SupBase();
    Rocket();
    glFlush();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    case 'q': exit(0);
  }
}

int main(int argc, char **argv){

    glutInit(&argc, argv); //Estabelece contato com sistema de janelas
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); //Cores dos pixels serão expressos em RGB
    glutInitWindowSize (800, 640); //Estabelece o tamanho (em pixels) da janela a ser criada
    glutInitWindowPosition (00, 00); //Posição inicial do canto superior esquerdo da janela a ser criada

    glutCreateWindow("FALCON HEAVY");//Nome do foguete lançador de satélite;
    glClearColor(0.6235, 0.7098, 1.0, 0.0); //selecionar cor de fundo (Azul CLaro)
    glOrtho (0, 800, 640, 0, -1 ,1);
    glutDisplayFunc(Tela); //Função callback chamada para fazer o desenho
    glutKeyboardFunc(keyboard); //Chamada sempre que uma tecla for precionada
    glutMainLoop(); //Depois de registradas as callbacks, o controle é entregue ao sistema de janelas

    return 0;
}