#include "core/Engine.hpp"
#include "math/Vec3.hpp"
#include <iostream>


Engine::Engine() 
    :   window(800, 600), 
        running(true),
        renderer(window.getRenderer(), 800, 600),
        camera(800, 600)
         {
            
            
            GameObject obj01;
            obj01.transform.position = {0, 1, 0};
            scene.add(obj01);

            GameObject terrorista;
            terrorista.transform.position = {4, 0, 0};
            terrorista.color = 0xFF00FF00;
            terrorista.mesh = Mesh::loadObj("src/objetos/bule.obj");
            scene.add(terrorista);
            

         } 


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

        
        Mat4 view = camera.getViewMatrix();
        Mat4 projection = camera.getProjectionMatrix();

        drawGrid();

        std::system("cls");

        std::cout << camera.getPositionCamera().x
                  << camera.getPositionCamera().y
                  << camera.getPositionCamera().z << "\n";

        for (auto& obj : scene.objects)
        {
            
            Mat4 model = obj.transform.getModelMatrix();
            Mat4 mvp = projection * view * model;

            std::vector<Vec3> projected(obj.mesh.vertices.size());
            std::vector<bool> valid(obj.mesh.vertices.size());

            for (int i = 0; i < obj.mesh.vertices.size(); i++) 
            {
                // projected.push_back(renderer.project(obj.mesh.vertices[i], mvp));
                valid[i] = renderer.projecSafe(obj.mesh.vertices[i], mvp, projected[i]);
                
            }
                

            for (const auto& t : obj.mesh.triangles)
            {
                if (!valid[t.a] || !valid[t.b] || !valid[t.c])
                    continue;

                Vec3 p0 = projected[t.a];
                Vec3 p1 = projected[t.b];
                Vec3 p2 = projected[t.c];

                Vec3 normal = Vec3::cross(p1 - p0, p2 - p0);

                Vec3 center = (p0 + p1 + p2) * (1.0f / 3.0f);

                

                // 🔥 Back-face culling (screen space)
                float cross =
                    (p1.x - p0.x) * (p2.y - p0.y) -
                    (p1.y - p0.y) * (p2.x - p0.x);

                if (cross < 0)
                    continue;

                                renderer.drawLine(
                    center.x, center.y,
                    center.x + normal.x * 20,
                    center.y - normal.y * 20,
                    0xFF00FF00
                );

                renderer.drawLine(p0.x, p0.y, p1.x, p1.y, 0xFFFF0000);
                renderer.drawLine(p1.x, p1.y, p2.x, p2.y, 0xFFFF0000);
                renderer.drawLine(p2.x, p2.y, p0.x, p0.y, 0xFFFF0000);

                renderer.drawTriangle(p0, p1, p2, obj.color);
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