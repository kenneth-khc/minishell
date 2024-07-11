# Grammar

```
command			: complete_command
			| subshell

subshell		: '(' complete_command ')'

complete_command	: pipe_sequence and_or

pipe_sequence		: simple_command pipe

pipe			: '|' pipe_sequence
			| ε  

and_or			: '&&' pipe_sequence and_or
			| '||' pipe_sequence and_or
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

