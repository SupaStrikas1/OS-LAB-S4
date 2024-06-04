#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

void main(){
    DIR *dir;
    struct dirent *entry;

    dir=opendir(".");
    if(dir==NULL){
        printf("Error");
        exit(EXIT_FAILURE);
    }
    while((entry=readdir(dir))!=NULL){
        printf("%s\n",entry->d_name);
    }
    closedir(dir);
}