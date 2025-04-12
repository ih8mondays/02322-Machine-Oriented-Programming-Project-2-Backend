#include <stdio.h>
#include "main.h"

#include <stdlib.h>
#include <string.h>


int main(void) {

    Card* head = generateCards();
    free(head);

    char buf[1024]={0};
    //Card *ptr[7]=

    strcat(buf,"hello world");

    memset(buf,0,sizeof(buf));




    printf("%s\n",buf);
    return 0;

}

Card * generateCards() {
    const Rank rank[] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
    const Suit suit[] = {CLUBS,DIAMONDS,HEARTS,CLUBS};

    const int s = sizeof(suit);

    Card *head = (Card*)malloc(sizeof(Card));
    Card *current = head;

    if (head == NULL) {
        printf("Memory couldn't be allocated");
        return NULL;
    }

    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 13; j++) {
            // Set current
            if (current == NULL) {
                printf("Memory couldn't be allocated");
                free(head);
                return NULL;
            }

            current->suit = suit[i];
            current->rank = rank[j];
            current->hidden = 0;

            if (i == 3 && j == 12) {
                current->next = NULL;
                break;
            }

            current->next = malloc(sizeof(Card));
            current = current->next;
        }
    }
    return head;

}


