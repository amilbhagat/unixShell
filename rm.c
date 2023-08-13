#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

void remove_file(const char *filename){
    if(remove(filename) == 0){
        printf("file deleted succesfully\n");
    }else{
        perror("ERROR ");
    }
}

void ls_delete(const char *dir){
    struct dirent *d;
    DIR *dh = opendir(dir);

    if(!dh){
        if(errno = ENOENT){
            perror("Directory doesn't exist");
        }else{
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }
    while((d = readdir(dh)) != NULL){
        remove(d->d_name);
    }
}

void remove_file_i(const char *filename){
    printf("rm: remove regular empty file \'%s\'? ",filename);
    char option;
    scanf("%c",&option);
    if(option == 'y'){
        remove(filename);
    };
}

void remove_file_r(const char *directory){
    if(chdir(directory)!=0){
        perror("ERROR ");
    }
    ls_delete(".");
    rmdir(directory);
}

int main(int argc,const char *argv[]){

    if(strcmp(argv[1],"-i")==0){
        remove_file_i(argv[2]);
    }else if(strcmp(argv[1],"-r")==0){
        remove_file_r(argv[2]);
    }else{
        remove_file(argv[1]);
    }
}