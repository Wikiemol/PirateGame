Game Framework Structure
========================

The basic structure of the game framework works like this, there are GameObjects, and there is the GameWorld. The GameWorld is essentially a controller that holds all of the GameObjects. The GameObjects can send out messages to the GameWorld. The GameWorld then broadcasts the messages, and then every GameObject can handle that message however they like. The GameWorld can also handle the message on its own. 

![](framework_diagram.png?raw=true)

In this diagram, each arrow represents a message being sent from one node to another. 

Its important to note that each of these layers should be considered very thin. I.e., there should be very little inheritance, one layer at the most. In place of inheritance, one should combine a usage of interfaces, and a usage of static methods within the interface's implementation when common functionality between classes is needed. 

We will now go over each node in more detail, starting with the Game World.

Game World
-----------

We can think of our design philosophy, in a way, as having Model View Controller mentality. In this light, our Game World is the controller. It simply passes messages between the model and the view. The Game Objects and the Action Handler know nothing of the Game World as a whole, they only know how to send and recieve messages from the Game World. 

Every frame, the Game World will go through each of the GameObjects in the world. First, it will go through every object, and call the object's update() method. Then, the GameWorld will handle all messages in the message queue. Finally, the GameWorld will send messages to the ActionHandler to give feedback to the user, and then clear all handled messages in the queue. So every frame, this is what the Game World does: 

1. update()
2. Handle messages
3. User feedback
4. Clear messages

Game Object
-----------

The Game Object is an abstract class. It will have an update() method, a getType() method, and a concrete getId() method. Every game object will have a type, which lets you know what the object can be casted to, every object will have a unique id number. Furthermore, it will also incorporate a messaging interface, which will be described in the Message section. This will simply allow the object to recieve messages. When implementing Objects, one will likely make heavy use of the Physics Library, which will hold only static methods and raw data structures.

Messages
--------
This is one of the most important aspects of the library. The Message object should have a message type, and a hashmap for message properties. You should be able to get the properties from the message using a message property enum for a key. 

Global Utils
------------

Anything in this class should be extremely data oriented. Things like data structures, or data manipulation go here for common standard classes, like std:: data classes or Qt data classes. Things like debugging and test utils can go here too. 

Memory Pool
--------------

The memory pool is worth noting. The GameWorld will only allocate memory through the memory pool, which will be initialized at the beginning. This will allow us to monitor and control the memory that we use, and allow us to optimize for caching. It will also give us a solid idea of *how much* memory we use. Furthermore, nothing should need to allocate memory on the heap except for the GameWorld. If we need to store a reference to something, it should be via a custom id (such as the game object's getId method) or if we really need to allocate something, we should request that the GameWorld allocate it.

Action Handler
--------------
The action handler is pretty straightforward, just functions that handle output to the user and the file system. 