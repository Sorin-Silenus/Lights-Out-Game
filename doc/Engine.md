The Engine does most of the heavy lifting. It is in charge of pretty much everything related to your window: drawing, taking input, doing logic, etc.
# Initialization
When creating a new engine object, the engine must first do some housekeeping to get everything ready for interaction, this is accomplished in three functions.
## Initialize window
This is where the actual window is created, it begins by starting up OpenGL and stating the version of GLFW we will be using.
```c++
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```
> Here we are choosing to use GLFW version 3.3!


The following code will help set some important features for running the program, as well as some specific to OSX. An example is the bit of code that sets the window to be resizable.
```c++
glfwWindowHint(GLFW_RESIZABLE, false);
```
> Welp, there's any chance of resizing this out the window.

Now that all that is out of the way, we can move onto creating our actual window! We specify things like width, height and window message. We will also set up GLAD, which is a library to help make sure OpenGL is using the correct hardware-specific calls. With that done, all that is left is to specify some drawing options, and we have our window created!
## Initialize shaders
GLFW makes use of [shaders](Shader.md), which are essentially extra bits of instructions to tell the program how to draw certain things. For the most part, you will not need to worry about the shaders, but they function as a little program of their own! The shaders you will find included in the program tell our program to draw our various shapes in two dimensions without looking skewed. Our shader programs are conveniently held in a [ShaderManager class](Shader.md#shader-manager) which will keep track of the shaders for each shape and use the correct ones when needed.
```c++
shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag",  nullptr, "shape");
```
> This line throws some serious shade.
## Initialize shapes
Here, we will create whatever [shapes](Shape.md) we wish to display when our program first starts up. It's where we will be creating most of our shapes that will be used in our program.
```c++
void Engine::initShapes() {
    // red button centered in the top left corner
    button = make_unique<Rect>(shapeShader, vec2{width/2,height/2}, vec2{100, 50}, color{1, 0, 0, 1});
}
```

> All these initialization functions really push my buttons!
# Main loop
## Process input
What's a good program without user interaction? That's where process input comes in! As a name so descriptive implies, this section concerns whatever combination of key taps to key smashes your humble user may choose to impart on your program. So this part of the program can be separated into two sections, input registration and input processing. All possible keys stored in a boolean array `keys[1024]` (Why? This makes it so that more key combinations are possible, such as `alt+F5` and multiple pressed keys at once). 
```c++
// Set keys to true if pressed, false if released
for (int key = 0; key < 1024; ++key) {
    if (glfwGetKey(window, key) == GLFW_PRESS)
        keys[key] = true;
    else if (glfwGetKey(window, key) == GLFW_RELEASE)
        keys[key] = false;
}
```
> Go through the key array and set pressed keys to true and released keys to false.

Once the key is set, we can check for certain key presses and act on them.
```c++
// Close window if escape key is pressed
if (keys[GLFW_KEY_ESCAPE])
    glfwSetWindowShouldClose(window, true);
```
> Here we can get get the value of the array at the key we are looking for

`GLFW_KEY_ESCAPE` is defined by GLFW with `#define` to coordinate to an index in the array. You can find some of the key defines [here](https://www.glfw.org/docs/latest/group__keys.html).

## Update
Update is we update things. As shocking as this is, it's an important part of how to program functions. Depending on the program you're writing, you will likely come across the need for some kind of timer or counter. Whether it's a rectangle moving 1 pixel down the screen every frame or changing to the next frame of an animated sprite, the update function is where the magic happens.
```c++
for (int i = 0; i < rainDrops.size(); ++i) {
        rainDrops[i]->moveY(-1);
}
```
> Almost all the rain puns I came up with mist their target.
## Render
Render is where all the actual drawing will happen. The renderer will clear the screen, draw the shapes and [swap the buffer](FAQ.md#why-do-i-need-to-swap-buffers). When drawing, one must call `setUniforms()` and `draw()` on every shape. `setUniforms()` is doing some important things behind the scenes that make sure the shape will be drawn at the correct perspective.
```c++
// Clear screen to black
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);

// Draw shapes
for (const unique_ptr<Raindrop>& drop : rainDrops) {
    drop->setUniforms();
    drop->draw();
}

// Swap buffer
glfwSwapBuffers(window);
```
