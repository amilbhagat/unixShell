#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(const char *filename){
    FILE* fptr;
    fptr = fopen(filename,"r");
    if(fptr == NULL){
        printf("Source file does not exist\n");
        exit(0);
    }
    char ch;
    while((ch = fgetc(fptr))!=EOF){
        printf("%c",ch);
    }
    printf("\n");
    fclose(fptr);
}

void readfilenumber(const char *filename){
    FILE* fptr;
    fptr = fopen(filename,"r");
    if(fptr == NULL){
        printf("Source file does not exist\n");
        exit(0);
    }
    char ch;
    int i=1;
    while((ch = fgetc(fptr))!=EOF){
        if(ch=='\n'){
            printf("%c",ch);
            ch=fgetc(fptr);
            printf("%d)%c",i,ch);
            i++;
        }else{
            if(i ==1){
                printf("1)%c",ch);
                i++;
            }else{
            printf("%c",ch);}
            }
    }
    printf("\n");
    fclose(fptr);
}

void read_and_write(const char *source, const char *dest){
    FILE *fptr1, *fptr2;
    fptr1 = fopen(source,"r");
    if(fptr1 == NULL){
        printf("Source file does not exist\n");
        exit(0);
    }
    fptr2 = fopen(dest,"w");
    if(fptr2 == NULL){
        printf("Destination file does not exist\n");
    }
    char c;
    c = fgetc(fptr1);
    while(c!=EOF){
        fputc(c,fptr2);
        c = fgetc(fptr1);
    }

    fclose(fptr1);
    fclose(fptr2);
}

int main(int argc, const char *argv[]){

    if(argc == 3 && strcmp(argv[2],"\n")==0){
        readfile(argv[1]);
    }else if(argc == 2){
        readfile(argv[1]);
    }else if(argc == 3 && strcmp(argv[1],"-n")==0){
        readfilenumber(argv[2]);
    }else if(argc == 4 && strcmp(argv[1],"-n")==0){
        readfilenumber(argv[2]);
    }else if(argc == 4 && strcmp(argv[2],">")==0){
        read_and_write(argv[1],argv[3]);
    }else if(argc == 5 && strcmp(argv[2],">")==0){
        read_and_write(argv[1],argv[3]);
    }
    return 1;
}