#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prompts user, then returns the user's reply
int userInput(){
    // prompt
    printf("Enter the NFL score (Enter 1 to stop): ");
    
    // try to get user input
    int num;
    scanf("%d", &num);

    return num;
}

// prints all combinations of score
void printCombinations(int score){
    for (int td2 = 0; td2 * 8 <= score; td2++) {
        for (int td1 = 0; td1 * 7 + td2 * 8 <= score; td1++) {
            for (int td = 0; td * 6 + td1 * 7 + td2 * 8 <= score; td++) {
                for (int fg = 0; fg * 3 + td * 6 + td1 * 7 + td2 * 8 <= score; fg++) {
                    for (int safety = 0; safety * 2 + fg * 3 + td * 6 + td1 * 7 + td2 * 8 <= score; safety++) {
                        int total = td2 * 8 + td1 * 7 + td * 6 + fg * 3 + safety * 2;
                        if (total == score) {
                            printf("  %d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td2, td1, td, fg, safety);
                        }
                    }
                }
            }
        }
    }
}

int main(){
    // get user input
    int score = userInput();
    
    while(score != 1){
        printf("Possible combinations of scoring plays if a team's score is %d:\n", score);

        // print all combinations
        printCombinations(score);

        // get user input
        score = userInput();
    }

    return 0;
}
