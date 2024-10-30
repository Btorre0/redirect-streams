# redirect-streams

Usage: redir <inp> <cmd> <out>

fork and exec "cmd", redirecting the input and output descriptors as necessary. Assume the values inp and out are filenames, read from and write to them respectively. If they are "-" leave them as stdin/stdout.

Note: cmd is ONE argument. For example "wc -l". You may need to split it into separate words (on " ") before execing it. You will need to properly handle (in code) the case where the command is not an absolute path: find the absolute path for the command!

No need to worry about spaces or quoted strings in its parameters. (It is not required to handle 'echo "foo bar"' as a command. That would/should/could get passed on as "echo", ""foo", "bar"".)

You'll probably love this link: https://www.rozmichelle.com/pipes-forks-dups/Links to an external site. 

## keeping track:
- Oct. 28:
    - Complete:
        - do basics of checking argument
        - set up input and output file
        - from website:
```c 
// if first command in pipeline has input redirection
if (hasInputFile && is1stCommand) { 
  int fdin = open(inputFile, O_RDONLY, 0644);
  dup2(fdin, STDIN_FILENO);
  close(fdin);
}

// if last command in pipeline has output redirection
if (hasOutputFile && isLastCommand) { 
  int fdout = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  dup2(fdout, STDOUT_FILENO);
  close(fdout);
}
```
- Oct. 29:
    - create child proccess (pid == 0)
    - create parent process

    - Make a Makefile
    - check input/output.txt