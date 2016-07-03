//
//  main.m
//  mywordsearcher
//
//  Created by thecult on 8/6/08.
//  Copyright __MyCompanyName__ 2008. All rights reserved.
//

// KODU IYICE OPTIMIZE ETMEYI UNUTMA SIZE_T SIZEOF .H LAR PLATFORMT INDEPENDET- GOOD PROGRAMING PRACTICE-MORE FLEXIBLE MAXWORDSIZE-Typing controls etc. Disclaimer. Welcome message...
// 4 lüler 3 lüler güzel genere olmuyor 5 liler de eksikler var-STACK de tekrar ediyor
//#import <Cocoa/Cocoa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINWORDSIZE 4
#define MAXWORDSIZE 7

int find_matching_words(void *letters,void *dict,int dwidth,int dsize);
int get_6_letter_words_from_dict_file(char file_name[20],void *word_array,int size);

char dictwords[500000][20]={"0"};
int globcnt_dict=0;
char stack[200][20]={"0"};
int ch=0;


int wordsearcher()
{
    int i=0;
    char letters[7]="ABCDEF";
    int numOfWordsFound=0;
    char dictfilename[50];
    system("cls");
    printf("Please enter dictionary file name: (ex:sowpods.txt)\n");
    scanf("%s",dictfilename);
    printf("Indexing the dictionary, Please wait...\n");


    globcnt_dict=get_6_letter_words_from_dict_file(dictfilename,(void *)dictwords,7); // Buraya char[20]yerine char * koysak nolur bakmamiz lazim

    while (1) {
        AGAIN:
        printf("\n\nPlease enter letters to search matching words in dictionary:\n");
        scanf("%s",&letters);
        for(i=0;i<strlen(letters);++i)
        if(!isalpha((letters[i]=toupper(letters[i]))))
        goto AGAIN;
        printf("\n\n");
        numOfWordsFound=find_matching_words(letters,dictwords,20,globcnt_dict);
        printf("%d Words have been found ... \nListing words found...\n\n",numOfWordsFound);
        while (--numOfWordsFound) {
            if (!(numOfWordsFound % 5))
                printf("\n");
            printf("%-6s ",(char *)stack+numOfWordsFound*20);
        }
    }



    return 0;
}


int get_6_letter_words_from_dict_file(char file_name[20],void *word_array,int size) {
    //Reads entry times string and returns the number of successfully read strings
    FILE *f;
    int i=0;
    char str[50]="0";

    if ((f=fopen(file_name,"r"))==NULL) {
        printf("Cannot open file ...\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(f,"%s",str)!= EOF) {
        if ((strlen(str)<7)&&(strlen(str)>2))
            memcpy(&dictwords[i++][0],str,7);
    }
    fclose(f);
    return i;
}

int find_matching_words(void *letters,void *dict,int dwidth,int dsize) {
    char tletters[7];
    char dicword[7];
    int cnt=0;
    int temp,i,k,scnt=0;

    memcpy(tletters,letters,7);

    while (dsize--) {
        memcpy(dicword,dict+dsize*dwidth,7);
        cnt=0;
        for (i=cnt;i<strlen(dicword);++i) {
            for (k=cnt;k<7;++k) {
                if (dicword[i]==tletters[k]) {
                    temp=tletters[k],tletters[k]=tletters[cnt],tletters[cnt]=temp;
                    temp=dicword[i],dicword[i]=dicword[cnt],dicword[cnt]=temp;
                    cnt++;
                    break;
                }
            }
        }
        if (cnt==strlen(dicword))
            memcpy(&stack[scnt++][0],dict+dsize*dwidth,7);

    }
    return scnt;
}
