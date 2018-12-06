#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node{
    char strData[50];
    struct _Node *next;
}Node;

void writeFile2(char fileName[], char ssData[], Node **oLinkedList){
    FILE *output_file;
    output_file=fopen(fileName, "a");
    if (output_file==NULL) {                 //checks whether is file working or not
        printf("Problem opening file\n");
    }
    if (ssData[0]!='\0') {                     //prints the substrings
        fprintf(output_file,"%s\n",ssData);
    }
    while ((*oLinkedList)!=NULL) {
        fprintf(output_file, "%s", (*oLinkedList)->strData);    //prints the linked list iteratively
        *oLinkedList=(*oLinkedList)->next;
    }
    fprintf(output_file, "\n");
    fclose(output_file);   //closes the file
}
int isPalindrome(char str[]){         //checks whether the line in iStrings is palindrome or not
    int i=strlen(str);
    int x=0;
    for (int n=0; n<(i/2); n++) {
        if (str[n]==str[i-1-n]) {
            x++;}}
    
    if (x==strlen(str)/2) {
        return 1;              //is palindrome
    } else return 0;}          //is not palindrome

char *getPalindrome(char str[]){       //implements the isPalindrome() function and returns the string
    int i=isPalindrome(str);
    if (i==1) {
        return "Is_Palindrome";
    } else return "Not_Palindrome";
}

int howManySubstrings(char subStr[], char str[]){     //checks the number of substring occurences
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

void freeLinkedlist(Node *head){     //frees the allocated memory for linked list
    while (head != NULL) {
        Node *temp=head->next;
        free(head);
        head=temp;
    }
}

void printLinkedlist(Node *head){     //prints the linkedlist to console
    if (head != NULL) {
        printf("%s",head->strData);
        printLinkedlist(head->next);
    }
}

void appendNode(Node **oLinkedList, char outputLine[]){       //appends the lists next to each other recuresively
    if ((*oLinkedList)==NULL) {
        *oLinkedList=malloc(sizeof(Node));
        strcpy((*oLinkedList)->strData, outputLine);
        (*oLinkedList)->next=NULL;
    } else {
        appendNode(&((*oLinkedList)->next), outputLine);
        
    }
}

void checkSubstringPalindrome2(char ssData[], char *iStringData[], Node **oLinkedList, int nrIOfileLines){
    char *pal;
    char howMany[10];
    char line[50];
    *oLinkedList=NULL;
    for (int i=0; i<nrIOfileLines; i++) {
        pal=getPalindrome(iStringData[i]);
        strcpy(line, iStringData[i]);
        strcat(line, "\t");
        sprintf(howMany, "%i", howManySubstrings(ssData, iStringData[i])); //the number of substring occurences is written as number in string
        strcat(line, howMany);
        strcat(line, "\t");
        strcat(line, pal);
        strcat(line, "\n");
        appendNode(oLinkedList, line);
    }
}

void readFile2(char filename[], char *ArrayPtr[]){
    FILE *input_file;
    char arr[50];
    input_file=fopen(filename, "r");
    if (input_file==NULL) {
        printf("Problem opening file\n");      //checks whether file is working or not
    }
    int j=0,i=0;
    while (!feof(input_file)) {
        char a=fgetc(input_file);
        if (a=='\n') {
            arr[i]='\0';
            ArrayPtr[j]=malloc(50*sizeof(char));
            strcpy(ArrayPtr[j], arr);
            i=0;
            j++;
            continue;}
        if (a=='\r') {continue;}
        arr[i]=a;
        i++;
    }
    fclose(input_file);
}

int countFileLines(char filename[]){
    FILE *input_file;
    int count=0;
    input_file=fopen(filename, "r");
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
    int lines=countFileLines("iStrings.txt"); //number of lines in iStrings file
    int sublines=countFileLines("subStrings.txt"); //number of lines in subStrings file
    char *twoDimArr[50];
    char *subtwoDimArr[50];
    Node *first=NULL;
    readFile2("iStrings.txt",twoDimArr); //reads the iStrings file
    readFile2("subStrings.txt",subtwoDimArr); //reads the subStrings file
    for (int i=0; i<sublines; i++) {
        checkSubstringPalindrome2(subtwoDimArr[i], twoDimArr, &first, lines); //checks the line for Palindrome and substring occurence
        Node *new=first;
        writeFile2("oStrings.txt", subtwoDimArr[i], &new); //writes the subStrings and contents of linked lists as lines to output file
        printLinkedlist(first); //in order to print the linked list
        printf("\n"); // in order to divide different linked lists when printing to the console
        freeLinkedlist(first); //frees the allocated memory for linked list
    }
    return 0;
}
