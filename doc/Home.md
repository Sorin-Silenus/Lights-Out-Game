Welcome to the CS2300 graphics wiki!

Here's a quick rundown how the program works.

# Setup
The first step to the program is the creation of the [Engine](Engine.md). The Engine is the great unifying power over all the functionality of the program, it will initialize the program in three steps. At a glance:
* [Initialize window](Engine.md#initialize-window) - initialize and creates the window we will be working with.
* [Initialize shaders](Engine.md#initialize-shaders) - loads the shape shaders into our program.
* [Initialize shapes](Engine.md#initialize-shapes) - creates any initial shapes to be used in the program.

With these out of the way, a window is created and ready to be drawn upon!
# Loop
The main loop of the program is similarly separated into three major sections.
* [Process input](Engine.md#process-input) - take and handle any input from the user.
* [Update](Engine.md#process-input)- update any counters, timers, etc. for a single frame.
* [Render](Engine.md#process-input) - display anything on the screen that there is to display.

Each of these functions will be called once per frame.
