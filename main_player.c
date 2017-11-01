#include "funcoes.h"  //chamando funções necessárias ao código que se encontram em outro arquivo

int main() {
    system("color 02");
    setlocale(LC_ALL, "Portuguese");
    system("cls");


    HANDLE hcom;                       //
    unsigned long n;                   //
    char *ncom="COM3",c=1,l=1;         // Variaveis e inicializações
    int baud=115200;                   // de funções referentes ao uso
    char dado[1];                      // de portas serial para comunicação
    hcom=AbreComm(ncom,baud);          // entre Dev e ARM
    if(hcom==INVALID_HANDLE_VALUE) {   //
        getch();                       // 
        return 1;                      //
    }                                  //
/////////////////////////////////////////

    InitFMOD();                       // Variáveis e inicializações 
    FSOUND_SAMPLE * son = NULL;       // de funções referentes ao uso 
    int channel;                      // do sistema de som
////////////////////////////////////////

    char nome[250];
    char opcao=*dado;
    int i = 0, j = -95, k=-63, status;

    faixas(); 

    gotoxy(1,22); //Utilizei gotoxy para modificar apenas uma parte da linha, e não ela inteira
    printf("Faixa selecionada: nenhuma faixa selecionada");
    gotoxy(1,23);
    printf("Reproduzindo faixa: nenhuma faixa reproduzindo ");
    WriteFile(hcom,"f", 1, &n, NULL); //função utilizada para enviar valores à porta serial, para que o bluetooth receba e mande para o ARM
    ReadFile(hcom, dado, 1, &n, NULL);//função que le a porta serial
    while(!n) {  //enquanto não chegar um byte via serial, o código fica trancado no while
            if(FSOUND_IsPlaying(channel)==FALSE){ //função para verificar se está ou não tocando música
                    WriteFile(hcom,"u", 1, &n, NULL); //caso não esteja, enviamos a letra 'u' para a porta serial, que envia ao ARM
                }
                ReadFile(hcom, dado, 1, &n, NULL); 
                opcao=*dado;//atribuimos à variável opção o valor lido na porta serial
                if(opcao=='z') return 0; //caso o valor lido na porta serial seja == 'z', encerra-se o programa.
            }
    
    while (opcao != 'z') //enquanto diferente de ESC
    {
        
        if(opcao=='p') {
            status = 0;
            FSOUND_SetPaused(FSOUND_ALL, TRUE); //função utilizada para pausar uma música em andamento
            WriteFile(hcom,"b", 1, &n, NULL); //ao pausarmos, enviamos a letra 'b' para a porta serial
            status=0;
            j=1;
            k=i;
            
        }
    
        while (opcao != 'c') {


            if (opcao == 'A' || opcao == 'a') {
                ++i; //sobe faixa
                
            } else if (opcao == 'R' || opcao == 'r') {

                --i; //desce faixa
               
            }
            else if(opcao=='p') {
                if(!(k==i&&j==1)) {
                    status = 0;
                    FSOUND_SetPaused(FSOUND_ALL, TRUE); //função utilizada para pausar uma música em andamento
                    WriteFile(hcom,"b", 1, &n, NULL); //ao pausarmos, enviamos a letra 'b' para a porta serial
                    status=0;
                    j=1;
                    k=i;
                    
                }
            }

            if (i > 29) i = 0;
            if (i < 0) i = 29;

            selecionaFaixa(i,nome); //chamamos a função selecionaFaixa que recebe o valor inteiro de i e o a string nome
        
            ReadFile(hcom, dado, 1, &n, NULL); //função para ler a porta serial
            while(!n) { //enquanto não receber byte ficará trancado no while
                if(FSOUND_IsPlaying(channel)==FALSE){//verificando se ha música tocando
                    WriteFile(hcom,"u", 1, &n, NULL); //caso não haja, eniar a letra 'u'
                }
                ReadFile(hcom, dado, 1, &n, NULL);
                opcao=*dado;//atribuimos à variável opção o valor lido na porta serial
                if(opcao=='z') return 0;
            }

        }



        if(!(j==1&&i==k)) {
            FSOUND_Close ( );//encerramos o periferico de som
            InitFMOD();//iniciamos o periferico de som
            son = FSOUND_Sample_Load(FSOUND_FREE, nome, FSOUND_HW2D, 0, 0); //atribuimos a variavel son uma função que decodifica um arquivo de música estatico em memória, é aqui que slecionamos qual música vai tocar
            channel = FSOUND_PlaySoundEx(FSOUND_FREE, son, NULL, FALSE); //carregamos o canal de som que vamos utilizar
            WriteFile(hcom,"a", 1, &n, NULL); //enviamos a letra 'a' para dizer que há música tocando
        }
        else {
            FSOUND_SetPaused (FSOUND_ALL, FALSE ); //funçao para despausar uma música
            WriteFile(hcom,"a", 1, &n, NULL); //enviamos a letra 'a' para dizer que há música tocando
        }


        gotoxy(21, 23);
        printf("                                                    ");
        if (i<9) {
            gotoxy(21, 23);
            printf("0%d ", i + 1);
            gotoxy(24, 23);
            puts(nome);
        } else {
            gotoxy(21, 23);
            printf("%d ", i + 1);
            gotoxy(24, 23);
            puts(nome);
        }

        ReadFile(hcom, dado, 1, &n, NULL);
        while(!n) { //enquanto nao receber um byte, o código fica trancado no while
                if(FSOUND_IsPlaying(channel)==FALSE){//caso nao haja música tocando
                    WriteFile(hcom,"u", 1, &n, NULL); //envia se a letra 'u' para a porta serial
                }
                ReadFile(hcom, dado, 1, &n, NULL);//lemos novamente a porta serial
                opcao=*dado;//atribuimos o valor lido a variável opção
                if(opcao=='z') return 0; 
            }
        
    }

    return 0;
}
