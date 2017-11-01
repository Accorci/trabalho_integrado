#include <windows.h> // Windows Header
#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <fmod/fmod.h> // FMOD Header
#include <locale.h>


HANDLE AbreComm(char *nomecom, int baudrate)                                      //
{                                                                                 //
    HANDLE hcom; //cria um ponteiro de nome hcom                                  //
    DCB cdcb;    //nomeia a estrutura DCB (Device Control Block)                  /	
    //utilizada para definir todos os parâmetros da comunicação                   // 	Funções utilizadas
    COMMTIMEOUTS comto; //nomeia a estrutura COMMTIMEOUTS (COMMon TIME OUTS)      //	para iniciar todas as 
    //utilizada para definir os timeouts da comunicação                           //	valores referentes ao
    hcom = CreateFile(                                                            //	uso das portas serial
               nomecom, //nome do arquivo                                         //	para comunicação entre
               GENERIC_READ | GENERIC_WRITE, //abre arquivo para leitura/escrita  //	Dev e ARM
               0, //indica que o arquivo não pode ser compartilhado               //
               NULL, //utiliza a estrutura default para as funções de segurança   //
               OPEN_EXISTING, //abre o arquivo, se não existir, retorna erro      //
               FILE_ATTRIBUTE_NORMAL, //o arquivo deve ser utilizado sozinho      //
               NULL); //sem gabarito de atributos                                 //
                                                                                  //
    if(hcom == INVALID_HANDLE_VALUE) // testa falha na abertura do arquivo        //
    {                                                                             //
        fprintf(stderr, "Nao abriu a %s\n", nomecom);                             //
        return hcom;                                                              //
    }                                                                             //
                                                                                  //
    GetCommState(hcom, &cdcb); //le os parâmetros de comunicação atuais           //
    cdcb.BaudRate    = baudrate; //define a taxa de transmissão                   //
    cdcb.ByteSize    = 8; //define o tamanho do dado - 8 bits                     //
    cdcb.StopBits    = ONESTOPBIT; //define o tamanho do stop bit - 1 stop bit    //
    cdcb.Parity      = NOPARITY; //define o tipo de paridade - sem paridade       //
																				  //
                                                                                  //
                                                                            	  //
    if(!SetCommState(hcom,&cdcb)) //seta os novos parâmetros de comunicação       //
    {                                                                             //
        fputs("SetCommState", stderr);                                            //
        return INVALID_HANDLE_VALUE;                                              //
    }                                                                             //
                                                                                  //
                                                                                  //
    GetCommTimeouts(hcom, &comto); //Le os parâmetros atuais de COMMTIMEOUTS      //
    comto.ReadIntervalTimeout         = MAXDWORD;//tempo máximo entre a chegada   //
    //de dois caracters consecutivos(ms)                                          //
    comto.ReadTotalTimeoutMultiplier  =    0;                                     //
    comto.ReadTotalTimeoutConstant    =    0;                                     //
    comto.WriteTotalTimeoutMultiplier =    0;                                     //
    comto.WriteTotalTimeoutConstant   =    0;                                     //
    SetCommTimeouts(hcom, &comto); //seta os parâmetros de COMMTIMEOUTS           //
    return hcom;                                                                  //
}                                                                                 //
////////////////////////////////////////////////////////////////////////////////////


void gotoxy(int x, int y) {                                                       //
    COORD c;                                                                      //
    c.X = x - 1;                                                                  //	função gotoxy
    c.Y = y - 1;                                                                  //
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);                 //
}                                                                                 //
////////////////////////////////////////////////////////////////////////////////////


void InitFMOD() {																   //
    FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND); // DirectSound						   //	Funções para inicialização
    FSOUND_SetDriver(0); // Sound Driver (default 0)							   //	do sistema de som
    FSOUND_SetMixer(FSOUND_MIXER_AUTODETECT); // Mixer							   //
    FSOUND_Init(44100, 32, 0); // 44.1 kHz and 32 channels						   //
} 																				   //
/////////////////////////////////////////////////////////////////////////////////////

void faixas () {																											   //
    printf("Lista de faixas disponíveis\n");                               													   //
    printf("  \nFaixa 01: Alesso - Heroes                                Faixa 16: Me Encontra");                              //
    printf("  \nFaixa 02: Bring  Me  The  Horizont - Deathbeds           Faixa 17: Myley Cyrus - Party In The USA");           //
    printf("  \nFaixa 03: Ela Vai Voltar                                 Faixa 18: Pegasus Fantasy");                          //   
    printf("  \nFaixa 04: Eminen - Rap God                               Faixa 19: Pra Você Lembrar");                         // 
    printf("  \nFaixa 05: Fury Of The Storm                              Faixa 20: Psy Trance - Summer Eletro Hits");          //
    printf("  \nFaixa 06: Take A Chance of Me                            Faixa 21: See You Again");                            //
    printf("  \nFaixa 07: Through The Fire And Flames                    Faixa 22: Senhor Do Tempo");                          //  menu
    printf("  \nFaixa 08: I Miss You                                     Faixa 23: SIMPLE PLAN - Crazy");                      //
    printf("  \nFaixa 09: Jet Lag-Simple plan                            Faixa 24: Só Os Loucos Sabem");                       //
    printf("  \nFaixa 10: Justin Bieber - Sorry                          Faixa 25: Vibration");                                //
    printf("  \nFaixa 11: Justin Bieber - Where Are You Now              Faixa 26: Simple Plan - Summer Paradise");            //
    printf("  \nFaixa 12: Linking Park - Numb                            Faixa 27: Welcome To My Life");                       //
    printf("  \nFaixa 13: Linking Park - Somewhere I Belong              Faixa 28: Wonderwall");							   //
    printf("  \nFaixa 14: Linking Park - What Ive Done                   Faixa 29: Guitar Battle - vs. Lou");				   //
    printf("  \nFaixa 15: manafest - impossible                          Faixa 30: Dias De Luta, Dias De Glória");			   //
    printf("  \n");																											   //
    printf("  \nPressione 'p' para pausar                                Pressione 'c para dar play");						   //
    printf("  \nPressione 'a' para avançar de faixa                      Pressione 'r' para retroceder de faixa");			   //
 																															   //
}																															   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void selecionaFaixa(int i, char *p) {//função que define o que a string nome vai ser, para definir qual música tocar
    int j;

    char frase[500];
    switch (i) {//recebemos se a música está subindo ou descendo

    case 0:

        strcpy(frase, "Alesso - Heroes.mp3\0"); //copiamos o nome da música para dentro da string frase
        for(j=0; j<21; j++) {
            *(p+j)=frase[j]; //utilizamos ponteiros para que nao seja necessário retornar nada, pois uma modificaçao direto na memória se mantém tanto aqui quanto no código principal

        }


        break;

    case 1:
        strcpy(frase, "Bring  Me  The  Horizont - Deathbeds.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 2:
        strcpy(frase, "Ela Vai Voltar.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 3:
        strcpy(frase, "Eminen - Rap God.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 4:
        strcpy(frase, "Fury Of The Storm.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 5:
        strcpy(frase, "Take A Chance Of Me.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 6:
        strcpy(frase, "Through The Fire And Flames.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 7:
        strcpy(frase, "I Miss You.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 8:
        strcpy(frase, "Jet Lag-Simple Plan.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 9:
        strcpy(frase, "Justin Bieber - Sorry.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 10:
        strcpy(frase, "Justin Bieber - Where Are You Now.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 11:
        strcpy(frase, "Linking Park - Numb.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 12:
        strcpy(frase, "Linking Park - Somewhere I Belong.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 13:
        strcpy(frase, "Linking Park - What I've Done.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 14:
        strcpy(frase, "manafest - impossible.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 15:
        strcpy(frase, "Me Encontra.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 16:
        strcpy(frase, "Myley Cyrus - Party In The USA.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 17:
        strcpy(frase, "Pegasus Fantasy.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 18:
        strcpy(frase, "Pra Você Lembrar.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 19:
        strcpy(frase, "Psy Trance - Summer Eletro Hits.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 20:

        strcpy(frase, "See You Again.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 21:
        strcpy(frase, "Senhor Do Tempo.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 22:
        strcpy(frase, "SIMPLE PLAN - Crazy.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;


    case 23:
        strcpy(frase, "Só Os Loucos Sabem.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 24:
        strcpy(frase, "Vibration.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 25:
        strcpy(frase, "Simple Plan - Summer Paradise.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 26:
        strcpy(frase, "Welcome To My Life.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 27:
        strcpy(frase, "Wonderwall.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 28:

        strcpy(frase, "Guitar Battle - vs. Lou.mp3\0");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    case 29:

        strcpy(frase, "Dias De Luta, Dias De Glória.mp3");
        for(j=0; j<strlen(frase)+2; j++) {
            *(p+j)=frase[j];
        }
        break;

    }

    gotoxy(20, 22);
    printf("                                                    ");
    if (i < 9) {
        gotoxy(21, 22);
        printf("0%d ", i + 1);
        gotoxy(24, 22);
        puts(frase);
    } else {
        gotoxy(21, 22);
        printf("%d ", i + 1);
        gotoxy(24, 22);
        puts(frase);
    }
}