# SlidingPuzzle

[Sliding Puzzle](https://en.wikipedia.org/wiki/15_puzzle) Solver.

## Motivation

Wanted to work on a small side project to get better at programming in C++.

## Usage

```bash
$ solver [OPTIONS] < examples/8puzzle_1.txt
```

The initial state of the puzzle is read from `stdin`. It expects a square amount of numbers greater than 4. That is: 9, 16, 25, etc... It will also read in 0 as representing the empty space.

### Options

#### Help

`-h --help`

Show help message and usage information.

#### Verbose

`-v --verbose`

Show each step taken to reach the solution, rather than just a list of tiles to move.

#### Statistics

`-s --stats`

Show how many nodes were expanded in the A* search and how many steps need to be taken to reach the goal state.
