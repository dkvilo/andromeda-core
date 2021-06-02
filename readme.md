# Andromeda-Core

Probably another Game Engine.
Project is very sideeey, It is possible that I'll newer finish it.


# WIP Screenshots

## Editor build (1,4 MB)
<img src="https://github.com/dkvilo/andromeda-core/blob/main/screenshots/editor.png" />

## Release build (255,8 KB)
<img src="https://github.com/dkvilo/andromeda-core/blob/main/screenshots/release.png" />


```zsh

  # get dependencies
  git submodule update --init --recursive

  # build dependencies
  make build
  
  # build sandbox layer in debug mode (Include Engine editor UI)
  make editor
  
  # Run Debug (Engine)
  make run-editor

  # build sandbox layer in release mode (Only Game Layer)
  make release

  # Run release
  make run-release

  # Build debug (Sandbox layer)
  make debug
  # You can use debug build with gdb  
  gdb
  > file ./build/sandbox/build-debug
  > run
  > bt

```
