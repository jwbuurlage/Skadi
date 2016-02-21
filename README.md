# Skadi
A simple chess engine writte in modern C++.

Skadi comes with a basic interface which can be played to play games against the engine, let the engine play a game against itself, or play against another human player. This can be built and run by issuing:
```
make
./bin/simple_chess
```

## Dependencies

Are supplied as submodules within the git repository.

- [Catch](https://github.com/philsquared/Catch) is used for unit tests.
- [JWUtil](https://github.com/jwbuurlage/JWUtil) is used for logging / command line flags.

## Features

- [ ] **Can be used to play chess against another human**
  - [x] Basic movement of chess pieces
  - [x] Capturing
  - [ ] Special moves (en-passent, castling, promotion)
  - [ ] Understands check / checkmate
- [ ] **Can be used to play chess against a simple AI**
  - [ ] Greedy search up to a certain depth, with a simple evaluation function
