#include<stdio.h>
#include<unistd.h> //for using create system call / close / read / write
#include<fcntl.h>  //for using the flags 
#include<dirent.h> // DIR / entry
#include<string.h>
#include<stdlib.h>
// #include<errno.h>

#define buf_size 1024

char buffer [buf_size];

int main(int argc, char *argv[])
{ 
    DIR *dir;
    struct dirent *entry;
    
    char path[256];
    printf("Enter the directory you want to work in: ");
    scanf("%s", path);

    // Change to the user-specified directory
    if (chdir(path) != 0) {
        perror("Failed to change directory");
        return 1;
    }

    printf("Changed to directory: %s\n", path);

    int choice;
    char filename[64];
    printf("what do you want to do \n");
    printf("#1 New file.\n");
    printf("##2 Open a file.\n");
    printf("###3 Edit a file.\n");
    printf("####4 Delete a file.\n");
    printf("####### Enter your choice : ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            dir = opendir("."); // open current directory 
            printf("\n############ Enter file name : ");
            scanf("%s",filename);
            while ((entry = readdir(dir)) != NULL) {
                if(strcmp(entry->d_name, filename) == 0){
                        printf("File already exists!");
                        return 1;
                }
            }
            int fd = creat(filename, 0644);
            if  (fd == -1){
                perror("Error:  ");
                return 1;
            }
            close(fd);
            closedir(dir);
            printf("File %s created successfully :) \n", filename);
            break;

        case 2:
            printf("\n############ Enter file name : ");
            scanf("%s", filename);
            dir = opendir("."); 
            if (dir == NULL) {
                perror("Error opening folder");
                return 1;
            }
        // Iterate over directory files, Read and print file content
            while ((entry = readdir(dir)) != NULL) {
                if(strcmp(entry->d_name, filename) == 0){
                    int fd2 = open(filename , O_RDONLY);
                    if (fd2 == -1){
                        perror("error : ");
                        return 1;
                    }
                    size_t n = read(fd2, buffer, buf_size);
                    if(n<0){
                        perror("error");
                        close(fd2);
                        closedir(dir);
                        return 1;
                    }
                    buffer[n] = '\0';
                    printf("|\n --> %s:\n\n%s ", filename, buffer);
                    close(fd2);
                }
            }
            closedir(dir);
            break;
       
            case 3:
                printf("\nRight now, you can only append, will work to enable full edit in future :)!");
                dir = opendir(".");
                printf("\n--> Enter file name : ");
                scanf("%s", filename);
                int fd3 = open(filename, O_WRONLY |O_CREAT |O_APPEND,0644);
                if(fd3 == -1){
                    perror("ERROR: ");
                    return 1;
                }
                printf("\n ####### Enter content to be append : ");
                getchar();
                fgets(buffer, buf_size, stdin);
                write(fd3, buffer, strlen(buffer));
                close(fd3);
                closedir(dir);
                printf("Content appended successfully :) !!");
                break;
       
        case 4:
            dir = opendir(".");
            printf("\n############ Enter file name : ");
            scanf("%s", filename);
            while ((entry = readdir(dir)) != NULL) {
                if(strcmp(entry->d_name, filename) == 0){
                    //use unlink to delete file
                    if (unlink(filename) == 0) {
                        printf("File deleted successfully :) \n");
                    } else {
                        perror("Failed to delete the file :( !!");
                    }
                }
            }
            closedir(dir);
            break;
        default:
            printf("Invalid choice");
            break;
    }

    return 0; 
}