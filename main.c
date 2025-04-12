#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int main(void) {

    Card *head = generateCards();
    if (head == NULL) {
        free(head);
        printf("Error in generateCards\n");
        return -1;
    }

    //

    //char buf[1024]={0};
    //Card *ptr[7]=
    //strcat(buf,"hello world");
    //memset(buf,0,sizeof(buf));
    //printf("%s\n",buf);

    return 0;

}

Card * generateCards() {
    const Suit suit[] = {CLUBS,DIAMONDS,HEARTS,CLUBS};
    const Rank rank[] = {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};

    const int suitSize = sizeof(suit)/sizeof(suit[0]);
    const int rankSize = sizeof(rank)/sizeof(rank[0]);

    Card *head = (Card*)malloc(sizeof(Card));
    Card *current = head;

    if (head == NULL) {
        printf("Memory couldn't be allocated");
        return NULL;
    }

    for (int i = 0 ; i < suitSize ; i++) {
        for (int j = 0 ; j < rankSize; j++) {

            if (current == NULL) {
                printf("Memory couldn't be allocated");
                free(head);
                return NULL;
            }

            // Assign current card values
            current->suit = suit[i];
            current->rank = rank[j];
            current->hidden = 0;

            // Last card won't allocate more memory
            if (i == suitSize - 1 && j == rankSize - 1) {
                current->next = NULL;
                return head;
            }

            // Set up next card
            current->next = malloc(sizeof(Card));
            current = current->next;
        }
    }

    return head;
}


