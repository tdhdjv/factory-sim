# API Documentation
# Backend
A representation of a factory pipeline, modeling factories, machines, conveyor, etc...
## Sink<T> (interface)
Consumes an object, and does something with object
### Methods
- **consume(object:T&)**: consumes an object and does an operation (ex: printing the value data, free in the object...)

## Source<T> (abstract)
Creates an object, and feeds it to a sink
### Member Variables
- **consumer**: Sink<T>*: the sink the source will 'feed' ( this: Source -> consumer: Sink )
### Methods
- **feed()**: feeds the consumer
- **set_consumer(Sink<T>*)**: sets consumer

## Process<In, Out> (interface)
Consumes and object, and transform it to another object (In -> Out)
### Inheritance
- **Sink<In>**
- **Source<Out>**

## StageBase (interface)
And an abstract class that used as a base for (ex: covenyors, machines, factory).
A templateless class for stage. 
Uses linked lists to create a sequence.
### Member Variables
- __next: StageBase*__: The next Stage in the sequence
### Methods
- __connect(next:StageBase*)__: Connects the stage with the next (sets next)
- **tick()** : does a tick
- **get_name()** : gets the name of the object (user defined name)

## Stage<In, Out> (interface)
A stage with templates, represents a stage in a factory (ex: conveyor, crusher, heater, ...)
### Inheritance
- StageBase
- Process<In, Out>

## AtomicStage<In, Out> (interface)
A stage that cannot be divided into further stages (ex: conveyor, machine)
### Inheritance
- Stage<In, Out>
### Member Variables
- queue: std::queue<In>
- capacity: u64

## Conveyor<in>
A stage that transfers objects to another stage, whilst also being able to store the object if transfer cannot be done.
### Inheritance
- Stage<In, Out>
### Methods
- **tick()**: tries to push the data to the next stage, stores if fail.

## Machine<In, Out> (abstract)
A stage that transform one data into another, and transfers it to the next stage.
The transformation takes a certain amount of time, and the machine has a probability of breaking down.
## Inheritance
- Stage<In, Out>
### Member variables
- **progress: u32**: How much the transformation is done
- **tickForProduction: u32**: How long a transformation takes
- **failureProbability: f32**: How likely the machine will breaking per every tick
- **broken: b8**: Is the machine broken?
### - 
- **transform(input: In&)**: Transform Input onto output
- **tick()**: Increases progress, and when progress finished sends transformed data to the next stage
- **fix()**: Change broken to false

## Factory<In, Out> 
A stage that is composed of other smaller stages (Machines, and Conveyor, or even other smaller factories)
### Inheritance
- Stage<In, Out>
### Member variables
- **stages: std::vector<StageBase>**: All the stages that compose the factory
### Methods
- **tick()**: Ticks all the sub stages that compose the factory in reserve order (The reverse order is to simulate the simultaneity, if the order wasn't reversed. The objects can be updated two or more times in one tick)

## Scene<In, Out>
A scene composes the whole process of production
### Member variables
- **source: Source<In>**: Represents the source of the material (ex: natural resources, energy...)
- **factory: Factory<In, Out>**: Represents the main factory that processes the materials to product
- **sink: Sink<In>**: Represents the consumer of the product(ex: consumers, busninesses that use the product...)
### Methods
- **tick()**: Ticks all the process in the scene
