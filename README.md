# aaa-lang
turing complete language that only accepts three characters

you read that right.  

i hate having to push more than three letters on my keyboard.

# installation
just compile the C file  
that's literally it  
if you have gcc, the command to build it is
```console
gcc aaa.c -o aaa
```
wow! so complex  
  
you can run a program file (literally just a file with text in it) with ./aaa using 
```console
./aaa <path-to-file>
```

# usage
aaa-lang only accepts A, ? and ! as characters, and has 9 commands.
each command is two characters long, however BEWARE OF THIS FACT: i made this to be terrible, so... the program counter only goes up by one after each command! hehehehehe  
this means that `a?!` is two commands: `a?` and `?!`. keep this in mind when writing code.  
  
### commands
all very nicely grouped
```
*a: pointer value manipulation 
?a: subtract one from pointer value
!a: add one to pointer value
aa: output pointer value

*?: pointer index manipulation
a?: subtract one from pointer index
!?: add one to pointer index
??: get input and put it at pointer index

*!: program counter jumping
a!: if pointer value is 0, jump to after next ?!
?!: if pointer value is not 0, jump to after previous a!
!!: if pointer value is not 0, jump to after next ?!
```
oh and you can totally put other characters in a program, the executer ignores them entirely

for those who think my C is bad:
```diff
i don't rightly care
```
