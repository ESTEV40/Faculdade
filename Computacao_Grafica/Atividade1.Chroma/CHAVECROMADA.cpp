//Criando um chroma key
//Estêvão Sousa Vieira - 202210345

#include <iostream>
#include <fstream>

using namespace std;

void NovaImagem(string, string,string, int , int, int ,int , int , int );

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

    NovaImagem(fore, back,NewPic, MaxRed, MinRed, MaxGreen, MinGreen, MaxBlue, MinBlue);
    return 0;
}
void NovaImagem(string foreground, string background, string NovaImagem, int MaxRed, int MinRed, int MaxGreen, int MinGreen, int MaxBlue, int MinBlue){

    //foreground << imagem com chroma key de fundo a ser preenchido
    //background << imagem com fundo para preencher no chroma key

    ifstream Fore, Back;
    ofstream NewPic;
    string Tipo;
    int R_Fore, G_Fore, B_Fore;
    int R_Back, G_Back, B_Back;
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
 
    //Verifica se as dimensões Background > Foreground
    if((Largura_Fore > Largura_Back) && (Altura_Fore > Altura_Back)){
        cout << "DIMENSOES INVÁLIDAS, EXIGE-SE UM FOREGROUND MENOR QUE O BACKGROUND" << endl;
        exit(-1);
    }

    //Comparando e Criando o novo Arquivo/Foto
    NewPic.open(NovaImagem);
    if(!NewPic.is_open()){
        cout << "ERRO AO ABRIR O ARQUIVO DE SAIDA" << endl;
        exit(-1);
    }

    NewPic << Tipo << "\n" << Largura_Fore << " " << Altura_Fore << "\n" << Max_Back << "\n";
    
    //percorre os dois arquivos e altera o novo diretamente
    for(int i = 0; i < Altura_Fore; i++){
        for(int j = 0; j < Largura_Fore; j++){

            Back >> R_Back >> G_Back >> B_Back;
            Fore >> R_Fore >> G_Fore >> B_Fore;

            if((G_Fore >= MinGreen && G_Fore <= MaxGreen) && 
                (B_Fore >= MinBlue && B_Fore <= MaxBlue) && 
                (R_Fore >= MinRed && R_Fore <= MaxRed)){

                NewPic << R_Back << " " << G_Back << " " << B_Back << " ";

            }else NewPic << R_Fore << " " << G_Fore << " " << B_Fore << " ";
        }
        //solução do bug do background
        for(int K = Largura_Fore; K < Largura_Back; K++){
            Back >> R_Back >> G_Back >> B_Back;
        }
        NewPic << "\n";
    }
    
    //Fechando Arquivos
    Fore.close();
    Back.close();
    NewPic.close();
}