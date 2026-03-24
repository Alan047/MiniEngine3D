#include "core/Engine.hpp"

Engine::Engine() 
    :   window(800, 600), 
        running(true),
        renderer(window.getRenderer(), 800, 600),
        camera(800, 600)
         {
            cubeMesh = Mesh::createCube();
            box = Mesh::createBox(2.0f, 1.0f, 1.0f);
            triangulo1 = Mesh::loadObj("src/objetos/teste.obj");

            
            
            
            // Cubo azul
            // GameObject cube;
            // cube.mesh = &cubeMesh;
            // cube.color = 0xFF0000FF;
            // cube.transform.position = { -3, 1, 3 };
            // scene.add(cube);
            
            // // box azul
            // GameObject box1;
            // cube.mesh = &box;
            // cube.color = 0xFFFF0000;
            // cube.transform.position = { 0, 0, 5 };
            // scene.add(cube);
            
            GameObject triag;
            triag.mesh = &triangulo1;
            triag.color = 0x0000FF80;
            triag.transform.position = {0, 0, -1};
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
            // obj.transform.position.z -= 0.001f;

            Mat4 model = obj.transform.getModelMatrix();
            Mat4 mvp = projection * view * model;

            std::vector<Vec3> projected;

            for (const auto& v : obj.mesh->vertices)
                projected.push_back(renderer.project(v, mvp));

            for (const auto& t : obj.mesh->triangles)
            {
                renderer.drawTriangle(
                    projected[t.a],
                    projected[t.b],
                    projected[t.c],
                    obj.color
                );

                Vec3 lin1 = projected[t.a];
                Vec3 lin2 = projected[t.b];

                renderer.drawLine(lin1.x, lin1.y, lin2.x, lin2.y, 0xFFFF0000);
            }
        }



        //==========================================

        renderer.present();
    }
}