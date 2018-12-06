/*
 ============================================================================
 Name        : ProgAssignment1.c
 Author      : Aidana Imangozhina
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    char command;
    int mysterious_number, i, guessed_number, new_range = 9999;
    float start_button_pressed=0,average_of_guesses,p=0;
    printf("WELCOME to the guessing game!\n");
    printf("MENU: (s) to start a game, (n) to set a new range, or (q) to quit:\n");
    do {
            command=getchar();
            if(command=='\n'){printf("MENU: (s) to start a game, (n) to set a new range, or (q) to quit:\n");}
            if (command=='s') {
                start_button_pressed++;
                printf("Start!\n");
                srand(time(NULL));
                mysterious_number=rand()%(new_range-1)+1;
                printf("The secret number is BETWEEN 0 AND %i. Guess:\n", new_range);
                for (i=1; ; i++) {
                    scanf("%i", &guessed_number);
                    if (guessed_number>mysterious_number) {printf("Too HIGH! Guess:\n");}
                    else if (guessed_number<mysterious_number) {printf("Too LOW! Guess:\n");}
                    else if (guessed_number==mysterious_number) {
                        p+=i;
                        if (i==1) {printf("CORRECT! You TOOK %i guess\n", i);break;}
                        else {printf("CORRECT! You TOOK %i guesses\n", i);}break;}
                }
            }
            else if (command=='n') {
                printf("Enter a new MAXIMUM:\n");
                scanf("%i", &new_range);
                    srand(time(NULL));
                    mysterious_number=rand()%(new_range-1)+1;
                }
        else if (command!='\n' && command!='q') {printf("UNRECOGNIZED command!\n");}} while (command!='q');
    average_of_guesses = p/start_button_pressed;
    printf("Thank you for playing! Your guess count AVERAGE %.1f\n", average_of_guesses);
    return 0;
}
