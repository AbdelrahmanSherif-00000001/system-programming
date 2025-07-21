#include<dirent.h>
#include<stdio.h>

int main()
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if(dir == NULL){
        perror("ERROR");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL){
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        continue;


        printf("%s\n", entry->d_name);
    }
    return 0;
}