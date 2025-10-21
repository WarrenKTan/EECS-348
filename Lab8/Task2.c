#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// prompts user, then returns the user's reply
float userFloat(char *prompt){
    // prompt
    printf("%s", prompt);
    
    // try to get user input
    float num;
    scanf(" %f", &num);

    // skip newlines after input
    while (getchar() != '\n');

    return num;
}

// prompts user, then returns the user's reply
char userChar(char *prompt){
    // prompt
    printf("%s", prompt);
    
    // try to get user input
    char c;
    scanf(" %c", &c);

    // skip newlines after input
    while (getchar() != '\n');

    return c;
}

int main(){
    // get user inputs
    float startTemp = userFloat("Enter the temperature value: ");
    char startScale = userChar("Enter the original scale (C, F, or K): ");
    char endScale = userChar("Enter the scale to convert to (C, F, or K): ");

    float kTemp = 0;
    float cTemp = 0;
    float fTemp = 0;

    // convert scales
    switch(startScale){
        case 'k':
        case 'K':
            kTemp = startTemp;
            cTemp = startTemp - 273.15;
            fTemp = ((startTemp - 273.15) * 9 / 5) + 32;
            break;
        case 'c':
        case 'C':
            kTemp = startTemp + 273.15;
            cTemp = startTemp;
            fTemp = (startTemp * 9 / 5) + 32;
            break;
        case 'f':
        case 'F':
            kTemp = ((startTemp - 32) * 5 / 9) + 273.15;
            cTemp = (startTemp - 32) * 5 / 9;
            fTemp = startTemp;
            break;
    }

    // print output
    printf("Converted temperature: ");
    switch(endScale){
        case 'k':
        case 'K':
            printf("%.2f K\n", kTemp);
            break;
        case 'c':
        case 'C':
            printf("%.2f C\n", cTemp);
            break;
        case 'f':
        case 'F':
            printf("%.2f F\n", fTemp);
            break;
    }

    // print temperature category
    char category[32];
    char advisory[128];
    if(cTemp < 0){
        strcpy(category, "Freezing");
        strcpy(advisory, "Stay indoors");
    }else if(cTemp < 10){
        strcpy(category, "Cold");
        strcpy(advisory, "Wear a jacket");
    }else if(cTemp < 25){
        strcpy(category, "Comfortable");
        strcpy(advisory, "Go outside");
    }else if(cTemp < 35){
        strcpy(category, "Hot");
        strcpy(advisory, "Drink lots of water");
    }else{
        strcpy(category, "Extreme Heat");
        strcpy(advisory, "Stay indoors");
    }
    
    printf("Temperature category: %s\n", category);
    printf("Weather advisory: %s!\n", advisory);
    // Enter the temperature value: 30
    // Enter the original scale (C, F, or K): C
    // Enter the scale to convert to (C, F, or K): F
    // Converted temperature: 86.00 F
    // Temperature category: Hot
    // Weather advisory: Drink lots of water!
    return 0;
}