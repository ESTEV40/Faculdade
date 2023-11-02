#include <bits/stdc++.h>
using namespace std;

int main()
{
    int Min_Vermelho=0, Max_Vermelho=0, Min_Verde=0, Max_Verde=0, Min_Azul=0, Max_Azul=0;

    // Define os nomes dos arquivos
    string Nome_Background, Nome_Chroma, Nome_Saida, Cor;
    cout << "Digite o nome do arquivo do Background (Ex: background.ppm)" << endl;
    cin >> Nome_Background;

    cout << "Digite o nome do arquivo do Chroma (Ex: chroma.ppm)" << endl;
    cin >> Nome_Chroma;

    cout << "Digite o nome do arquivo de Saida (Ex: saida.ppm)" << endl;
    cin >> Nome_Saida;

    system("cls || clear");

    // Define qual cor iremos usar para o Background
    cout << "Diga qual a cor de banda de fundo (ESCREVA APENAS: \"azul\" ou \"verde\")" << endl;
    cin >> Cor;

    system("cls || clear");

    // Define os minimos e maximos para o RGB
    // Vermelho
    cout << "Agora informe os valores minimos e maximos da banda VERMELHA" << endl;
    cout << "(ESCREVA OS 2 VALORES SEPARADOS POR APENAS UM ESPACO)" << endl;
    cout << "Minimo e maximo do vermelho: " << endl;
    cin >> Min_Vermelho >> Max_Vermelho;
    cout << endl
         << endl;

    system("cls || clear");

    // Verde
    cout << "Agora informe os valores minimos e maximos da banda VERDE" << endl;
    cout << "(ESCREVA OS 2 VALORES SEPARADOS POR APENAS UM ESPACO)" << endl;
    cout << "Minimo e maximo do verde: " << endl;
    cin >> Min_Verde >> Max_Verde;
    cout << endl
         << endl;

    system("cls || clear");

    // Azul
    cout << "Agora informe os valores minimos e maximos da banda AZUL" << endl;
    cout << "(ESCREVA OS 2 VALORES SEPARADOS POR APENAS UM ESPACO)" << endl;
    cout << "Minimo e maximo do azul: " << endl;
    cin >> Min_Azul >> Max_Azul;
    cout << endl
         << endl;

    system("cls || clear");

    ifstream background, chroma;
    background.open(Nome_Background, ifstream::in);
    if (!(background.is_open()))
    {
        cout << "ERRO AO ABRIR O BACKGROUND" << endl;
        cout << Nome_Background << endl;
        return -1;
    }
    chroma.open(Nome_Chroma, ifstream::in);
    if (!(chroma.is_open()))
    {
        cout << "ERRO AO ABRIR O CHROMA" << endl;
        cout << Nome_Chroma << endl;
        return -2;
    }

    // Pega o cabeçario do background
    string ignora1;
    int Backgorund_Largura, Backgorund_Altura, Backgorund_Pixel_Max;
    background >> ignora1;
    background >> Backgorund_Largura >> Backgorund_Altura >> Backgorund_Pixel_Max;

    // Testa pro Background
    cout << "Backgorund_Largura: " << Backgorund_Largura << endl;
    cout << "Backgorund_Altura: " << Backgorund_Altura << endl;

    // Pega o cabeçario da img (chroma key)
    string ignora2;
    int Chroma_Largura, Chroma_Altura, Chroma_Pixel_Max;
    chroma >> ignora2;
    chroma >> Chroma_Largura >> Chroma_Altura >> Chroma_Pixel_Max;


    // Testa pro Background
    cout << "Chroma_Largura: " << Chroma_Largura << endl;
    cout << "Chroma_Altura: " << Chroma_Altura << endl;

    // Testa se o Chroma é menor que o Backgorund
    if (Chroma_Largura > Backgorund_Largura || Chroma_Altura > Backgorund_Altura)
    {
        cout << "ERRO A IMAGEM DE CHROMA É MAIOR QUE O BACKGROUD" << endl;
        return -3;
    }

    ofstream saida(Nome_Saida);
    if (!saida.is_open())
    {
        cout << "ERRO AO CRIAR ARQUIVO DE SAIDA" << endl;
        return -4;
    }

    // Montando o cabeiçario da saida
    saida << "P3" << endl;
    saida << Backgorund_Largura << " " << Backgorund_Altura << endl;
    saida << Backgorund_Pixel_Max << endl;

    // Auxialires para pegar os valores analisados no momento
    int Vermelho, Verde, Azul;

    if(Cor ==  "azul")
    {
        for (int i = 0; i < Backgorund_Altura; i++)
        {
            for (int j = 0; j < Backgorund_Largura; j++)
            {
                if (i > (Backgorund_Altura - Chroma_Altura) && j < Chroma_Largura) 
                {
                    chroma >> Vermelho >> Verde >> Azul;
                    if(!((Vermelho < 200) && (Verde < 200) && (Azul >= 200)))
                    {
                            saida << Vermelho << " " << Verde << " " << Azul << " ";
                            background >> Vermelho >> Verde >> Azul;
                    }
                    else
                    {
                        background >> Vermelho >> Verde >> Azul;
                        saida << Vermelho << " " << Verde << " " << Azul << " ";
                    }
                }
                else
                {
                    background >> Vermelho >> Verde >> Azul;
                    saida << Vermelho << " " << Verde << " " << Azul << " ";
                }
            }
            saida << endl;
        }
    }
    else
    {
        for (int i = 0; i < Backgorund_Altura; i++)
        {
            for (int j = 0; j < Backgorund_Largura; j++)
            {
                if (i <  Chroma_Altura && j < Chroma_Largura) 
                {
                    chroma >> Vermelho >> Verde >> Azul;
                    if(!((Vermelho < 200) && (Azul < 200) && (Verde >= 200)))
                    {
                            saida << Vermelho << " " << Verde << " " << Azul << " ";
                            background >> Vermelho >> Verde >> Azul;
                    }
                    else
                    {
                        background >> Vermelho >> Verde >> Azul;
                        saida << Vermelho << " " << Verde << " " << Azul << " ";
                    }
                }
                else
                {
                    background >> Vermelho >> Verde >> Azul;
                    saida << Vermelho << " " << Verde << " " << Azul << " ";
                }
            }
            saida << endl;
        }
    }

    return 0;
}