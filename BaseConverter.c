#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char **buildAnsArray();

char* baseConversion(int number, int originalbase, int newbase);

int baseConversiontoten(int number, int originalbase, int newbase);

int LENGTH;
FILE *data;

char hexConverter(int number);

int power(int number, int exponent);

int findAnswer(char** answers, char* query, int high, int low);

char* pow2Converter(int number, int originalbase, int newbase);

int main(){
    int counter = 0;
    char **answers = buildAnsArray();
    while (counter < LENGTH){
        char* tempanswer;
        tempanswer = malloc(sizeof(char)* 25);
        int number, originalbase, newbase, answer;
        fscanf(data, "%d %d %d", &number, &originalbase, &newbase);
        tempanswer = baseConversion(number, originalbase, newbase);
        answer = findAnswer(answers, tempanswer, LENGTH-1, 0);
        printf("%d\n", answer);
        counter++;
    }
    return 0;
}

char **buildAnsArray(){
    int counter;
    data = fopen("data.txt", "r");
    fscanf(data, "%d", &LENGTH);
    char** answerarray = malloc(sizeof(char*)* LENGTH); //Mallocing the array size
    for (counter = 0; counter < LENGTH; counter++){
        answerarray[counter] = malloc(sizeof(char)* 25);
    }
    for (counter = 0; counter < LENGTH; counter++){
        fscanf(data, "%s", answerarray[counter]);
    }
    return answerarray;
}

int findAnswer(char** answers, char* query, int high, int low){
    if (high < low){
        return -1;
    }
    else{
        int midpoint = (high + low)/2;
        int currentval = atoi(answers[midpoint]);
        int key = atoi(query);
        if (currentval < key){
            return findAnswer(answers, query, midpoint-1, low);
        }
        else if(currentval > key){
            return findAnswer(answers, query, high, midpoint + 1);
        }
        else{
            return midpoint;
        }
    }
}

char* baseConversion(int number, int originalbase, int newbase){
    int temp;
    char* returned;
    returned = malloc(sizeof(char)* 25);
    if (originalbase != 10 && newbase == 10){
        temp = baseConversiontoten(number, originalbase, newbase); //If number is going to base ten, just convert and it's done.
        sprintf(returned, "%d", temp);
        return returned;
    }
    else if (originalbase == 2){
        returned = pow2Converter(number, originalbase, newbase);
        return returned;
    }
    else if (originalbase != 10 && newbase != 10){
        temp = baseConversiontoten(number, originalbase, newbase); //Otherwise, convert it to base 10 and recursively call the function.
        returned = baseConversion(temp, 10, newbase);
        return returned;
    }
    else{
        if ((number / newbase) == 0){ //Base case
            int tempnum = number%newbase;
            if (newbase > 10 && (tempnum >= 10)){
                sprintf(returned, "%c", hexConverter(number%newbase));
                return returned;
            }
            else{
                sprintf(returned, "%d", number%newbase);
                return returned;
            }
        }
        else{
            int tempnum = number % newbase;
            char tempstr[100];
            if (newbase > 10 && tempnum >= 10){
                sprintf(tempstr, "%c", hexConverter(number%newbase));
            }
            else{
                sprintf(tempstr, "%d", tempnum);
            }
            //fflush(stdout);
            returned = strcat(baseConversion(number / newbase, originalbase, newbase), tempstr);
            return returned;
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
        sum += temp[i] * power(originalbase, i);
    }
    return sum;
}

char hexConverter(int number){
    if (number == 10){
        return 'A';
    }
    else if (number == 11){
        return 'B';
    }
    else if (number == 12){
        return 'C';
    }
    else if (number == 13){
        return 'D';
    }
    else if (number == 14){
        return 'E';
    }
    else if (number == 15){
        return 'F';
    }
    else{
        return number;
    }

}

int power(int number, int exponent){
    int product = 1;
    int counter;
    for (counter = 0; counter < exponent; counter++){
        product *= number;
    }
    return product;
}

char* pow2Converter(int number, int originalbase, int newbase){
    int temp;
    char* returned;
    returned = malloc(sizeof(char)* 25);
    if (originalbase != 10 && newbase != 10){
        temp = baseConversiontoten(number, originalbase, newbase);
        returned = baseConversion(temp, 10, newbase);
        return returned;
    }
    else{
        if ((number / newbase) == 0){
            int tempnum = number%newbase;
            if (newbase > 10 && (tempnum >= 10)){
                sprintf(returned, "%c", hexConverter(number%newbase));
                return returned;
            }
            else{
                sprintf(returned, "%d", number%newbase);
                return returned;
            }
        }
        else{
            int tempnum = number % newbase;
            char tempstr[100];
            if (newbase > 10 && tempnum >= 10){
                sprintf(tempstr, "%c", hexConverter(number%newbase));
            }
            else{
                sprintf(tempstr, "%d", tempnum);
            }
            //fflush(stdout);
            returned = strcat(baseConversion(number / newbase, originalbase, newbase), tempstr);
            return returned;
        }
    }
}
