#pragma once
#include "platform/WindowSDL.hpp"
#include "graphics/SoftwareRenderer.hpp"
#include "graphics/Mesh.hpp"
#include "math/Mat4.hpp"
#include "graphics/Camera.hpp"
#include "scene/Scene.hpp"
#include "graphics/Camera.hpp"


class Engine {
public:
    Engine();
    void run();
    void drawGrid();
    bool clipLineNear(Vec4& a, Vec4& b, float near);

private:
    bool running;
    Window_SDL window; //class de WindowSDL.hpp
    SoftwareRenderer renderer;
    float angle;
    Scene scene;
    Camera camera;
    Mesh cubeMesh;
    Mesh box;
    Mesh triangulo1;
    
};