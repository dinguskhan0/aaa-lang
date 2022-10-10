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
if you want, you can get extra-cool debugging info by appending a d to the end of your command like so:
```console
./aaa <path-to-file> d
```
you'll get cool output that looks something like this
```console
[DEBUG MODE]
executing '!A'
   mem[0] = 1
executing 'A!'
   mem[0] != 0
executing '!A'
   mem[0] = 2
executing 'A?'
   mem[0] = 2
executing '??'
```

# usage
aaa-lang only accepts A, ? and ! as characters, and has 9 commands.
each command is two characters long, however BEWARE OF THIS FACT: i made this to be terrible, so... the program counter only goes up by one after each command! hehehehehe  
this means that `A?!` is two commands: `A?` and `?!`. keep this in mind when writing code.  
  
some things to note:  
the language allows manipulation of two main things `memory index` and `value at memory index`. this is all you get in the way of memory manipulation  
  
there are also three program flow thingies that jump around based on whether the `value at memory index` is `0` or `not 0`  
  
have fun!
### commands
all very nicely grouped
```
*A: memory value manipulation 
?A: subtract one from value at memory index
!A: add one to memory at memory index
AA: output value at memory index

*?: memory index manipulation
A?: subtract one from memory index
!?: add one to memory index
??: get input and put it at memory index (not entirely sure but i think this puts additional characters after the first one)

*!: program counter jumping
A!: if value at memory index is 0, jump to after matching ?! (this way you can have A! and ?! in between)
?!: if value at memory index is not 0, jump to after matching A!
!!: if value at memory index is greater than 0, jump to value at memmory index (don't go too far ¯\_( ͡° ͜ʖ ͡°)_/¯)
```
oh and you can totally put other characters in a program, the executer ignores them entirely

for those who think my C is bad:
```diff
- i don't rightly care
```

# some programs written in AAA
#### some kind of weird input loop
```!A!A??!``` asks for input and then *asks for input again and again and again and again and again...*

# will i ever update this?
probably... no

i don't see a reason nor do i care that much

if there's an error then *maybe*
