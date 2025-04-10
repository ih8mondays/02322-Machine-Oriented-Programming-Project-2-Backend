#include <stdio.h>
#include "main.h"

#include <stdlib.h>
#include <string.h>


int main(void) {

    const Rank rank[] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    const Suit suit[] = {CLUBS,DIAMONDS,HEARTS,CLUBS};

    Card *deck = (Card*)malloc(sizeof(Card)*52);

    if (deck == NULL) {
        printf("Memory couldn't be allocated");
    }

    for (int i = 0 ; i < sizeof(suit) ; i++) {
        for (int j = 0 ; j < sizeof(rank) ; j++) {

            deck[(i*13 + j)*sizeof(Card)] = Card {suit[i],rank[j],1,NULL};







        }
    }

    char buf[1024]={0};

    //Card *ptr[7]=

    strcat(buf,"hello world");



    memset(buf,0,sizeof(buf));




    printf("%s\n",buf);
    return 0;



}
