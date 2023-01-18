# SDL-2d-game
A 2d game entirely written in C++ for academic task.


![documentatie](https://user-images.githubusercontent.com/122129982/213194000-68af2149-4c74-4add-b9a8-2d53cbf15c83.png)


## It is a player vs computer game, each level adding a new enemy in order to increase dificulty. In order to win, you have to eliminate all the enemies by shooting them, while you try to avoid their projectiles.
## Controls: WASD for movement and SPACE for shooting.
## Other features: the menu which allows you to select which level you want to play and the healthbar which shows how much health you and the enemies have left, updating in real time.
## The main reason for realising this project was applying my OOP principples. I created classes for every object in the game(for example background or projectile). In order to reuse code, I created a class hierarchy, the more advanced objects taking characteristics from the simpler one. For handling better whith drawing all these objects, I made a interface class that has a static member which is a pointer to the rendered. All the classes derived from this class inherit this, so it is no longer necessary to pass it as an argument in constructors or drawing functions. The main game class uses STL templates and iterators in order to handle with updating all the objects in the game.
