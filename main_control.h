#include "stm32f4xx.h"         //
#include "N64_GPIO.h"          //   chmando todas
#include "uart2.h"             //   as bibliotecas 
#include "N64_GPIO.h"          //   necessarias para    
#include "uart1.h"             //   o funcionamento do 
#include <stdio.h>             //   codigo
#include <string.h>            //
#include "stm32f4xx.h"         //
#include "stm32f4xx_nucleo.h"  //
#include "lcd.h"               //
/////////////////////////////////

#define PSC_1ms     15499      //
#define ARR_TCONV   999        //  definições de 
#define PSC_100us   1599       //   timer
#define ARR_500ms   88         //
#define RES_ADC     0.0008     //
/////////////////////////////////

#define BAUDGEN (0x8A)  // Baud-rate em 115200

void Delay(__IO uint32_t nCount) { //função utilizada para delay
    while(nCount--) {
    }
}

void print_lcd(char *string) {//função utilizada para imprimir strings no LCD
    while(*string) {
        write_byte(*string, 1);
        string++;
    }
}

int main(void)
{
    TIM10->CR1=TIM_CR1_ARPE|TIM_CR1_CEN;
    RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;
    RCC->AHB1ENR=0x00000087;
    TIM10->CR1=TIM_CR1_ARPE|TIM_CR1_CEN;

    HAL_Init();
    __GPIOA_CLK_ENABLE();
    LCD.enable = GPIO_PIN_0;
    LCD.rs = GPIO_PIN_1;
    LCD.pinos[0] = GPIO_PIN_5;
    LCD.pinos[1] = GPIO_PIN_6;
    LCD.pinos[2] = GPIO_PIN_7;
    LCD.pinos[3] = GPIO_PIN_8;
    LCD.porta = GPIOA;

    init_display();
    char buffer[200]= {0};
    clear();

    GPIOB->MODER   = 0x0 ;
    GPIOB->PUPDR   = 0x202A80 ;
    GPIOB->OTYPER  = 0x0 ;
    GPIOB->OSPEEDR = 0x0 ;

    GPIOC->MODER   = 0x1 ;
    GPIOC->PUPDR   = 0x0 ;
    GPIOC->OTYPER  = 0x0 ;
    GPIOC->OSPEEDR = 0x0 ;


    GPIOB->IDR=0x0;

    char rec;
    unsigned int botao;
    int i = 0;

    N64_GPIO_Init();  // Inicializa E/S placa nucleo
    config_uart2(BAUDGEN);  // Inicializa porta serial 2
    config_uart1(BAUDGEN);  // Inicializa porta serial 2
    /**
         * Configurando Timer 10
         */
    
    TIM10->PSC=PSC_1ms;
    TIM10->ARR=ARR_TCONV;
    TIM10->CR1=TIM_CR1_ARPE|TIM_CR1_CEN;
    int cont = 1;
    cont++;



    while (1)
    {
        cont++;
        receive_uart1(&rec);

        if(rec==97) {
            GPIOC->ODR=0x1;
        }
        else {
            GPIOC->ODR=0x0;
        }
        printf("recebido %c, %d\n",rec);

        if (i > 29) i = 0;
        if (i < 0) i = 29;

        botao=GPIOB->IDR&0x478;


        if(botao==0x20) {
            clear();
            ++i;
            if (i > 29) i = 0;
            if (i < 0) i = 29;
            LD2_TOGGLE;
            printf("Enviando 'a', %d\n",cont);
            send_uart1('a');
            Delay(375000);
        }
        else if(botao==0x400) {
            clear();
            --i;
            if (i > 29) i = 0;
            if (i < 0) i = 29;
            LD2_TOGGLE;
            printf("Enviando 'r', %d\n",cont);
            send_uart1('r');
            Delay(375000);
        }
        else if(botao==0x8) {

            LD2_TOGGLE;
            printf("Enviando 'c', %d\n",cont);
            send_uart1('c');
            Delay(375000);
        }
        else if(botao==0x10) {

            LD2_TOGGLE;
            printf("Enviando 'p', %d\n",cont);
            send_uart1('p');
            Delay(375000);
        }
        else if(botao==0x40){

            LD2_TOGGLE;
            printf("Enviando 'z', %d\n",cont);
            send_uart1('z');
            Delay(375000);
            gotoxy(0,0);
            sprintf(buffer,"                ");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"                ");
            print_lcd(buffer);
            while(1){
                gotoxy(0,0);
                sprintf(buffer,"PLAYER ENCERRADO");
                print_lcd(buffer);
                Delay(375000);
                Delay(375000);
                Delay(375000);
                Delay(375000);
                Delay(375000);
                Delay(375000);
            }
        }
//////////////////////////////////

        switch (i) {

        case -1:
            gotoxy(0,0);
            sprintf(buffer, "Nenhuma faixa re");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer, "produzindo");
            print_lcd(buffer);


            break;

        case 0:
            gotoxy(0,0);
            sprintf(buffer,"Alesso - Heroes");
            print_lcd(buffer);
            break;

        case 1:
            gotoxy(0,0);
            sprintf(buffer,"Bring Me The Hor");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"izont - Deathbeds");
            print_lcd(buffer);
            break;

        case 2:
            gotoxy(0,0);
            sprintf(buffer,"Ela Vai Voltar");
            print_lcd(buffer);
            break;

        case 3:
            gotoxy(0,0);
            sprintf(buffer,"Eminen - Rap God");
            print_lcd(buffer);
            break;

        case 4:
            gotoxy(0,0);
            sprintf(buffer,"Fury Of The Stor");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"m");
            print_lcd(buffer);
            break;

        case 5:
            gotoxy(0,0);
            sprintf(buffer,"Take A Chance Of");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"Me");
            print_lcd(buffer);
            break;

        case 6:
            gotoxy(0,0);
            sprintf(buffer,"Through The Fire");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"And Flames");
            print_lcd(buffer);
            break;


        case 7:
            gotoxy(0,0);
            sprintf(buffer,"I Miss You");
            print_lcd(buffer);
            break;


        case 8:
            gotoxy(0,0);
            sprintf(buffer,"Jet Lag-Simple P");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"lan");
            print_lcd(buffer);
            break;


        case 9:
            gotoxy(0,0);
            sprintf(buffer,"Justin Bieber - ");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"Sorry");
            print_lcd(buffer);
            break;


        case 10:
            gotoxy(0,0);
            sprintf(buffer,"Justin Bieber Wh");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"ere Are You Now");
            print_lcd(buffer);
            break;


        case 11:
            gotoxy(0,0);
            sprintf(buffer,"Linking Park - ");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"Numb");
            print_lcd(buffer);
            break;


        case 12:
            gotoxy(0,0);
            sprintf(buffer,"Somewhere We bel");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"ong");
            print_lcd(buffer);
            break;


        case 13:
            gotoxy(0,0);
            sprintf(buffer,"What I've Done");
            print_lcd(buffer);
            break;

        case 14:
            gotoxy(0,0);
            sprintf(buffer,"manafest - impos");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"sible");
            print_lcd(buffer);
            break;


        case 15:
            gotoxy(0,0);
            sprintf(buffer,"Me Encontra");
            print_lcd(buffer);
            break;


        case 16:
            gotoxy(0,0);
            sprintf(buffer,"Party In The USA");
            print_lcd(buffer);
            break;


        case 17:
            gotoxy(0,0);
            sprintf(buffer,"Pegasus Fantasy");
            print_lcd(buffer);
            break;


        case 18:
            gotoxy(0,0);
            sprintf(buffer,"Pra Voce Lembrar");
            print_lcd(buffer);
            break;


        case 19:
            gotoxy(0,0);
            sprintf(buffer,"Summer Eletro Hits");
            print_lcd(buffer);
            break;

        case 20:
            gotoxy(0,0);
            sprintf(buffer,"See You Again");
            print_lcd(buffer);
            break;


        case 21:
            gotoxy(0,0);
            sprintf(buffer,"Senhor Do Tempo");
            print_lcd(buffer);
            break;


        case 22:
            gotoxy(0,0);
            sprintf(buffer,"SIMPLE PLAN - Cr");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"azy");
            print_lcd(buffer);
            break;


        case 23:
            gotoxy(0,0);
            sprintf(buffer,"So Os Loucos Sab");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"em");
            print_lcd(buffer);
            break;

        case 24:
            gotoxy(0,0);
            sprintf(buffer,"Vibration.mp3");
            print_lcd(buffer);
            break;

        case 25:
            gotoxy(0,0);
            sprintf(buffer,"Summer Paradise");
            print_lcd(buffer);
            break;

        case 26:
            gotoxy(0,0);
            sprintf(buffer,"Welcome To My Li");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"fe");
            print_lcd(buffer);
            break;

        case 27:
            gotoxy(0,0);
            sprintf(buffer,"Wonderwall");
            print_lcd(buffer);
            break;

        case 28:
            gotoxy(0,0);
            sprintf(buffer,"Guitar Battle - ");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"vs. Lou");
            print_lcd(buffer);
            break;

        case 29:
            gotoxy(0,0);
            sprintf(buffer,"Dias De Luta, Di");
            print_lcd(buffer);
            gotoxy(0,1);
            sprintf(buffer,"as De glória");
            print_lcd(buffer);
            break;
        }
//////////////////////////////////
    }
}
