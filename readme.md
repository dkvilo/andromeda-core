# Andromeda-Core

Probably another Game Library build top on the bgfx backend. Which will have it's own programming language frontend (Proxima) build top on llvm

Project is very sideeey, It is possible that I'll newer finish it.

Spec: C++ 11

```zsh

  # get dependencies
  git submodule update --init --recursive

  # build dependencies
  make build
  
  # build sandbox layer
  make run
  
  # run the application
  make app 

```


## Proxima

```prx

  let x := 888;
  let y := 777;

  let name := "David";

  get_user :: () -> int {
    let age := 22;
  }

```