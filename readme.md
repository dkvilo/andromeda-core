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
  make app
  
  # run the application
  make run 

```


## Proxima

```rust

// let is local scope
let x: @i8 := 3;
let y: @i8 := 5;
let z: @f32 := 33.0;

let name: @str := "David";
let grate: @char := 'A';
let is_valid: @bool := true;

extern get_user :: (name: @str, age: @i8) -> @i8 {
  return age * 2;
};

// Struct with constructor 
extern typedef struct Person :: <name: @str, age: @i8> -> @(self) {
  self(name, age); // bind arg to the property automatically (based on param type)
};

extern get_age :: (ptr& @Person) -> @i8 {
  return ptr->age;
}

extern dereference :: (ptr& @Person) -> @Person {
  @(Person)[ptr]->age = 22;
  return ptr;
}

// Actor interface for the Person, Entity and User type
#Actor :: [ptr&: @Person, @Entity, @User] {
  extern act :: (ptr: @(self));
};

```