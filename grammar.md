# Grammar

```
complete_command	: command

command			: list
			| subshell

list			: pipe_sequence and_or

subshell		: '(' list ')' pipe
			| '(' list ')' and_or

pipe_sequence		: simple_command pipe

pipe			: '|' list
			| ε  

and_or			: '&&' command
			| '||' command
			| ε

simple_command		: command_prefix command_word command_suffix
			| command_prefix command_word
			| command_prefix

command_prefix		: io_redirect command_prefix
			| ASSIGNMENT_WORD command_prefix
			| ε  

command_suffix		: io_redirect command_suffix
			| WORD command_suffix
			| ε  

io_redirect		: IO_NUMBER io_file
			| IO_NUMBER io_here
			| io_file
			| io_here
	
io_file			: '<' filename
			| '>' filename
			| '>>' filename

io_here			: '<<' here_end

command_name		: WORD

command_word		: WORD

filename		: WORD

here_end		: WORD
```

