<p align="center">
  <img src="https://github.com/iomonad/corewar/raw/master/resources/.github/banner.gif"/><br>
<br>
<br>
</p>

# Corewar [![HitCount](http://hits.dwyl.io/iomonad/corewar.svg)](http://hits.dwyl.io/iomonad/corewar) [![Build Status](https://travis-ci.org/iomonad/corewar.svg?branch=master)](https://travis-ci.org/iomonad/corewar)

Subject in [french](https://cdn.intra.42.fr/pdf/pdf/30/corewar.fr.pdf) or in [english](https://cdn.intra.42.fr/pdf/pdf/963/corewar.en.pdf)

##### TL;DR
Corewar is a ~~nerdish~~ game where two players confront themselves in a virtual arena.
The players are programs written in assembly with a specific set of instructions.
You have to create an assembler, a virtual machine, and a player according to the rules of Corewar.

## ASM

The assembler has to:
- Parse a file written from a given set of instructions.
- Convert that file into bytecode according to op.c and op.h
- Save the output into a .cor file

### How it works

Magic

### TODO

- Stuff
- Other stuff

## Virtual Machine

The virtual machine has to:
- Parse players written in bytecode generated from the assembler, according to op.c and op.h
- Setup the environnement for the game (initialize the players, check valid bytecode instructions, etc...)
- Execute each player's code in parallel
- Stop when all of the players except one are dead

### How it works

Magic

### TODO

- Stuff
- Other stuff
