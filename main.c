#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <pthread.h>
#define MAX_LIMIT 256

void *systemcalling(char *args){
    system(args);
}

int thread_creation(char *command){
    pthread_t thread;
    pthread_create(&thread,NULL,systemcalling,command);
    pthread_join(thread,NULL);
    return 1;
}

int cd(char **args);
int pwd(char **args);
int echo(char **args);

int launch_child_process1(char *filename ,char *arg1){
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
    }else if(rc == 0){
        int stat = execl(filename,filename,arg1,NULL);
    }else{
        int rc_wait = wait(NULL);
    }
    return 1;
}

int launch_child_process2(char *filename ,char *arg1,char *arg2, char *arg3){
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
    }else if(rc == 0){
        int stat = execl(filename,filename,arg1,arg2,arg3,NULL);
    }else{
        int rc_wait = wait(NULL);
    }
    return 1;
}

int launch_child_process_execv(char *filename, char **args){
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
    }else if(rc == 0){
        int stat = execv(filename,args);
    }else{
        int rc_wait = wait(NULL);
    }
    return 1;
}

char **parse(char *line){
    int bufsize = 64 , position = 0;
    char **args =  malloc(bufsize * sizeof(char*));
    char *piece;

    piece = strtok(line," ");
    while(piece != NULL){
        args[position] = piece;
        position++;

        if(position >= bufsize){
            bufsize = bufsize + 64;
            args = realloc(args, bufsize * sizeof(char*));
        }

        piece = strtok(NULL," ");
    }
    args[position] = NULL;
    return args;
}

void main_loop(char *path_ls,char *path_cat,char *path_date,char *path_rm,char *path_mkdir, char * directory_path){
    char *internal_commands[] = {"cd" , "echo" , "pwd"};
    char *external_commands[] = {"ls" , "cat" , "date" , "rm" , "mkdir"};
    char line[MAX_LIMIT];
    char **args;
    int status;

    do{
        printf("> ");
        fgets(line, MAX_LIMIT, stdin);
        char path_copy[500];
        strcpy(path_copy,directory_path);
        strcat(path_copy,"/");
        strcat(path_copy,line);
        if(strstr(path_copy,"&t")!=NULL){
            char pathcopycopy[500];
            for(int i = 0;i<strlen(path_copy);i++){
                if(path_copy[i]=='&'){
                    pathcopycopy[i]='\0';
                    break;
                }
                pathcopycopy[i]=path_copy[i];
            }
            status = thread_creation(pathcopycopy);
        }else{
        args = parse(line);
        if(strcmp(args[0],internal_commands[0])==0){
            status = cd(args);
        }else if(strcmp(args[0],internal_commands[1])==0){
            status = echo(args);
        }else if(strcmp(args[0],internal_commands[2])==0){
            status = pwd(args);
        }else if(strcmp(args[0],"ls")==0){
            status = launch_child_process_execv(path_ls,args);
        }else if(strcmp(args[0],external_commands[1])==0){
            status = launch_child_process_execv(path_cat,args);
        }else if(strcmp(args[0],external_commands[2])==0){
            status = launch_child_process_execv(path_date,args);
        }else if(strcmp(args[0],external_commands[3])==0){
            status = launch_child_process_execv(path_rm,args);
        }else if(strcmp(args[0],external_commands[4])==0){
            status = launch_child_process_execv(path_mkdir,args);
        }}
    }while(status);

}

int cd(char **args){
    if(strcmp(args[1] , "~") == 0){
        chdir("/home/amil");
    }else{
        if(chdir(args[1]) != 0){
            perror("lsh");
        }
    }
    return 1;
}

int pwd(char **args){
    char path[MAX_LIMIT];
    if(args[0] == NULL){
        fprintf(stderr, "expected argument to \"pwd\"\n");
    }else{
        if(getcwd(path, sizeof(path)) == NULL){
            perror("lsh");
        }else{
            printf("%s\n",path);
        }
    }
    return 1;
}

void slice_str(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

int echo(char **args){
    int k =0;
    while(args[k]!=NULL){k++;};
    if(strcmp(args[1],"-e")==0){
        for(int m = 2;m<k;m++){
            if(args[m][0] == '\\' && args[m][1] == 'b'){
                const size_t len = strlen(args[m]);
                char buffer[len+1];
                slice_str(args[m],buffer,2,len);
                printf("%s",buffer);
            }else if(args[m][0] == '\\' && args[m][1] == 't'){
                const size_t len = strlen(args[m]);
                char buffer1[len+1];
                slice_str(args[m],buffer1,2,len);
                printf("    %s",buffer1);
            }else{
                printf(" %s",args[m]);
            }
        }
    }else if(strcmp(args[1],"\n")==0){
        printf("ERROR : please give arguments");
    }
    else{
        for(int i = 1;i<k;i++){
        if(i!=k-1){
            printf("%s ",args[i]);
        }else if(i=k-1){
            printf("%s",args[i]);
        }
        }
    }
    return 1;
}

int main(){
    char directory_path[500];
    getcwd(directory_path,sizeof(directory_path));
    char *path_ls;
    path_ls = realpath("ls",NULL);
    char *path_cat;
    path_cat = realpath("cat",NULL);
    char *path_date;
    path_date = realpath("date",NULL);
    char *path_rm;
    path_rm = realpath("rm",NULL);
    char *path_mkdir;
    path_mkdir = realpath("mkdir",NULL);
    main_loop(path_ls,path_cat,path_date,path_rm,path_mkdir,directory_path);

    return 0;
}