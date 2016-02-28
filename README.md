# Skadi
A simple chess engine written in modern C++.

Skadi comes with a basic interface which can be played to play games against the engine, let the engine play a game against itself, or play against another human player.

The library and interface can be built and run by issuing:
```
cd build
cmake .
make
./bin/simple_interface
```
Simple algebraic notation such as `e4`, `Nxe4`, `exf8=Q+` is understood, and can be used as input to the interface. Furthermore, the library supports loading from FEN, and will support PGN in the future.

## Dependencies

Are supplied as submodules within the git repository.

- [Catch](https://github.com/philsquared/Catch) is used for unit tests.
- [JWUtil](https://github.com/jwbuurlage/JWUtil) is used for logging / command line flags.

## Features

- [ ] **Can be used to play chess against another human**
  - [x] Basic movement of chess pieces
  - [x] Capturing
  - [ ] Special moves
    - [x] En passant
    - [ ] Castling
    - [ ] Pawn promotion
  - [ ] Understands check / checkmate
  - [ ] Stalemate / 50 move rule
- [ ] **Can be used to play chess against a simple AI**
  - [ ] Greedy search up to a certain depth, with a simple evaluation function
  - [ ] Supports [UCI](https://en.wikipedia.org/wiki/Universal_Chess_Interface)
