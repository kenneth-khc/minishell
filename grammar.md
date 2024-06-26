# Grammar

```bnf
command		: and_or

and_or		: pipe_sequence
		| and_or AND_AND pipe_sequence
		| and_or OR_OR pipe_sequence

pipe_sequence	: simple_command
		| pipe-sequence PIPE simple_command

simple_command	: command_prefix command_word command_suffix
		| command_prefix command_word
		| command_prefix
		| command_name command_suffix
		| command_name

command_prefix	: io_redirect
		| command_prefix io_redirect
		| ASSIGNMENT_WORD
		| command_prefix ASSIGNMENT_WORD

command_suffix	: io_redirect
		| command_suffix io_redirect
		| WORD
		| command_suffix WORD

io_redirect	: io_file
		| io_here
	
io_file		: LESS filename
		| GREAT filename
		| GREAT_GREAT filename

io_here		: LESS_LESS here_end

command_name	: WORD

command_word	: WORD

filename	: WORD

here_end	: WORD
```

