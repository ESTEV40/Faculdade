//Criando um chroma key
//Estêvão Sousa Vieira - 202210345

/*
    Observações 28/09 23:13 : primeiramente -> SOCORRO (to com fome)
            Terminei >> Não testei ainda
            Descobri que podia fazer de uma maneira mt mais fácil
            TAFEAO MAS FOI OQ MINHA MENTE PROCESSOU NA HORA

*/
#include <iostream>
#include <fstream>

using namespace std;

typedef struct pixel{
    int RED;
    int GREEN;
    int BLUE;
}Tpixel;

void NovaImagem(string, string,string, int , int, int ,int , int , int );
void Pixel_ArquivoToMatriz(ifstream&, Tpixel**, int, int);
Tpixel** NovaMatrizPix(int, int);
void LiberaMatriz(Tpixel**, int);

int main(){

    string fore, back, NewPic;
    int MaxRed, MinRed;
    int MaxGreen, MinGreen;
    int MaxBlue, MinBlue;
    
    cout << "\t\tCHROMA KEY EM C-PLUSPLUS" << "\n\n";
    cout << "\tInsira o nome dos arquivos das imagens!" << endl;
    
    cout << "\tForeground: ";
    cin >> fore;
    
    cout << "\n\tBackground: ";
    cin >> back;

    cout << "\n\n\tNova Imagem: ";
    cin >> NewPic;

    cout << "\n\tInsira os valores Max e Min de cada banda";
    cout << "\n\t\tRed Maximo: ";
    cin >> MaxRed;
    cout << "\t\tRed Minimo: ";
    cin >> MinRed;
    
    cout << "\n\t\tGreen Maximo: ";
    cin >> MaxGreen;
    cout << "\t\tGreen Minimo: ";
    cin >> MinGreen;

    cout << "\n\t\tBlue Maximo: ";
    cin >> MaxBlue;
    cout << "\t\tBlue Minimo: ";
    cin >> MinBlue;


    NovaImagem(fore, back,NewPic, MaxRed,MinRed, MaxGreen, MinGreen, MaxBlue, MinBlue);


    return 0;
}

Tpixel** NovaMatrizPix(int largura, int altura){

    Tpixel** Vetor = new Tpixel*[largura];
    for(int i = 0; i < largura; i++)
        Vetor[i] = new Tpixel[altura];

    return Vetor;
}

void NovaImagem(string foreground, string background, string NovaImagem, int MaxRed, int MinRed, int MaxGreen, int MinGreen, int MaxBlue, int MinBlue){

    //foreground << imagem com chroma key de fundo a ser preenchido
    //background << imagem com fundo para preencher no chroma key

    ifstream Fore, Back;
    ofstream NewPic;
    string Tipo, linha;
    Tpixel **VetorFore, **VetorBack;
    int Largura_Fore, Altura_Fore, Max_Fore;
    int Largura_Back, Altura_Back, Max_Back;

    Fore.open(foreground, ifstream::in);
    if(!Fore.is_open()){
        cout << "ERRO AO ABRIR O ARQUIVO: " << foreground << endl;
        exit(-1);
    }

    Back.open(background, ifstream::in);
    if(!Back.is_open()){
        cout << "ERRO AO ABRIR O ARQUIVO: " << background << endl;
        exit(-1);
    }

    //Pega os Cabeçalhos e verifica se está no formato correto P3, para leitura de texto
    if(Back >> Tipo >> Largura_Back >> Altura_Back >> Max_Back && Tipo != "P3"){
        cout << "ARQUIVO BACKGROUND NAO ESTA NO FORMATO P3" << endl;
        exit(-1);
    }
    if(Fore >> Tipo >> Largura_Fore >> Altura_Fore >> Max_Fore && Tipo != "P3"){
        cout << "ARQUIVO FOREGROUND NAO ESTA NO FORMATO P3" << endl;
        exit(-1);
    }
 
    //Verifica se as dimensões Background < Foreground
    if((Largura_Fore > Largura_Back) && (Altura_Fore > Altura_Back)){
        cout << "DIMENSOES INVÁLIDAS, EXIGE-SE UM FOREGROUND MENOR QUE O BACKGROUND" << endl;
        exit(-1);
    }

    //Alocação de memória em vetores bidimensionais das dimensões de entrada
    VetorFore = NovaMatrizPix(Largura_Fore, Altura_Fore);

    VetorBack = NovaMatrizPix(Largura_Back, Altura_Back);

    //Atribuindo valores do foreground para o VetorFore
    //Pixel_ArquivoToMatriz(Fore, VetorFore, Largura_Fore, Altura_Fore);
    for(int i = 0; i < Altura_Fore; i++){
        for(int j = 0; j < Largura_Fore; j++){
            Fore >> VetorFore[i][j].RED >> VetorFore[i][j].GREEN >> VetorFore[i][j].BLUE;
        }
    }

    //Atribuindo valores do background para o VetorBack
    //Pixel_ArquivoToMatriz(Back, VetorBack, Largura_Back, Altura_Back);
    for(int i = 0; i < Altura_Back; i++){
        for(int j = 0; j < Largura_Back; j++){
            Back >> VetorBack[i][j].RED >> VetorBack[i][j].GREEN >> VetorBack[i][j].BLUE;
        }
    }

    //Comparando e Criando o novo Arquivo/Foto
    NewPic.open(NovaImagem);
    if(!NewPic.is_open()){
        cout << "ERRO AO ABRIR O ARQUIVO DE SAIDA" << endl;
        exit(-1);
    }

    NewPic << Tipo << "\n" << Largura_Back << " " << Altura_Back << "\n" << Max_Back << "\n";
    
    for(int i = 0; i < Altura_Back; i++){
        for(int j = 0; j < Largura_Back; j++){

            if (i < Altura_Fore && j < Largura_Fore){

                if((VetorFore[i][j].GREEN >= MinGreen && VetorFore[i][j].GREEN <= MaxGreen) && 
                (VetorFore[i][j].BLUE >= MinBlue && VetorFore[i][j].BLUE <= MaxBlue) &&
                (VetorFore[i][j].RED >= MinRed && VetorFore[i][j].RED <= MaxRed)){

                    NewPic << VetorBack[i][j].RED << " " << VetorBack[i][j].GREEN << " " << VetorBack[i][j].BLUE << " ";

                }else {
                    NewPic << VetorFore[i][j].RED << " " << VetorFore[i][j].GREEN << " " << VetorFore[i][j].BLUE << " ";
                }
            }else{
                NewPic << VetorBack[i][j].RED << " " << VetorBack[i][j].GREEN << " " << VetorBack[i][j].BLUE << " ";
            }
        }
        NewPic << "\n";
    }
    
    //Liberando memória alocada
    LiberaMatriz(VetorFore, Largura_Fore);
    LiberaMatriz(VetorBack, Largura_Back);
    
    //Fechando Arquivos
    Fore.close();
    Back.close();
    NewPic.close();
}

void LiberaMatriz(Tpixel** Vetor, int Largura){
    for(int i = 0; i < Largura; i++)
        delete[] Vetor[i];
    delete Vetor;
}

void Pixel_ArquivoToMatriz(ifstream &Arquivo, Tpixel** Vetor , int Largura, int Altura){
    for(int i = 0; i < Altura; i++){
        for(int j = 0; j < Largura; j++){
            Arquivo >> Vetor[i][j].RED >> Vetor[i][j].GREEN >> Vetor[i][j].BLUE;
        }
    }
}