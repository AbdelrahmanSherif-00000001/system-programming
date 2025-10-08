#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>

// int main(int argc, char* argv){
//     int val = 0;
//     printf("before fork, val is: %d,\n", val);
//     int fr = fork();
//     if(fr == 0){
//         val = 100;
//         printf("this is the child (pid: %d), and value of val is: %d\n", (int) getpid(), val);
//     }else if(fr > 0){
//         val = 1000;
//         int w = wait(NULL);
//         printf("I am the parent (pid: %d), and the value is: %d\n", (int) getpid(), val);
//     }else{
//         fprintf(stderr, "fork failed \n");
//         exit(1);
//     }
//   return 0;
// }

//                             Q2

// int main(){
//     char* msg = "let's see what will happen \n";
//     char* child_msg = "Here is the child !\n";
//     char* parent_msg = "I am the parent !!\n";
//     int fd = open("file.txt", O_CREAT | O_WRONLY, 0644);

//     ssize_t bytes = write(fd, msg, strlen(msg));
//     int fr = fork();
//     if(fr == 0){
//         printf("Child \n");
//         ssize_t bytes = write(fd, child_msg, strlen(child_msg));
//     }
//     else if(fr > 0){
//         printf("parent \n");
//         ssize_t bytes = write(fd, parent_msg, strlen(parent_msg));
//     }else{
//         fprintf(stderr, "fork failed \n");
//         exit(1);
//     }

//   return 0;
// }


//                            Q3
// first way: 
// int main(int argc, char* argv[])
// {
//     printf("Before fork !! \n");
//     int fo = fork();
//     if(fo == 0){
//         char* arr[3];
//         arr[0] = "echo";
//         arr[1] = "HELLO";
//         arr[2] = NULL;
//         execvp(arr[0], arr);
//     }else if(fo > 0){
//         sleep(1);
//         printf("Guten nacht \n");
//     }else{
//         printf("fork failed");
//     }
//   return 0;
// }

// second way:
// int main()
// {
//     printf("Before fork !! \n");
//     int fo = fork();
//     if(fo == 0){
//         printf("HELLO \n");
//         fflush(stdout); // will print immediately.
//         exit(0);
//     }else if(fo > 0){
//         sleep(1);
//         printf("Good Bye \n");
//     }else{
//         printf("fork failed");
//     }
//   return 0;
// }

//                             Q4


// int main(){
//     printf("hi \n");
//     int fo = fork();
//     if(fo < 0){
//         perror("ERROR !! \n");
//         exit(EXIT_FAILURE);
//     }
//     else if(fo == 0){
//         char* commands[4];
//         commands[0] = "ls";
//         commands[1] = "/mnt/c/users/abdel/documents/books";
//         commands[2] = NULL;
//         execvp(commands[0], commands);
//     }else{
//         int w = wait(NULL);
//         printf("Parent: %d \n", getpid());
//     }
//    return 0;
// }



//                          Q5
// int main(){
//     printf("using wait ()  \n");
//     int fo = fork();
//     if(fo < 0){
//         fprintf(stderr, "fork failed \n");
//         exit(EXIT_FAILURE);
//     }else if(fo == 0){
//         int w = wait(NULL);
//         printf("child with id: %d and wait is is : %d  \n", getpid(), w);
//     }else{
//         printf("parent with id: %d \n ", getpid());
//     }
//   return 0;
// }

//                                 Q6

// int main()
// {
//     int fo = fork();
//     if(fo == 0){
//         printf("Success \n");
//         exit(42);
//     }else if(fo < 0){
//         printf("Failure !! :( \n");
//         exit(EXIT_FAILURE);
//     }else{
//         int status;
//         pid_t wpid = waitpid(fo, &status, 0);
//         if(WIFEXITED(status))           printf("Exited normally :) \n");
//         else if(WIFSIGNALED(status))      printf("signal revceived \n");
//         printf("parent \n");
//     }
//   return 0;
// }


//##### wiatpid() is useful when we to control a specific process using its id.#######



//                                 Q7
// int main(){
//     pid_t fo = fork();
//     if(fo == 0){
//         printf("Child \n");
//         if(close(STDOUT_FILENO)==0){
//             printf("Stdout is closed successfully \n");
//         }
//         printf("let us test this \n");
//     }else if(fo < 0){
//         printf("Fail \n");
//         exit(EXIT_FAILURE);
//     }else
//         printf("Parent \n");
//   return 0;
// }

//after closing stdout_fileno uding close() , anything we try to print will not be printed.


//                                 Q8
int main(){
      int fd[2];// fd[0]: read end             fd[1]: write end.
      pipe(fd);
      
      pid_t fo1 = fork();
      if(fo1 == 0){
         close(fd[0]);
         dup2(fd[1], STDOUT_FILENO); //send all printf() output to the pipe.
         close(fd[1]);

         printf("Hello from child1 \n");
         exit(EXIT_SUCCESS);
      }
      pid_t fo2 = fork();
      if(fo2 == 0){
         close(fd[1]);
         dup2(fd[0], STDIN_FILENO); //makes stdin read from the pipe instead of keyboard.
         close(fd[0]);

         // these previous lines show how linux shells are implemented.

         char buf[100];
         fgets(buf, sizeof(buf), stdin);// structure: pointer to char arr, max # of char includes \0, file obj represent the input stream.
         printf("child 2 recieved: %s", buf);
         exit(EXIT_SUCCESS);
      }
      close(fd[0]);
      close(fd[1]);
      wait(NULL);
      wait(NULL);

   return 0;
}