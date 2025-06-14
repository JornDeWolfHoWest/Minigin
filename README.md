# DigDug
[https://github.com/JornDeWolfHoWest/Minigin](https://github.com/JornDeWolfHoWest/Minigin)


## Sounddesign
I decided to use SDL2 for sfx, however this can be expanded if the user provides a different source of input which they specify in the beginning what they use, either built in one that  I made for windows or an expanded sound class

## Inputmanager
I decided to build an inputmanager that can support multiple controllers using an index, -1 for general, and a keyboard handler which only does keyboard events

I also made it an object derived structure like specified within class, using std::shared_ptr<> as it's prefered way of handling pointers for shared objects like gameobjects, but normal pointers for components as each object is responsible for their own component this can't be handed to another object without ddeleting and re-adding 