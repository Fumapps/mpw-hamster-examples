## Examples for the hamster-simulator

This repository contains some independent examples for the hamster-simulator in C++.

## Setup SDL

### MacOS

* `brew install sdl2`
* `brew install sdl2_image`
* `brew install sdl2_ttf`

### Windows

* download development libraries, extract them to a directory
    * SDL2: https://libsdl.org/release/SDL2-devel-2.0.14-VC.zip
    * SDL2 Image: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
    * SDL2 TTF: https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip
* extend `CMakeListsLocalProperties.cmake` file
    * set a `SDL2_DIR` variable: `set(SDL2_DIR "<path-to-sdl-dir>")`
    * set a `SDL2_IMAGE_DIR` variable: `set(SDL2_IMAGE_DIR "<path-to-sdl-image-dir>")`
    * set a `SDL2_TTF_DIR` variable: `set(SDL2_TTF_DIR "<path-to-sdl-ttf-dir>")`

### SDL notes

* setup based on: https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/
