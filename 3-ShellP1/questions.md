1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**: fgets() is a good choice due to how it reads characters line by line. It also stops when it
	 > reads a certain number of characters that is provided by the user, and handles EOF.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  Using malloc() was needed to allocate memory due to how the shell handled memory usage, we also don't
	 > know the size of the cmd_line and we have to account for that. Malloc allows for this and can be free'd
	 > accordingly.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  This is necessary because commands would not be able to be recognized due to the spaces. Some issues
	 > that might arrise if we didn't trim spaces is that spaces could be used in the commands or arguments and may cause
	 > errors.

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  The first example would be redirecting the output to a different location like a file, a challenge
	 > would be due to the permissions that the file have. The second example would be redirecting the input from a file
	 > to another file, a challenge would be the permissions of both files. The third example would be appending the
	 > output to a file, a challenge would be making sure that the file exists.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  The key differences between redirection and piping is that redirection can output to a file or take
	 > it as an input and piping takes the output of a command for the input of a different command.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  It is important to keep these separate in a shell to be able to tell a program's output from error
	 > messages.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  For commands that fail, returning certain numbers would allow for easy indications along with print
	 > messages. STDOUT AND STDERR can be merged together through a single command through merge redirection >&.
