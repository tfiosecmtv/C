#include <stdio.h>
#include <string.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines){
    FILE *output_file;
    output_file=fopen(fileName, "a");
    if (output_file==NULL) {
        printf("Problem opening file\n");
    }
    fprintf(output_file,"%s\n",ssData);
    for (int i=0; i<nrIOfileLines; i++) {
        fprintf(output_file,"%s\n",oStringData[i]);
        if (i==(nrIOfileLines-1)) {
            fprintf(output_file,"\n");
        }
    }
    fclose(output_file);
}

int isPalindrome(char str[]){
    int i=strlen(str);
    int x=0;
    for (int n=0; n<(i/2); n++) {
        if (str[n]==str[i-1-n]) {
            x++;}}
    
    if (x==strlen(str)/2) {
        return 1;
    } else return 0;
    
}

char *getPalindrome(char str[]) {
    int i=isPalindrome(str);
    if (i==1) {
        return "Is_Palindrome";
    } else return "Not_Palindrome";
}

int howManySubstrings(char subStr[], char str[]){
    int i=0;
    int occurences=0;
    for(int n=0;str[n]!='\0';n++){
        if(subStr[i]==str[n]){
            i++;
            if(i==strlen(subStr)){
                i=0;
                occurences++;
            }
        }
    }
    return occurences;
}

void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines){
    char *pal;
    char howMany[10];
    for (int i=0; i<nrIOfileLines; i++) {
        pal=getPalindrome(iStringData[i]);
        strcpy(oStringData[i], iStringData[i]);
        strcat(oStringData[i], "\t");
        sprintf(howMany, "%i", howManySubstrings(subStr, iStringData[i])); //the number of substring occurences is written as number in string
        strcat(oStringData[i], howMany);
        strcat(oStringData[i], "\t");
        strcat(oStringData[i], pal);
    }
}

void readFile(char filename[], char twoDimArr[][50]){
    FILE *input_file;
    input_file=fopen(filename, "r");
    if (input_file==NULL) {
        printf("Problem opening file\n");
    }
    int j=0,i=0;
    while (!feof(input_file)) {
        char a=fgetc(input_file);
        if (a=='\n') {twoDimArr[i][j]='\0';i++;j=0;continue;}
        if (a=='\r') {continue;}
        twoDimArr[i][j]=a;
        j++;
    }
    fclose(input_file);
}

int countFileLines(char filename[]){
    FILE *input_file;
    int count=0;
    input_file=fopen(filename, "r");
    if (input_file==NULL) {
        printf("Problem opening file\n");
    }
    do {
        char a=getc(input_file);
        if (a=='\n') {
            count++;
        }
    } while (!feof(input_file));
    fclose(input_file);
    return count;
}

int main() {
    int lines=countFileLines("iStrings.txt");
    int sublines=countFileLines("subStrings.txt");
    char twoDimArr[lines][50];
    char subtwoDimArr[sublines][50];
    char output[lines][50];
    readFile("iStrings.txt",twoDimArr);
    readFile("subStrings.txt",subtwoDimArr);
    for (int i=0; i<sublines; i++) {
        checkSubstringPalindrome(subtwoDimArr[i], twoDimArr, output, lines);
        writeFile("oStrings.txt", subtwoDimArr[i], output, lines);
    }
    return 0;
}
