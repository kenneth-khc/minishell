# Minishell

Minishell is a simple implementation of a Bash-like shell.

## Features

wip


## Getting and storing user input

First, the program reads input from STDIN and stores the line read in a t_Line struct.  
Each t_Line struct contains a pointer to the line stored in memory and the length of the line.  
In certain cases, the user enters more than just a single line.  
For example, when the user wants a heredoc, or when the user has an unterminated quote.  

