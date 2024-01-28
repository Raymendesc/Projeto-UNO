#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdbool.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

const char naipes[4][4] = {
  "♥",
  "♣",
  "♠",
  "♦"
};

enum suits {
  copas,
  paus,
  espadas,
  ouro
};

void debug(char * message) {
  fprintf(stderr, "%s\n", message);
}

int main() {

  setbuf(stdin, NULL); // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);
  char players[MAX_LINE];
  char you[MAX_ID_SIZE];
  char * hand;
  char table[MAX_LINE];

  hand = (char * ) malloc(MAX_LINE);

  //LENDO AS 4 PRIMEIRAS STRINGS QUE O GERENCIADOR MANDA PARA O BOT
  scanf("PLAYERS %[^\n]\n", players);
  scanf("YOU %s\n", you);
  scanf("HAND %[^\n]\n", hand);
  scanf("TABLE %s\n", table);

  //DEFININDO VARIÁVEIS
  char action1[MAX_LINE];
  char action2[MAX_LINE];
  char complement1[MAX_ACTION];
  char nova_carta[MAX_ACTION];
  char discard[] = "11111";
  char discard_2[] = "111111";
  char complement2[MAX_ACTION];
  int tenho_na_hand = 0;
  int tem = 0;
  int pos = 0;
  int pos_inicial_carta_removida = 0;
  int pos_final_carta_removida = 0;


  //INÍCIO DO LAÇO
  while (1) {
    //LENDO TURNO DE JOGADOR
    scanf("%s %s", action1, complement1);

    //SE FOR MINHA VEZ
    if (strcmp(complement1, you) == 0) {

      //SE A CARTA DA MESA FOR UM C E A ÚLTIMA JOGARA TIVER SIDO UM DISCARD, ENTÃO DEVO PUXAR 4.
      if (table[0] == 'C' && action2[0] == 'D') {

        printf("BUY 4\n");
        //LENDO QUATRO STRINGS PARA AS NOVAS CARTAS
        for (int i = 0; i < 4; i++) {
          scanf("%s", nova_carta);

          //A CADA STRING LIDA, ACRESCENTAR CARTA NA STRING HAND
          for (int i = 0; i < strlen(hand); i++) {
          //PERCORRENDO A STRING HAND, QUANDO ENCONTRAR O FINAL DELA, ADICIONAR NOVA CARTA.
            if (hand[i] == ']') {
              //CASO A NOVA CARTA SEJA DO TIPO DIFERENTE DE 10x (única carta com mais posições de caracteres que as outras.)
              if (nova_carta[0] != '1') {
                hand[i] = nova_carta[0];
                hand[i + 1] = nova_carta[1];
                hand[i + 2] = nova_carta[2];
                hand[i + 3] = nova_carta[3];
                hand[i + 4] = ' ';
                hand[i + 5] = ']';
                hand[i + 6] = '\0';
              //CASO NÃO SEJA DO TIPO 10x
              } else {
                hand[i] = nova_carta[0];
                hand[i + 1] = nova_carta[1];
                hand[i + 2] = nova_carta[2];
                hand[i + 3] = nova_carta[3];
                hand[i + 4] = nova_carta[4];
                hand[i + 5] = ' ';
                hand[i + 6] = ']';
                hand[i + 7] = '\0';

              }

              break;
            }

          }
        }
      //SE A CARTA DA MESA FOR UM V, E A ÚLTIMA JOGADA TIVER SIDO DISCARD, DEVO PUXAR 2.
      } else if (table[0] == 'V' && action2[0] == 'D') {

        printf("BUY 2\n");

        //LENDO 2 STRINGS PARA AS NOVAS CARTAS
        for (int i = 0; i < 2; i++) {
          scanf("%s", nova_carta);

          //PARA CADA NOVA CARTA LIDA, ADICIONAR NA STRING HAND
          for (int i = 0; i < strlen(hand); i++) {
             //PERCORRENDO A STRING HAND, QUANDO ENCONTRAR O FINAL DELA, ADICIONAR NOVA CARTA.
            if (hand[i] == ']') {
              //CASO A NOVA CARTA NÃO SEJA DO TIPO 10x
              if (nova_carta[0] != '1') {
                hand[i] = nova_carta[0];
                hand[i + 1] = nova_carta[1];
                hand[i + 2] = nova_carta[2];
                hand[i + 3] = nova_carta[3];
                hand[i + 4] = ' ';
                hand[i + 5] = ']';
                hand[i + 6] = '\0';
                //CASO A CARTA SEJA DO TIPO 10x
              } else {
                hand[i] = nova_carta[0];
                hand[i + 1] = nova_carta[1];
                hand[i + 2] = nova_carta[2];
                hand[i + 3] = nova_carta[3];
                hand[i + 4] = nova_carta[4];
                hand[i + 5] = ' ';
                hand[i + 6] = ']';
                hand[i + 7] = '\0';

              }

              break;
            }

          }
        }
      //CASO NÃO PUXE NENHUMA CARTA POR CONSEQUÊNCIA DE UMA JOGADA ANTERIOR, É MINHA VEZ DE DESCARTAR.
      } else {
        //COMEÇO ASSUMINDO QUE EU NÃO TENHO A CARTA NECESSÁRIA PARA DESCARTAR COM A VARIÁVEL ABAIXO:
        tenho_na_hand = 0;
        //PERCORRENDO A STRING HAND PARA VERIFICAR SE TENHO A CARTA DA MESA
        for (int i = 0; i < strlen(hand); i++) {
          //VERIFICANDO TODOS OS CARACTERES DA STRING HAND QUE NÃO SEJAM {' ', '[', ']'}
          if (hand[i] != ' ' && hand[i] != '[' && hand[i] != ']') {

            //INICIALMENTE, VOU PROCURAR NA STRIG HAND, ALGUMA CARTA COM O MESMO "NÚMERO" ou "LETRA" , PARA QUE POSSA SER DESCARTADO. CASO NÃO ENCONTRE, PROCURAREI POR NAIPE.

            //=-=-=-=-=-=-=-=-=-=-=-=-PROCURANDO POR NÚMERO OU LETRA -=-=-=-=-=-=-=-=-=-=-=-=-=-
            //CASO O CARACTER hand[i] SEJA IGUAL AO PRIMEIRO CARACTER DA CARTA DA MESA E ESSE CARACTER SEJA '1' (então essa carta é do tipo 10x com um caracter a mais, precisando ser lida de uma forma diferente das outras.)
            if (hand[i] == table[0] && table[0] == '1') {
              //ADICIONANDO A CARTA DO TIPO 10x NA VARIÁVEL discard_2 QUE TEM TAMANHO ESPECÍFICO PARA ESSE TIPO DE CARTA.
              discard_2[0] = hand[i];
              discard_2[1] = hand[i + 1];
              discard_2[2] = hand[i + 2];
              discard_2[3] = hand[i + 3];
              discard_2[4] = hand[i + 4];
              discard_2[5] = '\0';
              //APÓS ADICIONAR A VARIÁVEL A SER DESCARTADA EM discard_2 PRINTAR O DISCARD.
              printf("DISCARD %s\n", discard_2);

              //APÓS PRINTAR O DISCARD, PRECISAMOS REMOVER A CARTA DA STRING HAND.
              pos_inicial_carta_removida = i;
              pos_final_carta_removida = i + 5;
              pos = 0;
              //PERCORRENDO A STRING HAND PARA SOBRESCREVER COM ELA PRÓPRIA, SEM CONTAR COM A CARTA REMOVIDA.
              for (int i = 0; i < strlen(hand); i++) {

                //CASO i SEJA MENOR QUE A POSIÇÃO INICIAL DA CARTA A SER REMOVIDA E i SEJA MAIOR QUE A POSIÇÃO FINAL DA CARTA A SER REMOVIDA, hand[pos] recebe hand[i]
                if (i < pos_inicial_carta_removida || i > pos_final_carta_removida) {
                  hand[pos] = hand[i];
                  pos++;
                }
              }
              //ADICIONANDO \0 AO NOVO FIM DA STRING HAND COM UMA CARTA A MENOS.
              hand[pos] = '\0';

              //COMO EU TINHA A CARTA PARA SER DESCARTADA, TROCAMOS O VALOR DA VARIÁVEL tenho_na_hand para 1
              tenho_na_hand = 1;

              break;

              //CONTINUANDO A PERCORRER A STRING HAND EM BUSCA DE ALGUMA CARTA PARA DESCARTAR.
              //CASO O CARACTER hand[i] SEJA IGUAL O PRIMEIRO CARACTER DA CARTA DA MESA, E A CARTA SEJA DIFERENTE DE 10x, CAIRÁ NESSE else.
            } else if (hand[i] == table[0]) {

              //ADICIONANDO A CARTA DO TIPO (Yx) NA VARIÁVEL discard.
              discard[0] = hand[i];
              discard[1] = hand[i + 1];
              discard[2] = hand[i + 2];
              discard[3] = hand[i + 3];
              discard[4] = '\0';

              //COMO A CARTA É DO TIPO (Yx) ELA PODE SER UM (A) OU UM (C) QUE NECESSITAM DE UM COMPLEMENTO 2.
              if (hand[i] == 'A' || hand[i] == 'C') {

                //NA ESCOLHA DO COMPLEMENTO 2, ESCOLHI O NAIPE DA PRIMEIRA CARTA DA MINHA HAND. ASSIM, ESCOLHI UM NAIPE QUE ESTÁ PRESENTE NA MINHA MÃO.
                printf("DISCARD %s %c%c%c\n", discard, hand[3], hand[4], hand[5]);
              } else {

                //CASO A CARTA A SER DESCARTADA NÃO SEJA DO TIPO (A) OU (C) BASTA DESCARTAR.
                printf("DISCARD %s\n", discard);
              }


              //MESMO PROCEDIMENTO PARA REMOÇÃO DE CARTA DA STRING HAND APÓS DESCARTE.
              pos_inicial_carta_removida = i;
              pos_final_carta_removida = i + 4;
              pos = 0;

              for (int i = 0; i < strlen(hand); i++) {
                if (i < pos_inicial_carta_removida || i > pos_final_carta_removida) {
                  hand[pos] = hand[i];
                  pos++;
                }
              }

              hand[pos] = '\0';

              tenho_na_hand = 1;

              break;

              //CASO NÃO ENCONTRE ALGUMA CARTA COM O MESMO NÚMERO OU LETRA PARA SER DESCARTADA.
              //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-PROCURANDO POR NAIPE-=-=-=-=-=-=-=-=-=--=-=-=-=-=


              //A COMPARAÇÃO ENTRE NAIPES FUNCIONA DA SEGUINTE FORMA:

              // UM NAIPE POSSUE 3 CARACTERES DISTINTOS QUE COMBINADOS FORMAM UMA FIGURA.
              // PARA TESTAR SE UM NAIPE É IGUAL A OUTRO, DEVO COMPARAR CADA CARACTER INDIVIDUALMENTE DA SEGUINTE FORMA:
              // C1    C2    C3       <-- NAIPE QUALQUER
              // ||    ||    ||    
              // C1    C2    C3       <-- NAIPE IDÊNTICO
              // ||    ||    ||
              // C2    C1    C3       <-- NAIPE DIFERENTE


              //SENDO ASSIM, CASO O PRIMEIRO CARACTER DO NAIPE DA HAND SEJA IGUAL AO PRIMEIRO CARACTER DA MESA, DEVO COMPARAR OS OUTROS 2 PARA CONFERIR SE REALMENTE SE TRATA DO MESMO NAIPE.

              //ESSA COMPARAÇÃO ESTÁ SENDO FEITA NO else if ABAIXO.
            } else if (hand[i] == table[1] && hand[i + 1] == table[2] && hand[i + 2] == table[3]) {


              //CASO OS NAIPES SEJAM IGUAIS E A CARTA DESSE NAIPE SEJA UM 10x
              if (hand[i - 2] == '1') {

                discard_2[0] = hand[i - 2];
                discard_2[1] = hand[i - 1];
                discard_2[2] = hand[i];
                discard_2[3] = hand[i + 1];
                discard_2[4] = hand[i + 2];
                discard_2[5] = '\0';
                printf("DISCARD %s\n", discard_2);

                //REMOÇÃO DE CARTA APÓS DESCARTE
                pos_inicial_carta_removida = i - 2;
                pos_final_carta_removida = i + 3;
                pos = 0;

                for (int i = 0; i < strlen(hand); i++) {
                  if (i < pos_inicial_carta_removida || i > pos_final_carta_removida) {
                    hand[pos] = hand[i];
                    pos++;
                  }
                }

                hand[pos] = '\0';

                tenho_na_hand = 1;

                break;

                //CASO NÃO SEJA UM 10x
              } else {

                discard[0] = hand[i - 1];
                discard[1] = hand[i];
                discard[2] = hand[i + 1];
                discard[3] = hand[i + 2];
                discard[4] = '\0';

                if (hand[i - 1] == 'A' || hand[i - 1] == 'C') {
                  printf("DISCARD %s %c%c%c\n", discard, hand[3], hand[4], hand[5]);
                } else {
                  printf("DISCARD %s\n", discard);
                }


                //REMOÇÃO DE CARTA APÓS DESCARTE
                pos_inicial_carta_removida = i - 1;
                pos_final_carta_removida = i + 3;
                pos = 0;

                for (int i = 0; i < strlen(hand); i++) {
                  if (i < pos_inicial_carta_removida || i > pos_final_carta_removida) {
                    hand[pos] = hand[i];
                    pos++;
                  }
                }

                hand[pos] = '\0';

                tenho_na_hand = 1;
                break;
              }
            }

          }

        }
        // ESSE É O FIM DO LAÇO FOR QUE PROCURA UMA CARTA QUE ESTEJA NA STRING HAND PARA DESCARTAR COMPARANDO COM A CARTA DA MESA, ENTÃO, CASO NÃO HAJA UMA CARTA DESSE TIPO, A VARIÁVEL tenho_na_hand VAI PERMANECER 0, ENTRANDO NO if ABAIXO.


        if (tenho_na_hand == 0) {

          //AO FAZER A COMPARAÇÃO ENTRE NAIPES E NÚMEROS PARA DESCARTAR, NÃO OBTIVEMOS SUCESSO EM ENCONTRAR UMA CARTA COMPATÍVEL PARA DESCARTE, NESSE CASO, EXISTEM DUAS CARTAS QUE PODEMOS DESCARTAR INDEPENDENTE DA CARTA DA MESA, QUE SÃO O (C) E O (A), ENTÃO VAMOS PROCURAR NA STRING HAND SE ALGUMA DELAS SE ENCONTRA.


          //COMEÇO SUPONDO QUE NÃO TENHO NENHUMA DESSAS CARTAS NA STRING COM A VARIÁVEL ABAIXO:
          tem = 0;
          //PERCORRENDO A STRING HAND
          for (int i = 0; i < strlen(hand); i++) {
            //CASO ALGUMA DELAS SEJA (A) OU (C)
            if (hand[i] == 'A' || hand[i] == 'C') {
              //CARTA ENCONTRADA, VARIÁVEL tem AGORA É 1.
              tem = 1;
              //GUARDO A POSIÇÃO DA CARTA ENCONTRADA.
              pos = i;
              break;
            }
          }
          if (tem) {
            //CASO A CARTA TENHA SIDO ENCONTRADA, ENTÃO PODEMOS DESCARTAR ELA, PARA NÃO TER QUE PUXAR UMA NOVA CARTA.


            //UTILIZANDO A POSIÇÃO DA CARTA ENCONTRADA, DEFINO A VARIÁVEL discard.
            discard[0] = hand[pos];
            discard[1] = hand[pos + 1];
            discard[2] = hand[pos + 2];
            discard[3] = hand[pos + 3];
            discard[4] = '\0';

            //COMO AS CARTAS (A) ou (C) NECESSITAM DE UM complemento2, ESCOLHO NOVAMENTE UM COMPLEMENTO2 QUE ESTEJA PRESENTE NA MINHA VARIÁVEL HAND.
            printf("DISCARD %s %c%c%c\n", discard, hand[3], hand[4], hand[5]);


            //REMOÇÃO DE CARTA APÓS DESCARTE
            pos_inicial_carta_removida = pos;
            pos_final_carta_removida = pos + 4;
            pos = 0;
            for (int i = 0; i < strlen(hand); i++) {
              if (i < pos_inicial_carta_removida || i > pos_final_carta_removida) {
                hand[pos] = hand[i];
                pos++;

              }
            }
            hand[pos] = '\0';

          } else {
            //EM CASO DA VARIÁTEM tem SER 0, SIGNIFICA QUE NENHUMA CARTA DA STRING HAND É PASSÍVEL DE DESCARTE, ASSIM COMPRANDO 1 NOVA CARTA.

            printf("BUY 1\n");
            scanf(" %s", nova_carta);
            //COMPRANDO NOVA CARTA E ADICIONANDO NA STRING HAND.
            for (int i = 0; i < strlen(hand); i++) {

              if (hand[i] == ']') {
                //CASO A CARTA SEJA DIFERENTE DE 10x
                if (nova_carta[0] != '1') {
                  hand[i] = nova_carta[0];
                  hand[i + 1] = nova_carta[1];
                  hand[i + 2] = nova_carta[2];
                  hand[i + 3] = nova_carta[3];
                  hand[i + 4] = ' ';
                  hand[i + 5] = ']';
                  hand[i + 6] = '\0';
                } else {
                  //CASO A CARTA SEJA DO TIPO 10x
                  hand[i] = nova_carta[0];
                  hand[i + 1] = nova_carta[1];
                  hand[i + 2] = nova_carta[2];
                  hand[i + 3] = nova_carta[3];
                  hand[i + 4] = nova_carta[4];
                  hand[i + 5] = ' ';
                  hand[i + 6] = ']';
                  hand[i + 7] = '\0';
                }

                break;
              }

            }

          }
        }
      }

    } else {
      //-=-=-=-=-=-=-=-=-=-=NÃO É MINHA VEZ-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

      //LENDO AÇÃO DO OUTRO BOT
      scanf("%s %s", action2, complement1);

      if (complement1[0] == 'A') {
        //CASO A CARTA DESCARTADA SEJA A, LER UM COMPLEMENTO 2 E ATUALIZA A TABLE COM O DEVIDO NAIPE
        scanf("%s", complement2);

        complement1[1] = complement2[0];
        complement1[2] = complement2[1];
        complement1[3] = complement2[2];

        strcpy(table, complement1);

      } else if (complement1[0] == 'C') {
      //CASO A CARTA DESCARTADA PELO JOGADOR SEJA UM (C), LER UM COMPLEMENTO 2 E ATUALIZA A TABLE COM O DEVIDO NAIPE
        scanf("%s", complement2);

        complement1[1] = complement2[0];
        complement1[2] = complement2[1];
        complement1[3] = complement2[2];
        strcpy(table, complement1);

      } else {
        //CASO A CARTA DESCARTADA NÃO SEJA (A) ou (C), ATUALIZA A TABLE COM A MESMA CARTA DESCARTADA.
        strcpy(table, complement1);

      }

    }
    //FIM DO LAÇO, RETORNA PARA LER O QUEM JOGA O PRÓXIMNO TURNO.

  }
}