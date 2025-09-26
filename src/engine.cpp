#include "engine.h"
#include <iostream>

// Off and On
color off, on;
enum state {start, playing, win};
state screen;
bool gameOver = true;
int numClicks = 0;

Engine::Engine() : keys() {
    this->initWindow();
    this->initShaders();
    this->initShapes();

    off = {0.5f, 0.5f, 0.5f, 1.0f};
    on = {1.0f, 1.0f, 0.0f, 1.0f};
}

Engine::~Engine() {}

unsigned int Engine::initWindow(bool debug) {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    // This creates the window using GLFW.
    // It's a C function, so we have to pass it a pointer to the window variable.
    window = glfwCreateWindow(width, height, "engine", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    // This sets the OpenGL context to the window we just created.
    glfwMakeContextCurrent(window);

    // Glad is an OpenGL function loader. It loads all the OpenGL functions that are defined by the driver.
    // This is required because OpenGL is a specification, not an implementation.
    // The driver is the implementation of OpenGL that is installed on your computer.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // OpenGL configuration
    // This defines the size of the area OpenGL should render to.
    glViewport(0, 0, width, height);
    // This enables depth testing which prevents triangles from overlapping.
    glEnable(GL_BLEND);
    // Alpha blending allows for transparent backgrounds.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    return 0;
}

void Engine::initShaders() {
    // load shader manager
    shaderManager = make_unique<ShaderManager>();

    // Load shader into shader manager and retrieve it
    shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag",  nullptr, "shape");

    // Configure text shader and renderer
    textShader = shaderManager->loadShader("../res/shaders/text.vert", "../res/shaders/text.frag", nullptr, "text");
    fontRenderer = make_unique<FontRenderer>(shaderManager->getShader("text"), "../res/fonts/MxPlus_IBM_BIOS.ttf", 24);

    // Set uniforms
    textShader.setVector2f("vertex", vec4(100, 100, .5, .5));
    shapeShader.use();
    shapeShader.setMatrix4("projection", this->PROJECTION);
}

void Engine::initShapes() {
    // TODO: Create shape(s) here! (Code is in README)
    buttons.push_back(make_unique<Rect>(shapeShader, vec2(width / 6, height /6), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[0]->getPosX(), buttons[0]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[1]->getPosX(), buttons[1]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[2]->getPosX(), buttons[2]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[3]->getPosX(), buttons[3]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[0]->getPosX() + width / 6, buttons[0]->getPosY()), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[5]->getPosX(), buttons[5]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[6]->getPosX(), buttons[6]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[7]->getPosX(), buttons[7]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[8]->getPosX(), buttons[8]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[5]->getPosX() + width / 6, buttons[5]->getPosY()), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[10]->getPosX(), buttons[5]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[11]->getPosX(), buttons[6]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[12]->getPosX(), buttons[7]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[13]->getPosX(), buttons[8]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[10]->getPosX() + width / 6, buttons[5]->getPosY()), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[15]->getPosX(), buttons[5]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[16]->getPosX(), buttons[6]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[17]->getPosX(), buttons[7]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[18]->getPosX(), buttons[8]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[15]->getPosX() + width / 6, buttons[5]->getPosY()), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[20]->getPosX(), buttons[5]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[21]->getPosX(), buttons[6]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[22]->getPosX(), buttons[7]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
     buttons.push_back(make_unique<Rect>(shapeShader, vec2(buttons[23]->getPosX(), buttons[8]->getPosY() + 150), vec2(100,100), color(1,1,0,1)));
    for (int i = 0; i < buttons.size(); i++) {
        outline.push_back(make_unique<Rect>(shapeShader, vec2(buttons[i]->getPosX(), buttons[i]->getPosY()), vec2(115,115), color(1,0,0,1)));
    }



}

void Engine::processInput() {
    glfwPollEvents();
    glfwGetCursorPos(window, &MouseX, &MouseY);

    MouseY = height - MouseY; // make sure mouse y-axis isn't flipped

    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key) {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    // in start screen, start the game when the "s" key is pressed
    if (keys[GLFW_KEY_S] && screen == start) {
        screen = playing;
    }

    //This for loop makes the outline appear if the mouse hovers over the square
    for (unique_ptr<Shape>& outline : outline) {
        if(outline->isOverlapping(vec2(MouseX, MouseY))) {
            outline->setOpacity(1);
        } else {
            outline->setOpacity(0);
        }
    }
    // If a button is pressed, turn it off or on
    bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    if (screen == playing) {
        if (mousePressedLastFrame && !mousePressed) {
            ++numClicks;
            for(int i = 0; i < buttons.size(); i++) {
                if(buttons[i]->isOverlapping(vec2(MouseX, MouseY))) {
                    switchState(buttons[i]);
                    if (i - 5 >= 0) {
                        switchState(buttons[i - 5]);
                    }
                    if (i + 5 <= 24) {
                        switchState(buttons[i + 5]);
                    }
                    if (i - 1 >= 0 && buttons[i]->getPosX() == buttons[i - 1]->getPosX()) {
                        switchState(buttons[i - 1]);
                    }
                    if (i + 1 <= 24 && buttons[i]->getPosX() == buttons[i + 1]->getPosX()) {
                        switchState(buttons[i + 1]);
                    }
                }
            }
        }
    }
    mousePressedLastFrame = mousePressed;
}


void Engine::update() {
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    bool won;
    if (screen == playing) {
        won = true;
        for (unique_ptr<Shape>& button : buttons) {
            if (button->getColor3() == vec3(1, 1, 0)) {
                won = false;
            }
        }
        if (won) {
            screen = win;
        }
    }


    // This function polls for events like keyboard input and mouse movement
    // It needs to be called every frame
    // Without this function, the window will freeze and become unresponsive
    glfwPollEvents();


}

void Engine::render() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // set shader to draw shapes
    shapeShader.use();
    switch (screen) {
        case start: {
            string welcome = "Welcome to Lights Out!";
            string directionsLine1 = "The objective of this game is to";
            string directionsLine2 = "have all lights turned off";
            string directionsLine3 = "Once a button is pressed all adjacent ";
            string directionsLine4 = "buttons will go from off to on ";
            string directionsLine5 = "or vise versa";
            string startMessage = "Press s to start";
            // (12 * message.length()) is the offset to center text.
            // 12 pixels is the width of each character scaled by 1.
            // NOTE: This line changes the shader being used to the font shader.
            //  If you want to draw shapes again after drawing text,
            //  you'll need to call shapeShader.use() again first.
            this->fontRenderer->renderText(welcome, width/2 - (12 * welcome.length()), (height/2) + 250, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(directionsLine1, width/2 - (12 * directionsLine1.length()), (height/2) + 125, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(directionsLine2, width/2 - (12 * directionsLine2.length()), (height/2)+100, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(directionsLine3, width/2 - (12 * directionsLine3.length()), (height/2) + 50, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(directionsLine4, width/2 - (12 * directionsLine4.length()), (height/2)+25, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(directionsLine5, width/2 - (12 * directionsLine5.length()), (height/2), projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(startMessage, width/2 - (12 * startMessage.length()), (height/2) - 75, projection, 1, vec3{1, 1, 1});

            break;
        }
        case playing: {
            auto start = glfwGetTime();
            // Render shapes
            // For each shape, call it's setUniforms() function and then call it's draw() function
            for (const unique_ptr<Shape>& s : outline) {
                s->setUniforms();
                s->draw();
            }
            for (const unique_ptr<Shape>& s : buttons) {
                s->setUniforms();
                s->draw();

            }
            string clicks = "Clicks:" + std::to_string(numClicks);
            this->fontRenderer->renderText(clicks, 10, 25, projection, 1, vec3{1, 1, 1});
            break;

        }

        case win: {
            auto end = glfwGetTime();
            if(gameOver) {
                calculateTime = static_cast<int>(end - start);
                gameOver = false;
            }
            string finalTime = "You completed the game in: " + std::to_string(calculateTime) + " seconds";
            string congrats = "You Win!";
            this->fontRenderer->renderText(congrats, width/2 - (12 * congrats.length()), (height/2) + 25, projection, 1, vec3{1, 1, 1});
            this->fontRenderer->renderText(finalTime, width/2 - (12 * finalTime.length()), (height/2) - 75, projection, 1, vec3{1, 1, 1});
            break;
        }
    }

    // This is glfw function call is required to display the final image on the screen
    // The front buffer contains the final image that is displayed.
    // The back buffer contains the image that is currently being rendered.
    glfwSwapBuffers(window);
}


 void Engine::switchState(unique_ptr<Shape>& button) {
     if (button->getColor3() == vec3(1, 1, 0)) {
         button->setColor(off);
     }
     else if (button->getColor3() == vec3(0.5, 0.5, 0.5)) {
         button->setColor(on);
     }
 }



bool Engine::shouldClose() {
    return glfwWindowShouldClose(window);
}
