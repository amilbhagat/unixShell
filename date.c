#include<stdio.h>
#include<string.h>
#include<time.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

void current_date_and_time(){
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    ptr=localtime(&t);
    printf("%s",asctime(ptr));
}

void current_date_and_time_utc(){
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    ptr=gmtime(&t);
    printf("%s",asctime(ptr));
}

int dayofweek(int d, int m, int y)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y+y/4-y/100+y/400+t[m-1]+d)%7;
}

void string_to_time(char *line){
    char argument[256];
    int k;
    for(int i = 0;i<strlen(line);i++){
        if(line[i]=='\"'){
            k=i;
            break;
        }
    }
    int g=0;
    for(k;k<strlen(line);k++){
        if(line[k]!='\"'){
            argument[g]=line[k];
            g++;
        }
    }
    // printf("%s\n",argument);
    if(strchr(argument,'/')!=NULL){
        struct tm* ptr;
        time_t t;
        t=time(NULL);
        ptr=localtime(&t);
        int count = 0;
        char date1[1];
        int flag = 0;
        char date2[2];
        char month[2];
        char year[4];
        for(int i =0;i<strlen(argument);i++){
            if(argument[i]=='/'){
                if(count == 1){
                    date1[0] = argument[i-1];
                }else if(count == 2){
                    date2[0] = argument[i-2];
                    date2[1] = argument[i-1];
                    flag = 1;
                }else if(count>3){
                    month[0] = argument[i-2];
                    month[1] = argument[i-1];
                    year[0] = argument[i+1];
                    year[1] = argument[i+2];
                    year[2] = argument[i+3];
                    year[3] = argument[i+4];
                }
            }
            count++;
        }
        int date;
        if(flag == 0){
            date = date1[0] - 48;
        }else{
            date = ((date2[0] -48)* 10) + (date2[1]-48);
        }
        int monthnumber;
        monthnumber = ((month[0] -48)* 10) + (month[1]-48);
        int yearnumber;
        yearnumber = ((year[0] -48)*1000) + ((year[1]-48)*100) + ((year[2]-48)*10) + (year[3]-48);
        ptr->tm_hour = 0;
        ptr->tm_sec = 0;
        ptr->tm_min = 0;
        ptr->tm_mon = monthnumber-1;
        ptr->tm_mday = date;
        ptr ->tm_year =yearnumber-1900;
        int day = dayofweek(date,monthnumber,yearnumber);
        ptr ->tm_wday = day;
        printf("%s",asctime(ptr));
    }
}

void yesterday(){
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t-(86400);
    printf("%s",ctime(&t));
}

void tomorrow(){
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t+(86400);
    printf("%s",ctime(&t));
}

void n_years_ago(char ch){
    int n;
    n = ch-48;
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t-(n*365*86400);
    printf("%s",ctime(&t));
}

void n_secs_ago(char ch){
    int n;
    n = ch-48;
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t-(n);
    printf("%s",ctime(&t));
}

void n_months_ago(char ch){
    int n;
    n = ch-48;
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t-(n*30*86400);
    printf("%s",ctime(&t));
}

void n_days_ago(char ch){
    int n;
    n = ch-48;
    struct tm* ptr;
    time_t t;
    t=time(NULL);
    t = t-(n*86400);
    printf("%s",ctime(&t));
}

int main(int argc, const char *argv[]){
    if(argc == 2 && strcmp(argv[1],"\n")==0){
        current_date_and_time();
    }else if(argc == 1){
        current_date_and_time();
    }else if(argc == 2 && strcmp(argv[1],"-u")==0){
        current_date_and_time_utc();
    }else if(argc == 3 && strcmp(argv[1],"-u")==0){
        current_date_and_time_utc();
    }else if(argc == 4 && strcmp(argv[1],"-d")==0 && strchr(argv[2],'/')!=NULL){
        string_to_time(argv[2]);
    }else if(argc == 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[2],"yesterday")==0){
        yesterday();
    }else if(argc == 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[2],"tomorrow")==0){
        tomorrow();
    }else if(argc > 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"years")==0 && strcmp(argv[4],"ago\"")==0){
        n_years_ago(argv[2][1]);
    }else if(argc > 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"seconds")==0 && strcmp(argv[4],"ago\"")==0){
        n_secs_ago(argv[2][1]);
    }else if(argc > 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"months")==0 && strcmp(argv[4],"ago\"")==0){
        n_months_ago(argv[2][1]);
    }else if(argc > 4 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"days")==0 && strcmp(argv[4],"ago\"")==0){
        n_days_ago(argv[2][1]);
    }else if(argc == 3 && strcmp(argv[1],"-d")==0 && strchr(argv[2],'/')!=NULL){
        string_to_time(argv[2]);
    }else if(argc == 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[2],"yesterday")==0){
        yesterday();
    }else if(argc == 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[2],"tomorrow")==0){
        tomorrow();
    }else if(argc > 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"years")==0 && strcmp(argv[4],"ago")==0){
        n_years_ago(argv[2][0]);
    }else if(argc > 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"seconds")==0 && strcmp(argv[4],"ago")==0){
        n_secs_ago(argv[2][0]);
    }else if(argc > 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"months")==0 && strcmp(argv[4],"ago")==0){
        n_months_ago(argv[2][0]);
    }else if(argc > 3 && strcmp(argv[1],"-d")==0 && strcmp(argv[3],"days")==0 && strcmp(argv[4],"ago")==0){
        n_days_ago(argv[2][0]);
    }
}