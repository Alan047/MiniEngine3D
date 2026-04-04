#include "core/Engine.hpp"
#include <iostream>


Engine::Engine() 
    :   window(800, 600), 
        running(true),
        renderer(window.getRenderer(), 800, 600),
        camera(800, 600)
         {
            cubeMesh = Mesh::createCube();
            box = Mesh::loadObj("src/objetos/terrorist.obj");
            triangulo1 = Mesh::loadObj("src/objetos/teste.obj");
            table = Mesh::loadObj("src/objetos/table.obj");

            
            
            
            // Cubo azul
            GameObject table01;
            table01.mesh = &table;
            table01.color = 0xFF0000FF;
            table01.transform.position = { 0, 0, 10};
            table01.transform.scale = {2, 2, 2};
            scene.add(table01);

            GameObject triangulo02(1);
            triangulo02.mesh = &cubeMesh;
            triangulo02.color = 0xFF00FF00;
            triangulo02.transform.position = { -2, 0, 0};
            triangulo02.transform.scale = {0.1f, 0.1f, 0.1f};
            scene.add(triangulo02);
            
            // box azul
            GameObject box1;
            box1.mesh = &triangulo1;
            // box1.color = 0xFF202020;
            box1.transform.position = { 0, 0, -20};
            box1.transform.scale = {5, 5, 5};
            scene.add(box1);

            // GameObject obj01;
            // obj01.transform.position = {0, -1, -5};
            // scene.add(obj01);
            
            // GameObject triag;
            // triag.mesh = &triangulo1;
            // triag.color = 0xFF0000FF;
            // triag.transform.position = {0, -1, 80};
            // scene.add(triag);

         } // Inicialização lista: inicializa membros antes do corpo do construtor



void Engine::run()
{
    Vec3 posCamera = {0, 1, 5};
    camera.setPosition(posCamera);


    while (running) {
        running = window.pollEvents();

        const uint8_t* keys = SDL_GetKeyboardState(NULL);
        
        int mouseX, mouseY;
        
        SDL_GetRelativeMouseState(&mouseX, &mouseY);


        float deltaTime = 0.016f; // temporário (~60 FPS)

        camera.update(deltaTime, keys);

        camera.processMouseMovement(mouseX, mouseY);

        renderer.clear(0xFF202020); // cinza escuro

        // Adicone tudo aqui
        //===========================================

        
        Mat4 projection = camera.getProjectionMatrix();
        Mat4 view = camera.getViewMatrix();

        drawGrid();

        for (auto& obj : scene.objects)
        {
            // obj.transform.rotation.y += 0.001f;
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

                if (v0.z < 0 || v1.z < 0 || v2.z < 0) {
                
                    // Desenha o Triangulo
                    renderer.drawTriangle(v0, v1, v2, obj.color);

                    // Wireframe(debug)
                    renderer.drawLine(v0.x, v0.y, v1.x, v1.y, 0xFFFF0000); // verde
                    renderer.drawLine(v1.x, v1.y, v2.x, v2.y, 0xFFFF0000); // azul
                    renderer.drawLine(v2.x, v2.y, v0.x, v0.y, 0xFFFF0000); // vermelho
                }
                
                
            }
        }



        //==========================================

        renderer.present();
    }
}

void Engine::drawGrid() {

    Mat4 projection = camera.getProjectionMatrix();
    Mat4 view = camera.getViewMatrix();
    Mat4 mvp = projection * view * Mat4::identity();

    int size = 30;
    float spacing = 1.0f;

    for (int i = -size; i <= size; i++) {
        float pos = i * spacing;

        Vec4 a = {-size * spacing, 0, pos, 1.0f};
        Vec4 b = { size * spacing, 0, pos, 1.0f};
        Vec4 c = {pos, 0, -size * spacing, 1.0f};
        Vec4 d = {pos, 0,  size * spacing, 1.0f};

        // View space
        Vec4 a_view = view * a;
        Vec4 b_view = view * b;
        Vec4 c_view = view * c;
        Vec4 d_view = view * d;

        float near = 0.1f;

        // ===== LINHAS DO EIXO X =====
        {
            Vec4 p0 = a_view;
            Vec4 p1 = b_view;

            if (clipLineNear(p0, p1, near))
            {
                Vec3 a_proj = renderer.project({p0.x, p0.y, p0.z}, projection);
                Vec3 b_proj = renderer.project({p1.x, p1.y, p1.z}, projection);

                renderer.drawLine(a_proj.x, a_proj.y, b_proj.x, b_proj.y, 0xFF000000);
            }
        }

        // ===== LINHAS DO EIXO Z =====
        {
            Vec4 p0 = c_view;
            Vec4 p1 = d_view;

            if (clipLineNear(p0, p1, near))
            {
                Vec3 c_proj = renderer.project({p0.x, p0.y, p0.z}, projection);
                Vec3 d_proj = renderer.project({p1.x, p1.y, p1.z}, projection);

                renderer.drawLine(c_proj.x, c_proj.y, d_proj.x, d_proj.y, 0xFF000000);
            }
        }
    }
        

        // z de a e b:-0.353553 -0.353553
        // z de c e d:-0.353553 -13.7886
        // Valor de z de C visivel: -0.353553
        // Valor de z de D visivel: -13.7886

        // z de c e d:0 -14.1421
        // z de a e b:-12.7279 -12.7279

        // std::cout << i << std::endl;
        // std::cout << pos << std::endl;

        // Vec3 a = renderer.project({-size * spacing, 0, pos}, mvp);
        // Vec3 b = renderer.project({size * spacing, 0, pos}, mvp);

        // Vec3 c = renderer.project({pos, 0, -size * spacing}, mvp);
        // Vec3 d = renderer.project({pos, 0,  size * spacing}, mvp);
        

        // std::cout << d.z << std::endl;
        // std::cout << a.z << std::endl;

        // if (a.z > 0 && b.z > 0)
        // {
        //    renderer.drawLine(a.x, a.y, b.x, b.y, 0xFF000000);
        // }
        
        // if (c.z > 0 && d.z > 0) 
        // {
        //     renderer.drawLine(c.x, c.y, d.x, d.y, 0xFF000000);
        // }
        

        // renderer.drawPixel(c.x, c.y, 0xFF00FF00);
        // renderer.drawPixel(d.x, d.y, 0xFF00FF00);
        

}


bool Engine::clipLineNear(Vec4& a, Vec4& b, float near)
{
    // ambos inválidos (atrás da câmera)
    if (a.z <= near && b.z <= near)
        return false;

    // ambos válidos
    if (a.z > near && b.z > near)
        return true;

    // um válido, outro não → calcular interseção
    float t = (near - a.z) / (b.z - a.z);

    Vec4 intersect = {
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        near,
        1.0f
    };

    if (a.z <= near)
        a = intersect;
    else
        b = intersect;

    return true;
}


// 0xFF000000  // preto
// 0xFFFF0000  // vermelho
// 0xFF00FF00  // verde
// 0xFF0000FF  // azul
// 0xFFFFFFFF  // branco