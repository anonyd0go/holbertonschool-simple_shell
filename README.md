# Simple Shell
This will be the readme file for the simple shell

### Introduction
This repository is the [Holberton School](https://www.holbertonschool.com/) first trimester Final Project. The school project consisted in writing a shell like sh (Bourne Shell) by Stephen Bourne  , in **C**.

The goal in this project was to make us understand how a shell works. Specifically: what is the *environment*(`env` vs `environ`), the difference between *functions* and *system calls* (and difference between *wrappers* and *sys calls*), how to create *processes* (using `execve`, `fork`, `wait`, ...)

## Usage
To run this program, clone this repo
`git clone https://github.com/anonyd0go/holbertonschool-simple_shell`

Compile with
`gcc 4.8.4 -Wall -Werror -Wextra -pedantic *.c -o hsh`

To use this shell, run the program in your terminal:    
`User@user:~$ ./hsh`  
It wil then display a simple prompt and wait for commands.  
`(흫_흫):$ `

The commands handled by the shell are builtins and normal programs.
### Built-ins
The Current list of built-ins is:
* env
Displays all environment variables
* getenv NAME
Displays the desired environment variable
* exit
Exits the shell. (At the moment it does not handle arguments)
* `Ctrl+D`
Can also be used to exit the simple shell program

### Commands
Handles most if not all commands inside the PATH variable
in the current environment.

It supports single word commands, full path commands, and command flags

## Examples
**Example 1**
```
Username@your-regular-prompt:~$ ./hsh
(흫_흫):$ pwd
/home/username/
(흫_흫):$ exit
username@your-prompt:~$
```
**Example 2**
```
username@your-prompt:~$ ./hsh
(흫_흫):$ /bin/ls -l /tmp 
-rw------- 1 username username    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 username username    0 Dec  5 12:09 unity_support_test.0
(흫_흫):$ exit
username@your-prompt:~$
```
**Example 3**
```
username@your-prompt:~$ ./hsh
(흫_흫):$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
(흫_흫):$ getenv PATH
/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
(흫_흫):$ exit
username@your-prompt:~$ 

```

At the moment the shell does not support history.

## Authors
* Diego Diaz Florez [anonyd0go](https://github.com/anonyd0go)