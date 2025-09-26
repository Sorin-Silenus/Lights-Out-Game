Fonts can be a little funny in OpenGL, essentially, fonts don't work in the way a font in your word processor or IDE does, as OpenGL doesn't have any way to read it out of the box. This is where one of our included libraries, freetype comes in. With the help of freetype, we can load in a font into our program as a texture. This is accomplished in this program with two classes, `Font` and `FontRenderer`.
# Font
The font creation process is fairly straightforward, as you may see, the constructor takes in a file path, and a size. The file path is a path to a TTF font, and the size is how big the desired default size will be. Now, with the help of freetype, we can go about loading the font into the program. This is accomplished in three steps:
## Load the font
This is where freetype does its work. It takes a TTF file, a common font format, and parses it into the program in a way that we can interface with. Each character is represented by a "glyph" in a font, so we will simply fetch the glyphs we need.
```c++
// Load font as face
FT_Face face;
if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
}

// Set size to load glyphs as
FT_Set_Pixel_Sizes(face, 0, fontSize);

// Attempt to load character glyph
if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
}
```
> Our font will load in Sans problème

Here we create our freetype representation of our font, then set it to our specified font size, and finally attempt to load the character `x` to see that it can fetch a glyph properly.

## Map each character to a texture
Now comes actually creating a texture for each of our glyphs. As you can see, we are loading in the 128 characters of font, this corresponds to the standard ASCII character set. While the provided font is likely Unicode, using a standard character set will keep things simple. Next, a texture is generated using OpenGL syntax for texture.
```c++
// generate texture
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    face->glyph->bitmap.width,
    face->glyph->bitmap.rows,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    face->glyph->bitmap.buffer
);
```
> Really putting the "text" in "texture"

If you're interested in a bit more of how textures work in OpenGL, you can check out [this page](https://learnopengl.com/Getting-started/Textures).

## Store the texture into a map.
For storing our characters, we will be using a map. If you remember what a dictionary is in python (and all the joys of nested dictionaries), then you get what a map is, this time with 100% less nesting™! Simply put, instead of an index, a map is a data collection that stores a value at a key, which is a data type of your choosing. This works out quite well for us since we can use a map to store all our character textures with the corresponding character as the key! At the end of the constructor, you can see this in action.
```c++
Character character = {
    texture,
    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
    static_cast<unsigned int>(face->glyph->advance.x)
};
Characters.insert(std::pair<char, Character>(c, character));
```
> Its seldom you see code with so much character.

Each texture is stored in a struct that is defined in the header of `Font`. This is so that we can store important information regarding the size of the texture. This is stored in four fields:
- TextureID - ID handle of the glyph texture
- Size - Size of glyph
- Bearing - Offset from baseline to left/top of glyph
- Advance - Offset to advance to next glyph

Feel free to read a bit more about fonts if you're interested in how offsets work, but for our purposes, we are just making sure that the values associated with each character match up with the texture we're storing. If you're curious why we are storing the texture as an `int` instead of a texture itself, it's because of how GLFW handles textures. Simply, GLFW will make a texture and hold it in its own texture cache, giving us an ID to use whenever we want to use it. Not unlike a coat check, when you want your coat (texture), you give the attendant your little slip (ID). Again, this can be read into more at [this page](https://learnopengl.com/Getting-started/Textures).

# Font Renderer
Simply having a font loaded won't do us any good, so this is where `FontRenderer` comes in. This is in charge of actually putting our finely crafted font textures to screen. The font rendering is done in much the same [[way that shapes are drawn|Shape]]. So this will focus on the unique functionality of the `FontRenderer`.
## Render Text
This function takes in what you might expect: the text to render and where to render it. It also includes a color to render text in, as well as a scale. Note that the scale is scaling off the size provided in the initialization. Simply, the string will be parsed one character at a time, and each character rendered individually, moving along from the initial coordinates. 