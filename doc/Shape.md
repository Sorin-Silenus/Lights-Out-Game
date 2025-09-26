The actual process of drawing shapes under the hood can be a little tricky, but the implementation of the program should make this somewhat simple. The shape class is the parent to other shapes in the program (i.e. Triangle, Rectangle).

# Initialization
A shape will take in a few things, first off is a [shader](Shader.md). Besides that, we will take in the basic parts to make a shape, such as a size, location, and color.
## Init Vertices
Vertices are stored in an array as normalized device coordinates. This is better explained [here](https://learnopengl.com/Getting-started/Hello-Triangle). Here is a short example of a triangle using NDC ![](https://learnopengl.com/img/getting-started/ndc.png)
## Init VAO? VBO?
You will come across some of these in the initialization, these are vertex buffers, specifically, vertex array object and vertex buffer object. These are actually the buffers of the vertices that will be drawn that are stored in the GPU. The important takeaway here is that we want to make sure that the vertices of our shape are associated with a buffer.
# Drawing
There are two functions that concern drawing in each shape; while draw may be self-explanatory, we also have `setUniforms`.
## Set Uniforms
Looking at some of the cases of how various things are displayed in example code, you might notice that the `setUniforms` function must be called before the draw function. Basically, it is making sure the perspective will be correct for a 2D view. Since linear algebra is not a prerequisite of this class, the important takeaway is that `setUniforms` must be called before calling `draw`. If you're interested, you can read more about it [here](https://learnopengl.com/Getting-started/Transformations).
## Draw
The draw function is more traditional in terms of how you might imagine it to work. To use a triangle as an example:
```c++
void Triangle::draw() const {
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
```
This is simply activating our vertex array, calling the GLFW draw function, and deactivating our vertex array. To see a bit more of how the syntax works for `glDrawElements`, you can read about it [here](https://learnopengl.com/Getting-started/Hello-Triangle).
