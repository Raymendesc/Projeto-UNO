#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10




int main() {

char players[MAX_LINE];
char you[MAX_ID_SIZE];
char hand[MAX_LINE];
char table[MAX_LINE];

scanf("PLAYERS %[^\n]\n", players);
scanf("YOU %s\n", you);
scanf("HAND %[^\n]\n", hand);


scanf("TABLE %s\n", table);

char action1[MAX_LINE];
char complement1[MAX_LINE];
char action2[MAX_LINE];
char complement2[MAX_LINE];

int aux=0;

while(1){
 scanf("%s %s", action1, complement1);

if (strcmp(complement1, you)==0){
  printf("jogada");
    
}
else{
  scanf("%s %s", action2, complement2);

}
  
}
/*  
while(1){

scanf("%s %s", action1, complement1); //TURN b1
  
do{

if(aux > 0){
scanf("%s %s", action1, complement1); //TURN b1
}
scanf("%s %s", action2, complement2); //DISCARD 9<3

aux++;
  
}
  while(strcmp(complement1, you));

nossa jogada
*/  
  
}





  
  return 0;
  }





                   