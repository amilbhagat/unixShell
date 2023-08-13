#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

void ls(const char *dir){
    struct dirent *d;
    DIR *dh = opendir(dir);

    if(!dh){
        perror("ERROR ");
        exit(1);
    }
    while((d = readdir(dh)) != NULL){
        if(d->d_name[0]!='.'){
        printf("%s      ", d->d_name);
        }
    }
    printf("\n");
}

void ls_a(const char *dir){
    struct dirent *d;
    DIR *dh = opendir(dir);

    if(!dh){
        perror("ERROR ");
        exit(1);
    }
    while((d = readdir(dh)) != NULL){
        printf("%s      ", d->d_name);
    }
    printf("\n");
}

void ls_l(const char *dir){
    struct dirent *d;
    DIR *dh = opendir(dir);

    if(!dh){
        perror("ERROR ");
        exit(1);
    }
    while((d = readdir(dh)) != NULL){
        printf("%d      %d      %s   \n", d->d_type,d->d_ino,d->d_name);
    }
    printf("\n");
}

int main(int argc, const char *argv[]){
    int flag=0;
    if(argc == 2 && strcmp(argv[1],"\n")==0){
        ls(".");
        flag = 1;
    }else if(argc == 2 && strcmp(argv[1],"-a\n")==0){
        ls_a(".");
        flag = 1;
    }else if(argc == 2 && strcmp(argv[1],"-a")==0){
        ls_a(".");
        flag = 1;
    }else if(argc == 2 && strcmp(argv[1],"-l\n")==0){
        ls_l(".");
        flag = 1;
    }else if(argc == 2 && strcmp(argv[1],"-l")==0){
        ls_l(".");
        flag = 1;
    }else if(argc == 2 && strcmp(argv[1],"..\n")==0){
        ls("..");
        flag =1;
    }else if(argc == 2 && strcmp(argv[1],"..")==0){
        ls("..");
        flag = 1;
    }else if(argc == 3 && argv[2]=='\n'){
        ls(argv[1]);
        flag = 1;
    }else if(argc == 1){
        ls(".");
        flag = 1;
    }else if(argc == 3){
        ls(argv[1]);
    }else if(argc == 2 && strcmp(argv[1],"&t")==0){
        ls(".");
    }
}