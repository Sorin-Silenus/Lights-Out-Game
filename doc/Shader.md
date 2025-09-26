Shaders are essentially little programs that run on the GPU. These are important to the actual displaying of stuff in our window. If you're interested in how shaders work and are structured, [this page](https://learnopengl.com/Getting-started/Shaders) has an in-depth look into working with shaders. As for this program, the important things to know about shaders are that they take in inputs and give outputs. The two shaders used in the program are **vertex** and **fragment** shaders. The **vertex** shader takes in vertices and [applies transformations to their coordinates](FAQ.md#why-do-i-need-a-vertex-shader-why-would-i-want-to-make-transformations-if-im-just-working-in-2d). The **fragment** shader is used to determine the colors of pixels on the screen. More information about vertex and fragment shaders and why we use them can be found [here](https://learnopengl.com/Getting-started/Hello-Triangle).

# Shader
Our shader object is used to store our shader programs and manage how and when they are used. The important bit of this class is `compile`. As stated, shaders are little programs, and just like C or C++ code, need to be compiled. It is in this function where that happens. It takes the source of the shader programs and turns them into the shaders that we can interact with later in our program. There are also quite a few functions that are like setters but for “vectors”. These vectors are not quite like vectors you may be used to in C++, but in this case, these vectors are just a set of values, not terribly unlike a tuple. Essentially, the names of the functions indicate how many values the vector is, and its type. For example:
```c++
// So based on the function name, the setVector below will take in a vector that has 4 floats
// note: vectors are types from the glm (gl math) library
glm::vec4 myVector = {1.0f, 0.5f, 0.75f, 0.25f};

myShader->setVector4f("something", myVector);
```
The reason for these functions is to give inputs to our shader programs.

## Shader Manager
Shader Manager functions very similar to the functionality of [fonts](Font). A map stores the shaders, with the shader names as the keys and the values being the associated shaders. These shaders are fetched from the manager with the getter function. `loadShader` will simply read in the contents of our programs and put them into the `Shader` constructor, to build the shader. It will then call compile to build the program and store in the aforementioned map.
