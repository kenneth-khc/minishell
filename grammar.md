# Grammar

```bnf
command			: complete_command

complete_command	: pipe_sequence and_or

pipe_sequence		: simple_command pipes

pipes			: PIPE pipe_sequence 
			| ε  

and_or			: AND_AND pipe_sequence and_or
			| OR_OR pipe_sequence and_or
			| ε

simple_command		: command_prefix command_word command_suffix
			| command_prefix command_word
			| command_prefix
			| command_name command_suffix
			| command_name

command_prefix		: io_redirect command_prefix
			| ASSIGNMENT_WORD command_prefix
			| ε  

command_suffix		: io_redirect command_suffix
			| WORD command_suffix
			| ε  

io_redirect		: io_file
			| io_here
	
io_file			: LESS filename
			| GREAT filename
			| GREAT_GREAT filename

io_here			: LESS_LESS here_end

command_name		: WORD

command_word		: WORD

filename		: WORD

here_end		: WORD
```

