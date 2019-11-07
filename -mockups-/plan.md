# Graph 2

```
// Controls: 
//  + Move cursor
//  A Select item
//  B Backspace if possible, other exit
//  B(hold) exit

// Goals:
// * Functional RPN calculator that can store a function as a collection of tokens.
// * Shunting-yard algorithm???
```

* main priority: have an rpn calculator that draws a graph.
* next priority: have a way of typing a function (in rpn form) that will then be graphed
* next priority: implement shunting yard algorithm that takes string and outputs token array

# Costs

The Arduboy has only 2.5kb of RAM. There will have to be some cost-cutting measures in place to keep this reasonable.

* ~~252 (63floats) bytes - Graph space~~
* ~~63 bytes - Graph space~~
* JUST USE THE SCREEN BUFFER YOU really cool intelligence haver - Graph space
* 64 (16floats) bytes - function space

OOPS THAT's ALREADY 1/8TH OF THE RAM

* 64 bytes - function string space

# How, though?

You write a function in the "function string space", it gets run through the Shunting-Yard algorithm. That gets put into the "function space", which is then calculated 63 times to form the graph.

```
[2 3]		constants

[>0 1 +]	tokens
 |> [>2 3]
[2<]		stack

[0 >1 +]
 |> [2 >3]
[2 3<]

[0 1 >+]
* 2+3=5 *
[5<]

[5]
Output stack has length 1! Good!
```

```
2x + 5
2*x + 5

2x*5+

[2 5]		constants
8			variable

[>0 x * 1 +]		tokens
 |> [>2 5]
[2]			stack

[0 x * 1 +]
 |> 8
[2 8]
```
