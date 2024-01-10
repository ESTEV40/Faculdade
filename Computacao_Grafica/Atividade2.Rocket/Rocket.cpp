// Estêvão Sousa Vieira - 202210345


/*
  Anotações:
    -> Cronometro de lançamento: ok
    -> Animação de subida do foguete : ok
    -> Animação de descida da plataforma: ok
    -> Animação de escurecimento de céu: ok
    -> Estrelas : ok
    -> Fogo: ok
    -> Nuvem: ok 
    -> fumaça: ok 
    -> desaclopamento stage 1: !ok (tirar os lados)
    -> desavlopamento stage 2: !ok (descer o meio)

    Bônus -> LUA : !ok
*/

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>

#define QTD_STARS 100
#define QTD_CLOUDS 8
#define QTD_FUMACA 30

#define R 0.6235
#define G 0.7098
#define B 1.0

#define R_Corpo 192
#define G_Corpo 192
#define B_Corpo 192

#define R_ASACENTRO 120
#define G_ASACENTRO 20
#define B_ASACENTRO 20

#define R_CDE 30
#define G_CDE 60
#define B_CDE 130

#define ceu_R 0.5294
#define ceu_G 0.8078
#define ceu_B 0.9215

#define NUVEM_R 20
#define NUV_PONTOS 30

using namespace std;

typedef struct Coord{
  GLfloat x;
  GLfloat y;
} Tcoord;

//Relógio
int contagem = 10;

//flags
bool EnableEstrelas = false;
bool EnableFumaca = false;
bool EnableDesacoplar1 = false;
bool EnableDesacoplar2 = false;
bool EnableDecolar = false;
bool EnableLancamento = false;

//vaiaveis de animação
GLfloat DeformacaoFogo1 = 5.0;
GLfloat DeformacaoFogo2 = 10.0;
GLfloat VibracaoAmplitude = 1.0f;
GLfloat Desvio_Rocket_X = 0.0;
GLfloat Desvio_Rocket_Y = 0.0;
GLfloat Desvio_CeuY = 0.0;
GLfloat Desvio_NuvemY = 0.0;
GLfloat Desvio_NuvemResto = 0.0;
GLfloat Desvio_Stars = 0.0;
GLfloat Desvio_BaseY = 0.0;
GLfloat DesvioY_Turbina = 0.0;
GLfloat DesvioX_Turbina = 0.0;
GLfloat DesvioY_TurbinaC = 0.0;
GLfloat ALPHA_NUV = 0.9;
GLfloat ALPHA_FUMACA = 0.5;
GLfloat ALPHA_FogoD = 1.0;
GLfloat ALPHA_FogoE = 1.0;
GLfloat ALPHA_FogoCinf = 1.0;
GLfloat ALPHA_FogoCSup = 0.0;
GLfloat AnguloDesvio = 0.0;

vector<Tcoord> Stars;
vector<vector<Tcoord>> Smoke;
vector<Tcoord> Clouds {
  {100,135},
  {500,432},
  {320,80}
};

// Coordenadas dos pontos para a base do foguete
vector<Tcoord> pontosTrapezioCinza = {
    {082.811, 640.000},
    {116.942, 577.232},
    {688.314, 577.232},
    {722.343, 640.000}
};
vector<Tcoord> pontosQuad1 = {
    {158.506, 640.000},
    {158.506, 603.697},
    {249.402, 603.697},
    {249.402, 640.000}
};
vector<Tcoord> pontosQuad2 = {
    {290.966, 640.000},
    {290.966, 603.697},
    {381.862, 603.697},
    {381.862, 640.000}
};
vector<Tcoord> pontosQuad3 = {
    {423.426, 640.000},
    {423.426, 603.697},
    {514.322, 603.697},
    {514.322, 640.000}
};
vector<Tcoord> pontosQuad4 = {
    {555.886, 640.000},
    {555.886, 603.697},
    {646.782, 603.697},
    {646.782, 640.000}
};

// Coordenadas dos pontos para apoio do foguete
vector<Tcoord> PontosApoioBaseQuad1 = {
    {350.699, 220.608},
    {458.149, 220.608},
    {458.149, 309.439},
    {350.699, 309.439}

};
vector<Tcoord> PontosApoioBaseQuad2 = {
    {350.699, 309.439},
    {458.149, 309.439},
    {458.149, 397.439},
    {350.699, 397.439}
};
vector<Tcoord> PontosApoioBaseQuad3 = {

    {350.699, 397.439},
    {458.149, 397.439},
    {458.149, 486.270},
    {350.699, 486.270}
};
vector<Tcoord> PontosApoioBaseQuad4 = {
    {350.699, 486.270},
    {458.149, 486.270},
    {458.149, 575.102},
    {350.699, 575.102}
};

//Coordenadas dos pontos para o corpo direito do foguete
vector<Tcoord> PontosCorpoD = {
    {424.785, 336.758},
    {458.198, 336.758},
    {458.198, 567.011},
    {424.785, 567.011}};
vector<Tcoord> PontosBicoD = {
    {424.852, 336.675},
    {426.500, 330.002},
    {428.208, 324.899},
    {429.876, 321.104},
    {432.077, 317.495},
    {434.248, 315.061},
    {436.686, 313.292},
    {436.686, 313.292},
    {438.137, 312.612},
    {441.456, 311.841},
    {444.988, 312.670},
    {446.439, 313.350},
    {448.877, 315.119},
    {451.048, 317.553},
    {453.249, 321.162},
    {454.917, 324.957},
    {456.626, 330.060},
    {458.274, 336.733}};
vector<Tcoord> PontosAsaD = {
    {458.198, 491.353},
    {458.198, 567.054},
    {476.983, 567.054},
};
vector<Tcoord> PontosPropulsorD = {
    {430.758, 567.054},
    {451.967, 567.054},
    {458.198, 572.752},
    {424.785, 572.752},
};
vector<Tcoord> PontosApoioD = {
    {421.153, 343.853},
    {424.785, 343.853},
    {424.785, 372.091},
    {421.153, 372.091}

};
vector<Tcoord> PontosFogoD = {
  {424.865, 572.817},
  {458.198, 572.806},
  {441.655, 603.926},
  {428.878, 572.814},
  {454.204, 572.814},
  {441.620, 590.337}
};
  
//Coordenadas dos pontos para o corpo esquerdo do foguete
vector<Tcoord> PontosCorpoE = {
    {350.738, 336.644},
    {384.140, 336.644},
    {384.140, 566.892},
    {350.738, 566.892}
    
};
vector<Tcoord> PontosApoioE = {
    {384.140, 343.853},
    {387.739, 343.853},
    {387.739, 372.091},
    {384.140, 372.091}

};
vector<Tcoord> PontosBicoE = {
    {350.686, 336.725},
    {352.334, 330.052},
    {354.043, 324.949},
    {355.711, 321.154},
    {357.912, 317.545},
    {360.083, 315.111},
    {362.521, 313.342},
    {363.972, 312.662},
    {367.291, 311.891},
    {370.823, 312.749},
    {372.274, 313.429},
    {374.712, 315.198},
    {376.883, 317.632},
    {379.084, 321.241},
    {380.752, 325.036},
    {382.461, 330.139},
    {384.109, 336.812}

};
vector<Tcoord> PontosPropulsorE = {
    {356.709, 567.054},
    {377.911, 567.054},
    {384.140, 572.752},
    {350.738, 572.752}
};
vector<Tcoord> PontosAsaE = {
    {350.738, 491.353},
    {350.738, 566.892},
    {331.953, 566.892}
};
vector<Tcoord> PontosFogoE = {
  {350.815, 572.623},
  {384.148, 572.611},
  {367.605, 603.731},
  {354.828, 572.619},
  {380.154, 572.619},
  {367.570, 590.142}
};

//Coordenadas dos pontos para o corpo direito do foguete
vector<Tcoord> PontosCorpoC = {
    {387.739, 215.693},
    {421.153, 215.693},
    {421.153, 566.687},
    {387.739, 566.687}
};
vector<Tcoord> PontosBicoSupC = {
    {384.425, 148.777},
    {385.291, 145.443},
    {386.323, 142.031},
    {387.542, 138.554},
    {389.234, 134.708},
    {391.267, 131.203},
    {396.081, 125.908},
    {397.370, 124.959},
    {399.078, 124.068},
    {401.188, 123.311},
    {404.240, 122.809},
    {404.648, 122.600},
    {407.701, 123.311},
    {409.811, 124.068},
    {411.518, 124.959},
    {412.808, 125.908},
    {416.526, 129.717},
    {417.622, 131.203},
    {419.654, 134.708},
    {421.346, 138.554},
    {422.565, 142.031},
    {423.598, 145.443},
    {424.464, 148.777}

};
vector<Tcoord> PontosCorpoBicoC = {
    {384.368, 148.841},
    {424.480, 148.841},
    {424.480, 210.047},
    {384.368, 210.047}

};
vector<Tcoord> PontosBicoInfC = {
    {384.368, 210.063},
    {424.480, 210.063},
    {421.157, 215.709},
    {387.368, 215.709}
};
vector<Tcoord> PontosPropulsorCInf = {
    {393.713, 566.685},
    {414.921, 566.685},
    {421.153, 572.561},
    {387.739, 572.561}
};
vector<Tcoord> PontosPropulsorCSup ={
  {387.888, 221.526},
  {393.830, 215.693},
  {415.135, 215.775},
  {421.381, 221.472}
};
vector<Tcoord> PontosFogoCInf = {
  {387.770, 572.590},
  {421.103, 572.590},
  {404.560, 603.699},
  {391.783, 572.587},
  {417.109, 572.587},
  {404.560, 590.110}
};

vector<Tcoord> PontosFogoCSup = {
  {387.717, 221.645},
  {421.131, 221.645},
  {404.429, 243.627},
  {393.923, 221.622},
  {414.925, 221.622},
  {404.427, 239.022}
};

void DesenhaR_Direito(void);
void DesenhaR_Esquerdo(void);
void DesenhaR_PrincipalH(void);
void DesenhaR_PrincipalB(void);
void DesenhaSupBase(void);
void DesenhaBase(void);
void DesenhaEstrelas(void);
void DesenhaFogo(vector<Tcoord> vec, GLfloat);
void Desenha_Nuvem(float X, float Y, float raio,int Numpontos);
void DesenhaFumaca(void);
void atualizaNuvens(void);
void Nuvens(void);
void rotaciona(vector<Tcoord>& pontos, float angulo);
Tcoord calcularCentroObjeto(vector<Tcoord>& pontos);
void InicializaNuvens(void);
void InicializarEstrelas(void);
void InicializarFumaca(void);
void atualizaestrelas(void);
int NumeroAleatorio(int min, int max);
vector<Tcoord> calcularCircunferencia(float centerX, float centerY, float raio, int numPontos);
void update(int valor);
void contar(int valor);
void EscreveContagem(float x, float y, string texto);
void Tela(void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv){

  glutInit(&argc, argv);                       // Estabelece contato com sistema de janelas
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); // Cores dos pixels serão expressos em RGBA
  glutInitWindowSize(800, 640);                // Estabelece o tamanho (em pixels) da janela a ser criada
  glutCreateWindow("FOGUETAO");       // Nome do foguete lançador de satélite;
  glClearColor(0.0, 0.0 , 0.0, 0.0); // selecionar cor de fundo (Preto)
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glOrtho(0, 800, 640, 0, -1, 1);

  srand(time(nullptr));

  InicializarEstrelas();
  InicializaNuvens();
  InicializarFumaca();

  glutDisplayFunc(Tela);      // Função callback chamada para fazer o desenho
  glutKeyboardFunc(keyboard); // Chamada sempre que uma tecla for precionada
  glutTimerFunc(1000, update, 0);
  glutMainLoop(); // Depois de registradas as callbacks, o controle é entregue ao sistema de janelas

  return 0;
}


void update(int value){
    //Prepara Lançamento
    if(contagem <= 5 && contagem > 0) Desvio_Rocket_X = Desvio_Rocket_X >= 0 ? -(VibracaoAmplitude) : VibracaoAmplitude;

    //Ligam os Propulsores;
    if(contagem <= 3 && contagem >= 0) {
      InicializarFumaca();
      EnableLancamento = true;
      ALPHA_FUMACA = (ALPHA_FUMACA - 0.004) < 0 ? 0 : (ALPHA_FUMACA - 0.004);
    }
    //PÓS LANCAMENTO O FOGO TREPIDA
    if(contagem <= 0)  EnableDecolar = true;

    if(contagem <= -30 ) ALPHA_NUV = (ALPHA_NUV - 0.01) < 0 ? 0 : (ALPHA_NUV - 0.01);

    //Lançou
    if(contagem <= 0 && contagem > -1) Desvio_Rocket_Y -= 2;
    //atualiza nuvens no topo da janela
    if(Desvio_NuvemY >= 640) atualizaNuvens();

    //Nuvem Desce
    if(EnableDecolar && contagem <= -1 && Desvio_NuvemY <= 640) Desvio_NuvemY += 3;
    
    //Distanciamento da base
    if(contagem <= -1 && contagem >= -10) Desvio_BaseY += 3;

    //Saindo da atmosfera(tela escurecendo)
    if(contagem <= -2 && contagem >= -55) Desvio_CeuY += 5;

    //Estrelas Aparecem
    if(contagem <= -30) EnableEstrelas = true;

    if(contagem <= -45) {
      ALPHA_FogoD = ALPHA_FogoD - 0.02 > 0 ? ALPHA_FogoD - 0.02 : ALPHA_FogoD;
      ALPHA_FogoE = ALPHA_FogoE - 0.02 > 0 ? ALPHA_FogoE - 0.02 : ALPHA_FogoE;
    }

    if(contagem <= -47) EnableDesacoplar1 = true;

    if(EnableDesacoplar1) {
      DesvioX_Turbina  = DesvioX_Turbina < 160 ? DesvioX_Turbina + 1.8 : DesvioX_Turbina;
      if (DesvioX_Turbina >= 20)DesvioY_Turbina  = DesvioY_Turbina < 360 ? DesvioY_Turbina + 3.0 : DesvioY_Turbina;
      if (DesvioX_Turbina >= 30) AnguloDesvio = AnguloDesvio < 45 ? AnguloDesvio + 1 : AnguloDesvio;
    }

    if(contagem <= -55) ALPHA_FogoCinf = ALPHA_FogoCinf - 0.02 > 0 ? ALPHA_FogoCinf - 0.02 : ALPHA_FogoCinf;

    if(contagem <= -60) EnableDesacoplar2 = true;

    if(EnableDesacoplar2) DesvioY_TurbinaC = DesvioY_TurbinaC < 600 ? DesvioY_TurbinaC + 5 : DesvioY_TurbinaC;


    if(DesvioY_TurbinaC > 40) ALPHA_FogoCSup = ALPHA_FogoCSup < 1 ? ALPHA_FogoCSup + 0.007 : ALPHA_FogoCSup; 

    //atualização de estrelas
    if(Desvio_Stars >= 640) atualizaestrelas();

    //Desvio
    if(EnableEstrelas && Desvio_Stars <= 640) Desvio_Stars++;

    glutPostRedisplay();
    glutTimerFunc(30, update, value);
}

void Tela(void){
  glClear(GL_COLOR_BUFFER_BIT);

  //Quadrado degradê do céu
  glPushMatrix();
    glTranslatef(0.0, Desvio_CeuY, 0.0);
      glBegin(GL_QUADS);
          glColor3f(0.0, 0.0, 0.0);
          glVertex2f(0.0, -8000.0);
          glVertex2f(800.0,-8000.0);
          
          glColor3f(ceu_R, ceu_G, ceu_B);
          glVertex2f(800.0, 640);
          glVertex2f(0.0, 640.0);
      glEnd();
  glPopMatrix();

  //Estrelas do céu
  glPushMatrix();
    if(EnableEstrelas){
      if(Desvio_Stars <= 640) 
        glTranslatef(0.0f, Desvio_Stars - 640, 0.0f);
      DesenhaEstrelas();
    }
  glPopMatrix();

  //Base de lançamento
  glPushMatrix();
    glTranslatef(0.0, Desvio_BaseY, 0.0);
      DesenhaBase();
      DesenhaSupBase();
  glPopMatrix();

  //Foguete
  glPushMatrix();
    glTranslatef(Desvio_Rocket_X, Desvio_Rocket_Y, 0.0f);
      if(EnableLancamento){
        DesenhaFogo(PontosFogoD, ALPHA_FogoD);
        DesenhaFogo(PontosFogoE, ALPHA_FogoE);
        DesenhaFogo(PontosFogoCInf, ALPHA_FogoCinf);
        DesenhaFogo(PontosFogoCSup, ALPHA_FogoCSup);
      }
      glPushMatrix();
        glTranslatef(DesvioX_Turbina, DesvioY_Turbina, 0.0);
          DesenhaR_Direito();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-DesvioX_Turbina, DesvioY_Turbina, 0.0);
          DesenhaR_Esquerdo();
      glPopMatrix();

      DesenhaR_PrincipalH();

      glPushMatrix();
        glTranslatef(0.0, DesvioY_TurbinaC, 0.0);
          DesenhaR_PrincipalB();
      glPopMatrix();
      
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0, Desvio_BaseY, 0.0);
      if(EnableLancamento) DesenhaFumaca();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0f, Desvio_NuvemY, 0.0f);
      Desenha_Nuvem(Clouds[0].x, Clouds[0].y, NUVEM_R, NUV_PONTOS);
      Desenha_Nuvem(Clouds[1].x, Clouds[1].y, NUVEM_R, NUV_PONTOS);
      Desenha_Nuvem(Clouds[2].x, Clouds[2].y, NUVEM_R, NUV_PONTOS);
  glPopMatrix();

  glPushMatrix();
    if(EnableDecolar){
      if(Desvio_NuvemY <= 640)
        glTranslatef(0.0f, Desvio_NuvemY - 640, 0.0f);
      Nuvens();
    }
  glPopMatrix();

  if (contagem >= 0){
    stringstream ss;
    ss << contagem;
    EscreveContagem(20.0f, 30.0f, ss.str());
  }

  glutSwapBuffers();
}

void DesenhaR_Esquerdo(void){

  glPushMatrix();
    if(EnableDesacoplar1) rotaciona(PontosCorpoE, -AnguloDesvio);
      glBegin(GL_QUADS);
        glColor3ub(R_Corpo, B_Corpo, G_Corpo);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosCorpoE.size(); i++){
            glVertex2f(PontosCorpoE[i].x, PontosCorpoE[i].y);
          }

      glEnd();

      glBegin(GL_TRIANGLES);
        glColor3ub(R_ASACENTRO, G_ASACENTRO, B_ASACENTRO);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosAsaE.size(); i++){
            glVertex2f(PontosAsaE[i].x, PontosAsaE[i].y);
          }
      glEnd();

      glBegin(GL_POLYGON);
        glColor3ub(R_CDE, G_CDE, B_CDE);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosBicoE.size(); i++)
          {
            glVertex2f(PontosBicoE[i].x, PontosBicoE[i].y);
          }

      glEnd();

      glBegin(GL_QUADS);
        glColor3ub(86, 86, 86);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosPropulsorE.size(); i++){
            glVertex2f(PontosPropulsorE[i].x, PontosPropulsorE[i].y);
          }

      glEnd();

      glBegin(GL_QUADS);
        glColor3ub(86, 86, 86);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosApoioE.size(); i++){
            glVertex2f(PontosApoioE[i].x, PontosApoioE[i].y);
          }
      glEnd();
  glPopMatrix();
}

void DesenhaR_Direito(void){

  glPushMatrix();
    if(EnableDesacoplar1) rotaciona(PontosCorpoD, AnguloDesvio);
      glBegin(GL_QUADS);
        glColor3ub(R_Corpo, B_Corpo, G_Corpo);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosCorpoD.size(); i++){
            glVertex2f(PontosCorpoD[i].x, PontosCorpoD[i].y);
          }

      glEnd();
      glBegin(GL_TRIANGLES);
        glColor3ub(R_ASACENTRO, G_ASACENTRO, B_ASACENTRO);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosAsaD.size(); i++){
            glVertex2f(PontosAsaD[i].x, PontosAsaD[i].y);
          }
      glEnd();

      glBegin(GL_POLYGON);
        glColor3ub(R_CDE, G_CDE, B_CDE);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosBicoD.size(); i++)
          {
            glVertex2f(PontosBicoD[i].x, PontosBicoD[i].y);
          }

      glEnd();

      glBegin(GL_QUADS);
        glColor3ub(86, 86, 86);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosPropulsorD.size(); i++){
            glVertex2f(PontosPropulsorD[i].x, PontosPropulsorD[i].y);
          }

      glEnd();

      glBegin(GL_QUADS);
        glColor3ub(86, 86, 86);
        // for que desenha de acordo com as coordenadas do vector
          for (int i = 0; i < PontosApoioD.size(); i++){
            glVertex2f(PontosApoioD[i].x, PontosApoioD[i].y);
          }
      glEnd();
  glPopMatrix();
}

void DesenhaR_PrincipalH(void){

  glBegin(GL_QUADS);
    glColor3ub(R_ASACENTRO, G_ASACENTRO, B_ASACENTRO);

    for (int i = 0; i < PontosCorpoBicoC.size(); i++){
      glVertex2f(PontosCorpoBicoC[i].x, PontosCorpoBicoC[i].y);
    }

  glEnd();

  glBegin(GL_QUADS);

    for (int i = 0; i < PontosBicoInfC.size(); i++){
      glVertex2f(PontosBicoInfC[i].x, PontosBicoInfC[i].y);
    }

  glEnd();

  glBegin(GL_POLYGON);

    for (int i = 0; i < PontosBicoSupC.size(); i++){
      glVertex2f(PontosBicoSupC[i].x, PontosBicoSupC[i].y);
    }

  glEnd();

  glBegin(GL_QUADS);
    glColor3ub(86, 86, 86);

    for (int i = 0; i < PontosPropulsorCSup.size(); i++){
      glVertex2f(PontosPropulsorCSup[i].x, PontosPropulsorCSup[i].y);
    }

  glEnd();
}

void DesenhaR_PrincipalB(void){

  glPushMatrix();

    glBegin(GL_QUADS);
      glColor3ub(R_Corpo, G_Corpo, B_Corpo);

      for (int i = 0; i < PontosCorpoC.size(); i++){
        glVertex2f(PontosCorpoC[i].x, PontosCorpoC[i].y);
      }

    glEnd();

    glBegin(GL_QUADS);
      glColor3ub(86, 86, 86);

      for (int i = 0; i < PontosPropulsorCInf.size(); i++){
        glVertex2f(PontosPropulsorCInf[i].x, PontosPropulsorCInf[i].y);
      }

    glEnd();
  glPopMatrix();

}

void DesenhaFogo(vector<Tcoord> vec, GLfloat Alpha){

  float D = EnableDecolar  ? (float)NumeroAleatorio(-3, 5) : -3;

  glBegin(GL_TRIANGLES);
    // Triângulo interno (vermelho)
    glColor4f(0.8313, 0, 0, Alpha);
    glVertex2f(vec[0].x, vec[0].y);
    glVertex2f(vec[1].x, vec[1].y);
    glVertex2f(vec[2].x, vec[2].y + D);
        // Triângulo externo (amarelo)
    glColor4f(1, 0.800, 0, Alpha);
    glVertex2f(vec[3].x, vec[3].y);
    glVertex2f(vec[4].x, vec[4].y);
    glVertex2f(vec[5].x, vec[5].y + D);

  glEnd();
}

void DesenhaSupBase(void){

  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
  glColor3ub(174, 174, 174);

  glVertex2f(PontosApoioBaseQuad1[0].x, PontosApoioBaseQuad1[0].y);
  glVertex2f(PontosApoioBaseQuad1[1].x, PontosApoioBaseQuad1[1].y);
  glVertex2f(PontosApoioBaseQuad1[2].x, PontosApoioBaseQuad1[2].y);
  glVertex2f(PontosApoioBaseQuad1[3].x, PontosApoioBaseQuad1[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad2[0].x, PontosApoioBaseQuad2[0].y);
  glVertex2f(PontosApoioBaseQuad2[1].x, PontosApoioBaseQuad2[1].y);
  glVertex2f(PontosApoioBaseQuad2[2].x, PontosApoioBaseQuad2[2].y);
  glVertex2f(PontosApoioBaseQuad2[3].x, PontosApoioBaseQuad2[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad3[0].x, PontosApoioBaseQuad3[0].y);
  glVertex2f(PontosApoioBaseQuad3[1].x, PontosApoioBaseQuad3[1].y);
  glVertex2f(PontosApoioBaseQuad3[2].x, PontosApoioBaseQuad3[2].y);
  glVertex2f(PontosApoioBaseQuad3[3].x, PontosApoioBaseQuad3[3].y);

  glEnd();
  glBegin(GL_LINE_LOOP);

  glVertex2f(PontosApoioBaseQuad4[0].x, PontosApoioBaseQuad4[0].y);
  glVertex2f(PontosApoioBaseQuad4[1].x, PontosApoioBaseQuad4[1].y);
  glVertex2f(PontosApoioBaseQuad4[2].x, PontosApoioBaseQuad4[2].y);
  glVertex2f(PontosApoioBaseQuad4[3].x, PontosApoioBaseQuad4[3].y);

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

void DesenhaBase(void){

  glColor3ub(86, 86, 86);
    glBegin(GL_QUADS);
      for (int i = 0; i < pontosTrapezioCinza.size(); i++)
        glVertex2f(pontosTrapezioCinza[i].x, pontosTrapezioCinza[i].y);
    glEnd();

  glColor3f(ceu_R, ceu_G, ceu_B);
    glBegin(GL_QUADS);
      for (int i = 0; i < pontosQuad1.size(); i++)
        glVertex2f(pontosQuad1[i].x, pontosQuad1[i].y);
    glEnd();

    glBegin(GL_QUADS);
      for (int i = 0; i < pontosQuad2.size(); i++)
        glVertex2f(pontosQuad2[i].x, pontosQuad2[i].y);
    glEnd();

    glBegin(GL_QUADS);
      for (int i = 0; i < pontosQuad3.size(); i++)
        glVertex2f(pontosQuad3[i].x, pontosQuad3[i].y);
    glEnd();

    glBegin(GL_QUADS);
      for (int i = 0; i < pontosQuad4.size(); i++)
        glVertex2f(pontosQuad4[i].x, pontosQuad4[i].y);
  glEnd();
}

void DesenhaEstrelas(void){
    glColor3f(1.0, 1.0, 1.0);  // Cor branca
    // Desenha as estrelas
      for (int i = 0; i < QTD_STARS; i++) {         
          glPointSize(NumeroAleatorio(1,2));
          glBegin(GL_POINTS);
          glVertex2f(Stars[i].x, Stars[i].y);
          glEnd();
      }
}

void InicializarEstrelas(void){
    for (int i = 0; i < QTD_STARS; i++) {

        float x = rand() % 800;
        float y = rand() % -640;

        Stars.push_back({x, y});
    }
}

void InicializaNuvens(void){
  for (int i = 0; i < QTD_CLOUDS; i++) {

        float x = rand() % 800;
        float y = rand() % -640 + 20;

        Clouds.push_back({x, y});
    }
}

void InicializarFumaca(void){
  vector<Tcoord> vec;
  Smoke.clear();
  for (int i = 0; i < QTD_FUMACA; i++) {

    float y = NumeroAleatorio(570, 585);
    float x = NumeroAleatorio(310, 500);

    vec = calcularCircunferencia(x, y, 10, 30);
    Smoke.push_back(vec);
  }
}

void DesenhaFumaca(){
  glColor4f(0.4392, 0.4392, 0.4392, ALPHA_FUMACA);  // Cor cinza

  for(int i = 0; i < QTD_FUMACA; i++){
    glBegin(GL_POLYGON);
      for(int j = 0; j < 30; j++){
          glVertex2f(Smoke[i][j].x, Smoke[i][j].y);
      }
    glEnd();
  }
}

void atualizaestrelas(void){
    // Atualiza as coordenadas Y para fazer as estrelas se moverem para baixo
    for (int i = 0; i < QTD_STARS; ++i) {
        Stars[i].y += 1.0; //Mantêm a trajetória da nuvem após o limite do desvio ser atingido
        if (Stars[i].y > 640) {
            Stars[i].x = NumeroAleatorio(0,800);
            Stars[i].y = 0;
        }
    }
}

void atualizaNuvens(void){
  for (int i = 0; i < QTD_STARS; ++i) {
        Clouds[i].y += 3.0; //Mantêm a trajetória da nuvem após o limite do desvio ser atingido
        if (Clouds[i].y >= 650) {
            Clouds[i].x = NumeroAleatorio(0,800);
            Clouds[i].y = -10;
        }
    }
}

void EscreveContagem(float x, float y, string texto){
  glColor3f(1.0f, 0.0f, 0.0f); // Cor do texto (vermelho)

  glPushMatrix();
  // Aplica a translação para a posição desejada
    glTranslatef(x, y, 0.0f);
      glRasterPos2f(0, 0);
      // Aplica a cor e desenha o texto
      for (char letra : texto)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letra);
  glPopMatrix(); // Restaura a matriz anterior
}

vector<Tcoord> calcularCircunferencia(float centerX, float centerY, float raio, int Numpontos) {
    vector<Tcoord> pontosCircunferencia;

    for (int i = 0; i < Numpontos; ++i) {
        float Angulo = fmod(2.0 * M_PI * i / Numpontos, 2.0 * M_PI);
        float x = centerX + raio * cos(Angulo);
        float y = centerY + raio * sin(Angulo);

        Tcoord ponto;
        ponto.x = x;
        ponto.y = y;

        pontosCircunferencia.push_back(ponto);
    }

    return pontosCircunferencia;
}

Tcoord calcularCentroObjeto(vector<Tcoord>& pontos) {
    Tcoord centro = {0.0, 0.0};

    // Calcula a média das coordenadas x e y
    for (const auto& ponto : pontos) {
        centro.x += ponto.x;
        centro.y += ponto.y;
    }

    centro.x /= pontos.size();
    centro.y /= pontos.size();

    return centro;
}

void rotaciona(vector<Tcoord>& pontos, float angulo) {

    Tcoord Ponto = calcularCentroObjeto(pontos);
    // Translada para o centro do objeto
    glTranslatef(Ponto.x, Ponto.y, 0.0);

    // Rotaciona em torno do centro do objeto
    glRotatef(angulo, 0.0, 0.0, 1.0);

    // Translada de volta para a posição original
    glTranslatef(-Ponto.x, -Ponto.y, 0.0);
}

void Desenha_Nuvem(float X, float Y, float raio, int Numpontos) {

  vector<Tcoord> Nuvempontos1 = calcularCircunferencia(X,Y,raio,Numpontos);
  vector<Tcoord> Nuvempontos2 = calcularCircunferencia(X+raio,Y,raio, Numpontos);
  vector<Tcoord> Nuvempontos3 = calcularCircunferencia(X+(raio*2),Y,raio, Numpontos);

  glColor4f(0.9176, 0.9411, 0.9294, ALPHA_NUV);

  glBegin(GL_POLYGON);
    for(int i = 0; i < Numpontos; i++){
      glVertex2f(Nuvempontos1[i].x, Nuvempontos1[i].y);
    }
  glEnd();
  glBegin(GL_POLYGON);
    for(int i = 0; i < Numpontos; i++){
      glVertex2f(Nuvempontos2[i].x, Nuvempontos2[i].y);
    }
  glEnd();
  glBegin(GL_POLYGON);
    for(int i = 0; i < Numpontos; i++){
      glVertex2f(Nuvempontos3[i].x, Nuvempontos3[i].y);
    }
  glEnd();
}

void Nuvens(){
  for(int i = 2; i < QTD_CLOUDS; i++)
    Desenha_Nuvem(Clouds[i].x,Clouds[i].y, NUVEM_R, NUV_PONTOS);
}

void contar(int valor){
  contagem--;
  cout << "clock: " << -contagem << endl;
  glutPostRedisplay();
  glutTimerFunc(1000, contar, valor); // Chama a função timer novamente após 1 segundo
}

int NumeroAleatorio(int min, int max) {
    random_device rd;
    mt19937 mt(rd());

    // Crie uma distribuição uniforme dentro do intervalo
    uniform_int_distribution<int> dist(min, max);

    // Gere um número aleatório
    return dist(mt);
}

void keyboard(unsigned char key, int x, int y){
  switch (key){
    case 13: {
              glutTimerFunc(0, contar, 0);
              break;
    };
    case 27 : exit(0); break;
  }
}