# permanent

## What is it?
permanent is a program for counting [the permanent](https://en.wikipedia.org/wiki/Permanent "Permanent") of a matrix using Ryser's formula with **O(2^n`*`n^2)** time complexity. Not only numbers but also polynomials in many variables can be the elements of the matrix.

### What do we mean by a polynomial?
By a polynomial we mean an arithmetical expression, which doesn't contain spaces written with the use of `+`,`-`,`*` and `^` signs 
with operators which are polynomials made of variables and brackets(the second term in operator `^` must be a positive integer
and the first term mustn't be an integer). By a variable we mean any sequence of symbols which doesn't contain arithmeic signs
but contains at least one symbol different from `0..9` and `.`. Any variable as well as any number 
is considered a polynomial. The multiplication sign can't be skipped: for example, `1.5x` is an incorrect construction because the program
will take it as a single variable. The right way to write it is  `1.5*x`.

## How to use it?
The program reads from the standart input stream and returns the result into the output stream. 
Firstly, you should write one number `n`, the size of the matrix the permanent of which is counted(if `n`>14, 
the program will work too much time). Then `n` strings containing polynomials separated by spaces should follow.
The output consists of one polynomial - the permanent of the matrix. For example:
~~~
\\stdin
3
(semen+svyat)^2 x 1
(semen-svyat)^2 0 1
1*ivan_kazmenko 1 0
\\stdout
2*svyat^2+2*semen^2+x*ivan_kazmenko
~~~

## And what is it needed for?
I don't know :)
