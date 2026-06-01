# Long Day Factory
<img width="716" height="712" alt="longday" src="https://github.com/user-attachments/assets/bc7b42a4-5a56-4665-b1ac-6b924b7ea364" />

## Why Long Days?
Long day factory is a reference to a meme called "Long Day Factory".\
The meme is about a fictional place that produces "Long Days".\
There are several reasons why we choose this fictional factory to simulate, instead of conventional factories.\
1. **Uniqueness** — Choosing a fictional factory simulation, give uniqueness and character, compared to a boring conventional factory.
2. **Extendibility** — A fictional factory simulation, forces us to make a general interface for any factory, as it is non specific. This means that the code is built with extendibility in mind.
3. **Creativity** — A fictional factory allows us creative liberty, allowing us to come up with machines, and component that might be in a **Long Day Factory**.
4. **Comedy** — It provides comedic value

## Setup
### Installation

``` cmd
git clone git@github.com:tdhdjv/factory-sim.git
```

### Build

`Ctrl` + `Shift` + `B`

### Run

`F5`

## Requirements

### Windows
#### VSCode
- C/C++: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
- MakeFile Tools: https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools

#### Tools
- GCC
- Make (MakeFiles)
#### Install
In MSYS MINGW64 run:
```console 
pacman -S mingw-w64-clang-x86_64-make
```
for Make in windows

### Linux
#### Tools
- GCC
- Make (MakeFiles)

#### LIBRARIES
- glfw (Use package manager to install, ex: ```sudo dnf install glfw-devel```)

## Quick Start
### Creating Your Own Factory
``` cpp
namespace LongDay {
  /*Change class name to your own*/
  class MyFactory: public Factory<> {
  }
}
```

## API Reference
See [API.md](API.md) for detail
