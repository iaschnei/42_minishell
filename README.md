# 42_minishell
A minimalist 'shell' in C, made with [@Acsts](https://github.com/Acsts)

The goal was to recreate a basic shell-like program that could take input from the user and output according to the commands passed in.

It has a command history, handles redirections, pipes and environment variables.

It also has the following builtins: 
- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

# Usage:
```console
~ make
~ ./minishell
>minishell [command(s) separated by pipes]
>minishell [command(s) separated by pipes]
>minishell ...
>minishell [exit]
```
