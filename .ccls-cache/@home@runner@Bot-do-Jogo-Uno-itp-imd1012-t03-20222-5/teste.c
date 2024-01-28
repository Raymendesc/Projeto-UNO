#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdbool.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

/*const char naipes[4][4] = {"♥", "♣", "♠", "♦"};

enum suits{
	copas,
	paus,
	espadas,
	ouro
};*/

void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}
void debugint(char *message) { //Aqui para imprimir inteiro, tem que passar um inteiro
  fprintf(stderr, "%d\n", message);
}
void debug3char(char *c1,char *c2, char *c3) {
  fprintf(stderr, "%c%c%c\n", *c1, *c2, *c3);
}
int main() {
  
  
  char players[MAX_LINE];
  char you[MAX_ID_SIZE];
  char *hand;
  char table[MAX_LINE];
  
  hand = (char *) malloc(MAX_LINE);
  

  
  //LENDO AS 4 PRIMEIRAS STRINGS QUE O GERENCIADOR MANDA PARA O BOT
  scanf("PLAYERS %[^\n]\n", players);
  scanf("YOU %s\n", you);
  scanf("HAND %[^\n]\n", hand);
  scanf("TABLE %s\n", table);
/*
  debug(players);
  debug(you);
  debug(hand);
  debug(table);
 */
  /printf("dados iniciais lidos\nplayers = %s\nyou = %s\nhand = %s\ntable = %s\n",players,you,hand,table);/
  //MODELO:
  /*
  PLAYERS b1 b2 b3
  YOU b1
  HAND [ 4♥ 7♦ 2♥ V♠ A♥ 3♦ 2♦ 9♠ ]
  TABLE 8♣
  */
  char action1[MAX_LINE];
  char action2[MAX_LINE];
  char complement1[MAX_ACTION];
  char nova_carta[MAX_ACTION];
  char nova_carta2[MAX_ACTION];
  char nova_carta3[MAX_ACTION];
  char nova_carta4[MAX_ACTION];
  
  char discard[] = "11111";
  char discard_2[] = "111111";
  char complement2[MAX_ACTION];
  int tenho_na_hand = 0;
  

  while (1) {
    //LENDO TURNO
    //MODELO:
    /*
    TURN b1
    */
    //printf("turno:\n");
    scanf("%s %s", action1, complement1);
 

    // MINHA VEZ
    //printf("COMPLEMENT 1: %s\n",complement1);
    //printf("YOU: %s\n",you);
    //printf("result = %d\n",strcmp(complement1,you));
    if (strcmp(complement1, you) == 0) {
      //printf("----------MINHA VEZ-----------\n");
    //printf("minha vez\n");
      //ESCOLHENDO QUAL CARTA DESCARTAR
      //PERCORRENDO A STRING HAND E ESCOLHENDO UMA CARTA QUE
      //DÊ MATCH COM A CARTA DA MESA.
      //debug("TABLE====");
      //printf("%s\n",table);

      
      //printf("  \n");
      //printf("table[0] = %c\n",table[0]);
      //printf("action2 = %s\n",action2);
      
      if (table[0] == 'C' && action2[0] == 'D'){
        printf("BUY 4\n");
        for(int i = 0; i< 4;i++){
        scanf("%s",nova_carta);
        
        for (int i = 0; i < strlen(hand); i++) {
        //ADICIONAR CARTA NA HAND
        //printf("%d\n",i);
        if(hand[i] == ']'){
         //printf("entrou");
          if(nova_carta[0] != '1'){
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = ' ';
          hand[i+5] = ']';
          hand[i+6] = '\0';
          }
          else{
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = nova_carta[4];
          hand[i+5] = ' ';
          hand[i+6] = ']';
          hand[i+7] = '\0';
            
          }

         debug(hand);
          break;
        }

          
        }
          }
      }

      else if (table[0] == 'V' && action2[0] == 'D'){
        printf("BUY 2\n");
        for(int i = 0; i< 2;i++){
        scanf("%s",nova_carta);
        
        for (int i = 0; i < strlen(hand); i++) {
        //ADICIONAR CARTA NA HAND
        //printf("%d\n",i);
        if(hand[i] == ']'){
         //printf("entrou");
          if(nova_carta[0] != '1'){
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = ' ';
          hand[i+5] = ']';
          hand[i+6] = '\0';
          }
          else{
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = nova_carta[4];
          hand[i+5] = ' ';
          hand[i+6] = ']';
          hand[i+7] = '\0';
            
          }

         debug(hand);
          break;
        }

          
        }
          }
        
        
      }
      else{
//-=-=-=-=-=-=-=-=MINHA VEZ DE DISCARD=-=-=-=--=-=-===-=-
      tenho_na_hand = 0;
      for (int i = 0; i < strlen(hand); i++) {
      
      if(hand[i] != ' ' && hand[i] != '[' && hand[i] != ']'){

       ///// printf("%c\n",hand[i]);
        //COMPARANDO NÚMERO OU LETRA DA CARTA DA MESA COM AS DA HAND
        //SE FOR IGUAL EU POSSO DISCARTAR.
        ////printf("testando se %c == %c E %c == %c\n",hand[i],table[0],table[0] =='1');
        if(hand[i] == table[0] && table[0] == '1'){
		  //debug("Caminho secreto");
          debug("primeiro");
          //CASO A CARTA SEJA 10
          discard_2[0] = hand[i];
          discard_2[1] = hand[i+1];
          discard_2[2] = hand[i+2];
          discard_2[3] = hand[i+3];
          discard_2[4] = hand[i+4];
          discard_2[5] = '\0';
          
          //printf("DISCARD %c%c%c%c\0\n",hand[i],hand[i+1],hand[i+2],hand[i+3]);
          printf("DISCARD %s\n", discard_2);
          tenho_na_hand = 1;
          debug(discard_2);
          break;
          }
          
        else if(hand[i] == table[0]){
          debug("segundo");
          //CASO A CARTA NÃO SEJA 10
          discard[0] = hand[i];
          discard[1] = hand[i+1];
          discard[2] = hand[i+2];
          discard[3] = hand[i+3];
          discard[4] = '\0';

          printf("DISCARD %s\n", discard);
          tenho_na_hand = 1;
          debug(discard);
          break;
        }
          //JÁ DESCARTOU, NÃO PRECISO MAIS PERCORRER A HAND
          
        
        
        //SE O NÚMERO OU LETRA DA CARTA DA HAND NÃO FOR IGUAL
        //A DA MESA COMPARAR O NAIPE
        //CADA SÍMBOLO TEM 3 CARACTERES DIFERENTES, PARA DAR MATCH NO SIMBOLO
        //DEVO COMPARAR  SE OS 3 CARACTERES SÃO IGUAIS.
      
        else if (hand[i] == table[1] && hand[i+1] == table[2] && hand[i+2] == table[3]){               
          
          if (hand[i-2] =='1'){
            debug("terceiro");
          discard_2[0] = hand[i-2];
          discard_2[1] = hand[i-1];
          discard_2[2] = hand[i];
          discard_2[3] = hand[i+1];
          discard_2[4] = hand[i+2];
          discard_2[5] = '\0';
          printf("DISCARD %s\n",discard_2);
            tenho_na_hand = 1;
            debug(discard_2);
            break;
          }
          else{
            debug("quarto");
            
			      discard[0] = hand[i-1];
          	discard[1] = hand[i];
          	discard[2] = hand[i+1];
          	discard[3] = hand[i+2];
          	discard[4] = '\0';
		
	      	debug(discard);
			  
          	printf("DISCARD %s\n", discard);
            tenho_na_hand = 1;
            break;
          }
        }
          //printf("DISCARD %c%c%c%c\n",hand[i-1],hand[i],hand[i+1],hand[i+2]);
          

          
          
          
          
          
          
          
        }
        
      }

        

      if (tenho_na_hand == 0){
        printf("BUY 1\n");
        scanf(" %s",nova_carta);
        //printf("nova_carta = %s\n",nova_carta);
        for (int i = 0; i < strlen(hand); i++) {
        //ADICIONAR CARTA NA HAND
        //printf("%d\n",i);
        if(hand[i] == ']'){
         //printf("entrou");
          if(nova_carta[0] != '1'){
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = ' ';
          hand[i+5] = ']';
          hand[i+6] = '\0';
          }
          else{
          hand[i] = nova_carta[0];
          hand[i+1] = nova_carta[1];
          hand[i+2] = nova_carta[2];
          hand[i+3] = nova_carta[3];
          hand[i+4] = nova_carta[4];
          hand[i+5] = ' ';
          hand[i+6] = ']';
          hand[i+7] = '\0';
          }

         debug(hand);
          break;
        }

          
        }
      }

        }
//-=-=-=-=-=-=/\/\/\MINHA VEZ DE DISCARD/\/\/\-=-=-=-=-=-=--=-=-=-
      }

    
    
    // NÃO É MINHA VEZ, DEVO LER A JOGADA DE OUTRO JOGADOR E ATUALIZAR A TABLE
    // CASO A JOGADA TENHA UMA CARTA DE AÇÃO E EU SEJA O PRÓXIMO, TRATAR.
    else {
    //printf("------VEZ DE %s-------\n",complement1);
    //LENDO AÇÃO DE OUTRO JOGADOR
    //printf("Ação de %s:\n",complement1);
    scanf("%s %s", action2, complement1);
      
    //CASO A AÇÃO DO JOGADOR SEJA DESCARTAR UM ÁS, LER O COMPLEMENTO 2.
    if(complement1[0] == 'A'){
      
      scanf("%s",complement2);

      //ATUALIZANDO A TABLE
      complement1[1] = complement2[0];
      complement1[2] = complement2[1];
      complement1[3] = complement2[2];
      
//      table[0] == 'A';
      debug(complement1);
        strcpy(table,complement1);
      debug(table);
        //printf("NOVA TABLE: %s\n",table);
      }
    //CASO A AÇÃO DO JOGADOR SEJA UM CORINGA, LER O COMPLEMENTO 2.
    else if(complement1[0] == 'C') {
      //printf("CAMINHO SECRETISSOMO\n");
      scanf("%s",complement2);

      //ATUALIZANDO A TABLE
      complement1[1] = complement2[0];
      complement1[2] = complement2[1];
      complement1[3] = complement2[2];
      strcpy(table,complement1);
      printf("NOVA TABLE: %s\n",table);
      //ATUALIZANDO TABLE
    }
    else{
      strcpy(table,complement1);
      //printf("nova_mesa = %s\n",table);
    }
    
  }

  }
}