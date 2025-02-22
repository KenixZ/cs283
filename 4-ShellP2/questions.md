1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**: Using fork insteaed of just calling execvp directly allows for new child processes to be made that
	 > allows the shell to continue in separate memory spaces. Calling execvp directly would replace the current working
	 > shell.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If the fork system call fails, it will return -1 due to not being able to create new processes. My
	 > implementation handles this scenario through checking if the variable is less than 0 and giving an error message.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  execvp() finds the command to execute through directory pathnames in the PATH environment.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  The purpose of calling wait() in the parent process after forking is for the child process to finish
	 > and also gives information about the child process state. If there is no wait command, then any terminated child
	 > will be in a zombie state accumulating resources.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  The WEXITSTATUS() is a macro that return the status code when a child process exits. This allows to
	 > see if the child process exited normally or had an error. 

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  My implementation handles quoted arguments through a boolean that tells when
	 > inside quotes and iterates through keeping everything as a single argument.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  Some of the changes in parsing logic were in reference to keeping commands within quotation marks in
	 > the same argument. Some challenges were iterating through the argument and storing inside the cmd struct

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  The purpose of signals in a Linux system is to act like a notification of a process that is going to
	 > happen efficiently. Compared to other forms of interprocess communication (IPC) that use pipes, it does not
	 > exchange data.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGKILL is used to end processes and their signals cannot be caught, blocked or ignored. SIGTERM is a
	 > termination signal that allows programs to catch it and clean up resources. SIGINT stops the processes through the
	 > keyboard.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  SIGSTOP would stop the process but not end it. It cannot be caught, blocked, or ignored because it is
	 > immediate no matter what the state is in.
