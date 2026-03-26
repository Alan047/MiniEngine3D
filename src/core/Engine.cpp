#include "core/Engine.hpp"

Engine::Engine() 
    :   window(800, 600), 
        running(true),
        renderer(window.getRenderer(), 800, 600),
        camera(800, 600)
         {
            cubeMesh = Mesh::createCube();
            box = Mesh::createBox(2.0f, 1.0f, 1.0f);
            triangulo1 = Mesh::loadObj("src/objetos/terrorist.obj");

            
            
            
            // Cubo azul
            GameObject cube;
            cube.mesh = &triangulo1;
            cube.color = 0xFF0000FF;
            cube.transform.position = { -3, 1, 80 };
            scene.add(cube);
            
            // box azul
            GameObject box1;
            box1.mesh = &triangulo1;
            box1.color = 0xFFFFFFFF;
            box1.transform.position = { -20, -10, 65 };
            scene.add(box1);
            
            GameObject triag;
            triag.mesh = &triangulo1;
            triag.color = 0x0000FF80;
            triag.transform.position = {0, -20, 60};
            scene.add(triag);

         } // Inicialização lista: inicializa membros antes do corpo do construtor

// Vec3 posCamera = {0, 0, -5};

void Engine::run()
{
    while (running) {
        running = window.pollEvents();

        renderer.clear(0xFF202020); // cinza escuro

        // Adicone tudo aqui
        //===========================================

        // camera.setPosition(posCamera);
        Mat4 projection = camera.getProjectionMatrix();
        Mat4 view = camera.getViewMatrix();

        for (auto& obj : scene.objects)
        {
            obj.transform.rotation.y += 0.001f;
            // obj.transform.position.z -= 0.05f;

            Mat4 model = obj.transform.getModelMatrix();
            Mat4 mvp = projection * view * model;

            std::vector<Vec3> projected;

            for (const auto& v : obj.mesh->vertices) 
                projected.push_back(renderer.project(v, mvp));

            for (const auto& t : obj.mesh->triangles)
            {
                Vec3 v0 = projected[t.a];
                Vec3 v1 = projected[t.b];
                Vec3 v2 = projected[t.c];
                
                // Desenha o Triangulo
                renderer.drawTriangle(v0, v1, v2, obj.color);

                // Wireframe(debug)
                renderer.drawLine(v0.x, v0.y, v1.x, v1.y, 0xFFFF0000);
                renderer.drawLine(v1.x, v1.y, v2.x, v2.y, 0xFFFF0000);
                renderer.drawLine(v2.x, v2.y, v0.x, v0.y, 0xFFFF0000);
            }
        }



        //==========================================

        renderer.present();
    }
}