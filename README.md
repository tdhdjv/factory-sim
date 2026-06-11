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
### Creating Your Own Machine
``` cpp
namespace LongDay {
  /*Change class name to your own*/
  /*Change In, Out type to your own types*/
  class MyMachine: public Machine<In, Out>
   :Machine<In, Out>(capacity, tickForProduction, breakDownProbability) {}

  Out transform(const In& in) {
    Out out;
    /*Logic to transform in to out*/
    ...
    return out;
  }

  const char* get_name() const override {
    return "my machine";
  }
}
```
### Creating Your Own Conveyor
``` cpp
Conveyor<Type> conveyor(capacity);
```

### Creating Your Own Factory
``` cpp
namespace LongDay {
  /*Change class name to your own*/
  /*Change In, Out type to your own types*/
  class MyFactory: public Factory<In, Out> {
    append(std::make_unique<Machine/Conyevor>(...))
    .append(std::make_unique<Machine/Conyevor>(...))
    .append(std::make_unique<Machine/Conyevor>(...))
    .append(std::make_unique<Machine/Conyevor>(...))
    .append(std::make_unique<Machine/Conyevor>(...))
    .append(std::make_unique<Machine/Conyevor>(...));
  }

  const char* get_name() const override {
    return "my factory";
  }
}
```
### Example
#### Machine
``` cpp
namespace LongDay {
	class DoubleMachine: public Machine<i32, i32> {
	public:
		explicit DoubleMachine(u64 capacity, u64 ticksForProduction, f32 breakDownProbability)
      :Machine<i32, i32>(capacity, tickForProduction, breakDownProbability) {}

		i32 transform(const i32& num) override {
      i32 result;
      result = num*2;
      return result;
    }

		const char* get_name() const override {
      return "double machine"
    }
	};
}

```
``` cpp
namespace LongDay {
	class SquareMachine: public Machine<i32, i32> {
	public:
		explicit Squareachine(f32 breakDownProbability)
      :Machine<i32, i32>(10, 3, breakDownProbability) {}

		i32 transform(const i32& num) override {
      i32 result;
      result = num*num;
      return result;
    }

		const char* get_name() const override {
      return "square machine"
    }
	};
}
```
#### Factory
``` cpp
namespace LongDay {
  /*Change class name to your own*/
  /*Change In, Out type to your own types*/
  class NumberFactory: public Factory<In, Out> {
    append(std::make_unique<Conveyor<i32>>(3))
    .append(std::make_unique<DoubleMachine>(5, 10, 0.01f))
    .append(std::make_unique<Conveyor<i32>>(5))
    .append(std::make_unique<SquareMachine>(0.0025f));
  }

  const char* get_name() const override {
    return "number factory";
  }
}
```
## API Reference
See [API.md](API.md) for detail
