#include<unistd.h>
#include<iostream>
#include<string>
using namespace std;

/*
1. The parent and child process create 2 unique pipes using pipe ( ) system call.
2. The parent process forks (use fork () system call to spawn the child process)
3) Both child and parent create 2 File descriptors, one for each pipe()
DONE

-Parent sends Message to child process
a) The writer (parent) closes its read end of the first pipe, and the reader (child) closes its write end of the first pipe.    
b) The parent and child communicate by using write ( ) and read ( ) calls respectively.
c) Parent sends a message to child,  Child will print the message from the Parent(specifying that it is the child printing the parents message)
DONE

-Child sends Message to Parent process
a) The writer (child) closes its read end of the second pipe, and the reader (Parent) closes its write end of the second pipe.    
b) The parent and child communicate by using write ( ) and read ( ) calls respectively.
c) Child sends a message to Parent, Parent will print the message from the  child(specifying that it is the child printing the parents message)
4) Each process closes its active pipe descriptor when it’s finishes with it.

Computing the sums(Extra Credit 5 points towards grade)
Note: Once a pipe is used it cannot be reused, you only need to send data in one direction.
a)	Parent computes the partial sum of 1 through 5
b)	child computes the partial sum of 6 through 10
c)	Child sends its result to the Parent using a pipe(use the same technique you used in previous parts)
d)	 Parent sums the Partial sums together 
e)	Parent prints the total sum.
Deliverables: Submit on blackboard your complete c++ code, and screen shots of your code running, showing the results. 


int fd[2];
pipe(fd);
fd[0]; //-> for using read end
fd[1]; //-> for using write end

*/

int main()
{

    int pipe1[2],pipe2[2]; // file descriptor declaration.
    pipe(pipe1);
    pipe(pipe2);
    string mess = "Message";
    string m2 = "Second Message";
    
    pid_t pid = fork(); // creats parent and child process
  
    if (pid < 0) //  checks for failure 
    {
        cout << "Fork Failed";
    }

    else if (pid > 0) // partent process
    {
        close(pipe1[0]); // close read
        write(pipe1[1], &mess, sizeof(mess));



    }
    else // child process
    {
       close(pipe1[1]); // cloose weite

        read(pipe1[0], &mess, sizeof(mess));
	    cout << "Child recieved this: " << mess << endl;

        close(pipe1[0]);

    }


    /*
    -Child sends Message to Parent process
    a) The writer (child) closes its read end of the second pipe, and the reader (Parent) closes its write end of the second pipe.    
    b) The parent and child communicate by using write ( ) and read ( ) calls respectively.
    c) Child sends a message to Parent, Parent will print the message from the  child(specifying that it is the child printing the parents message)
    4) Each process closes its active pipe descriptor when it’s finishes with it.
*/
    if (pid == 0) //cjild
    {        
        close(pipe2[0]); //close read
        write(pipe2[1], &m2, sizeof(m2));

    }

    else // parent
    {
        close(pipe2[1]); //close write
        read(pipe2[0], &m2, sizeof(m2));

        cout <<  "Parent recieved this: "  << m2 << endl;

        close(pipe2[0]);


    }




  
    return 0;
    
}