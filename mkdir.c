#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


void make_directory(const char *dirname){
    if(mkdir(dirname,0777)==0){
        printf("Directory created successfully\n");
    }else if(mkdir(dirname,0777)==-1){
        perror("ERROR ");
        exit(1);
    }
}

void make_directory_p(const char *path){
    char argument[256];
    for(int i = 0;i<strlen(path);i++){
        argument[i]=path[i];
    }
    argument[strlen(path)]='\0';

    char *token = strtok(argument,"/");
    char returning_directory[256];
    getcwd(returning_directory,sizeof(returning_directory));

    while(token!=NULL){
        printf(" %s\n",token);
        mkdir(token,0777);
        chdir(token);
        token =strtok(NULL,"/");
    }

    chdir(returning_directory);
}

void make_directory_v(const char *dirnames[],int size){
    for(int i = 2;i<size;i++){
        if(mkdir(dirnames[i],0777)==0){
            printf("mkdir: created directory '%s'\n",dirnames[i]);
        }else{
            printf("mkdir: cannot create directory '%s'\n",dirnames[i]);
        }
    }
}

int main(int argc, const char* argv[]){
    
    if(argc == 2){
        make_directory(argv[1]);
    }else if(argc>2){
        if(strcmp(argv[1],"-v")==0){
            make_directory_v(argv,argc);
        }else if(strcmp(argv[1],"-p")==0){
            make_directory_p(argv[2]);
        }
    }else{
        make_directory(argv[1]);
    }
}