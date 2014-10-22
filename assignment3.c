#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char **buildAnsArray();

int baseConversion(int number, int originalbase, int newbase);

int baseConversiontoten(int number, int originalbase, int newbase);

int LENGTH;

int main(){
    int counter;
    char **answers = buildAnsArray();
    int temp = baseConversion(233, 4, 8);
    printf("%d", temp);
    return 0;
}
char **buildAnsArray(){
    int length, counter;
    FILE *data;
    data = fopen("data.txt", "r");
    fscanf(data, "%d", &LENGTH);
    char **answerarray = malloc(sizeof(char*)* LENGTH);
    for (counter = 0; counter < LENGTH; counter++){
        answerarray[counter] = malloc(sizeof(char)* 25);
    }
    for (counter = 0; counter < LENGTH; counter++){
        fscanf(data, "%s", answerarray[counter]);
    }
    return answerarray;
}

int baseConversion(int number, int originalbase, int newbase){
    int temp;
    if (originalbase != 10 && newbase == 10){
        temp = baseConversiontoten(number, originalbase, newbase);
        return temp;
    }
    else if (originalbase != 10 && newbase != 10){
        temp = baseConversiontoten(number, originalbase, newbase);
        return baseConversion(temp, 10, newbase);
    }
    else{
        if (number == 0){
            return number;
        }
        else{
        return (number % newbase) + 10*baseConversion(number / newbase, originalbase, newbase);
        }
    }
}

int baseConversiontoten(int number, int originalbase, int newbase){
    int temp[25];
    int counter = 0, sum = 0;
    while(number != 0){
        temp[counter] = number%10;
        counter++;
        number = number/10;
    }
    int i;
    for(i = 0; i < counter; i++){
        sum += temp[i] * pow(originalbase, i);
    }
    return sum;
}
