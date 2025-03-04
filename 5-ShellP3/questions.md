1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation ensures that all child processes complete by using waitpid() in a loop thus the parent process has to
wait for all child processes to complete. If I forget to call waitpid(), any terminated child will become a zombie
process and accumulate resources over time.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

It is necessary to close unused pipe ends after calling dup2() due to the process of how it reads from the pipe and
could wait endlessly for the data. If there are too many pipes left open, too many resources will be accumulated and cause errors elsewhere.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

It is important for cd to be implemented as a built-in command rather than an external command that would run in a child
process. This would create the challenge for when the child process terminates and the cd command not being called in
the parent shell. 

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

Currently I use a fixed size array using ARG_MAX to store a fixed number of piped commands and this wastes a lot of
memory. In order to modify my implementation, a 2d array would be able to support an arbitrary number of pipe commands. Some trade-offs I would need to consider are memory leaks.
