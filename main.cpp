//
//  main.cpp
//  305Lab5
//
//  Created by Qumber Zaidi on 5/1/22.
//

#include<iostream>
#include<unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
    
int pipe1_fd[2];
int pipe2_fd[2];
int pipe1Status;
int pipe2Status;
char pipe1Message[30] = "(Pipe1 MESSAGE): YOO!";
char pipe2Message[30] = "(Pipe2 MESSAGE): WHATS UP!";
char readPipeMessage[30];
int parentSum = 0;
int childSum = 0;
int partialSumTotal = 0;
    
pipe1Status = pipe(pipe1_fd);
if (pipe1Status == -1) {
    cout<<"Cannot create pipe 1" << endl;
return 1;
}
    
pipe2Status = pipe(pipe2_fd);
if (pipe2Status == -1) {
    cout<<"Cannot create pipe 2" << endl;
return 1;
}
    
int pid = fork();
if (pid != 0) {
close(pipe1_fd[0]);
close(pipe2_fd[1]);
cout<<"(Parent) Proccess: Writing Message to (CHILD) pipe 1:" << pipe1Message << endl;
write(pipe1_fd[1], pipe1Message, sizeof(pipe1Message));
read(pipe2_fd[0], readPipeMessage, sizeof(readPipeMessage));
cout<<"(Parent) Proccess: Reading Message from (CHILD) from pipe 2:"<< readPipeMessage << endl;
  
    read(pipe2_fd[0], &parentSum, sizeof(parentSum));
    read(pipe2_fd[0], &childSum, sizeof(childSum));
    partialSumTotal = parentSum + childSum;
    cout <<"\nThe Partial Sum of the parent computing 1 through 5 is: " << parentSum << endl;
    cout <<"The Partial Sum of the parent computing 6 through 10 is: " << childSum << endl;
    cout << "Total Sum of the Partial Sums is: " << partialSumTotal << endl;
    close(pipe1_fd[1]);
    close(pipe2_fd[0]);
}
    
if (pid == 0) {
close(pipe1_fd[1]);
close(pipe2_fd[0]);
read(pipe1_fd[0], readPipeMessage, sizeof(readPipeMessage));
cout<<"(Child) Proccess: Reading Message from (PARENT) pipe 1:"<<readPipeMessage << endl;
cout<<"(Child) Proccess: Writing Message to (PARENT) pipe 2:"<<pipe2Message << endl;
write(pipe2_fd[1], pipe2Message, sizeof(pipe2Message));
    
int partialNum = 5;
int partialNum2 = 10;

   for(int i = 1; i <= partialNum; i++){
    parentSum+=i;
    }
    
    for(int i = 6; i <= partialNum2; i++){
    childSum +=i;
    }
    
    write(pipe2_fd[1], &parentSum, sizeof(parentSum));
    write(pipe2_fd[1], &childSum, sizeof(childSum));
    close(pipe1_fd[0]);
    close(pipe2_fd[1]);
    }

return 0;
}

