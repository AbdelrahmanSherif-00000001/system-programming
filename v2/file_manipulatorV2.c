#include<stdio.h>
#include<unistd.h> //for using create system call / close / read / write
#include<fcntl.h>  //for using the flags 
#include<dirent.h> // DIR / entry
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
// #include<errno.h>

#define buf_size 4055

char buffer [buf_size];

int main(int argc, char *argv[])
{ 
    struct dirent *entry;
    char path[256];
    char again = 'Y';

    do{
    printf("Want to change DIR ??.... (Y/N)  ");  
    char change = getchar();
    if(change == 'Y' || change == 'y'){
        printf("Enter the directory you want to work in: ");
        scanf("%255s", path);

        // Change to the user-specified directory
        if (chdir(path) != 0) {
            perror("Failed to change directory!!");
            return 1;
        }else
            printf("Changed to directory: %s\n", path);
    }
    int choice;
    char filename[64] = {0};
    printf("what do you want to do \n");
    printf("#1. New file.\n");
    printf("##2. Open a file.\n");
    printf("###3. Append to a file.\n");
    printf("####4. Edit a file.\n");
    printf("#####5. Delete a file.\n");
    printf("\n####### Enter your choice : ");
    scanf("%d", &choice);
    while(getchar() != '\n');
    switch(choice){
        case 1:
        {
            DIR *dir;
            dir = opendir("."); // open current directory
            if(dir == NULL){
                perror("Can not open the folder !!\n");
                break;
            } 

            printf("\n############ Enter file name: ");
            scanf("%63s", filename);
            int exist = 0;
            while ((entry = readdir(dir)) != NULL) {
                if(strcmp(entry->d_name, filename) == 0){
                    printf("File already exists! \n");
                    exist = 1;
                    break;
                }
            }
            closedir(dir);//we should close the folder "directory" once we done with it following RAII principle.
           
            if(exist)
                break;

            int fd = creat(filename, 0644);
            if (fd == -1){
                perror("Error while creating the file: \n");
                break;
            }

            close(fd);
            // closedir(dir);
            printf("File %s created successfully :) \n", filename);
            break;
        }

        case 2:
        {
            printf("\n############ Enter file name : ");
            scanf("%63s", filename);
            int fd2 = open(filename , O_RDONLY);
            if (fd2 == -1){
                perror("error : ");
                break;
            }
            ssize_t n = read(fd2, buffer, buf_size);
            if(n<0){
                perror("error");
                close(fd2);
                break;
            }
            buffer[n] = '\0';
            printf("|%s:\n ----> %s ", filename, buffer);
            close(fd2);
            break;
        }
       
            case 3:
                //dir = opendir(".");
                printf("\n--> Enter file name : ");
                scanf("%63s", filename);
                while(getchar() != '\n');
                int fd3 = open(filename, O_WRONLY |O_CREAT |O_APPEND,0644);
                if (fd3 == -1){
                    perror("ERROR, opening the file: ");
                    break;
                }
                printf("\n ####### Enter content to be append : ");
                // getchar();
                fgets(buffer, buf_size, stdin);
                write(fd3, buffer, strlen(buffer));
                close(fd3);
                //closedir(dir);
                printf("Content appended successfully :) !!\n");
                break;

        case 4:
        {
            int fd;
            char newtext[buf_size] = {0};
            char line[1024] = {0};
            printf("\nEnter file name: ");
            scanf("%63s", filename);
            while(getchar() != '\n');
            fd = open(filename, O_RDONLY | O_CREAT , 0644);
            if(fd==-1){
                perror("Error openning the file !!\n");
                break;
            }
            ssize_t bytes = read(fd, buffer, buf_size);
            if (bytes == -1)
            {
                perror("Error reading the file !!\n");
                close(fd);
                break;
            }
            else if(bytes == 0) printf("No content !!\n");
            else{
                buffer[bytes] = '\0';
                printf("|%s's current content:\n ---->%s", filename, buffer);
            }
            close(fd);

            fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1){
                perror("Error while opening the file \n");
                break;
            }

            printf("To edit, copy the above content, edit it, it will be saved :)\n");
            printf("Type a new text (to finish press /):    \n\n");
           
            while(1){

                if(fgets(line, sizeof(line), stdin)== NULL){
                    printf("Input ended ! \n");
                    break;
                }
                line[strcspn(line, "\n")] = 0;

                if(strcmp(line, "/") == 0){
                    printf("New text has been saved :) \n");
                    break;
                }

                if(strlen(newtext) + strlen(line) + 2 < buf_size){
                    strcat(newtext, line);
                    strcat(newtext, "\n");
                }else{
                    printf("File Too large !!! \n");
                    break;
                }
            }
            if(strlen(newtext) == 0){
                printf("No content added !!, edit not saved \n");
                close(fd);
                break;
            }
            ssize_t wr = write(fd, newtext, strlen(newtext));
            if(wr == -1)
                perror("Failed to save the edit : \n");
            else
                printf("Edit has been saved to %s :) \n", filename);

            close(fd);
            break;
        }
        case 5:
        {
            //dir = opendir(".");
            printf("\n############ Enter file name : ");
            scanf("%63s", filename);
            if (unlink(filename) == 0) {
                printf("File has been deleted successfully :) \n");
            } else {
                perror("Failed to delete the file :( !! \n");
            }
            break;
        default:
            printf("Invalid choice");
            break;
        }
    }
   printf("\n Want another operation (Y/N)  ");
   scanf(" %c", &again);
  }while(again == 'Y' || again == 'y');

    printf("\n\t\t\tI am sure you enjoy this, (if anyone had tried it already)");
    return 0; 
}