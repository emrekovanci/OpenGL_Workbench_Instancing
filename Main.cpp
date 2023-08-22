#include <iostream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include <Core/VertexArray.hpp>
#include <Core/Buffers/VertexBuffer.hpp>
#include <Core/Vertex.hpp>
#include <Core/Shader.hpp>
#include <Core/Camera.hpp>
#include <Core/FrameRateCounter.hpp>

#include <Math/Graph.hpp>

#include <Graphics/PostProcess.hpp>

#include "Window.hpp"

Transforms transforms;
Graph graph(&transforms);

void displayGpuInfo()
{
    std::cout
        << "---------------------------------------------\n"
        << "Vendor:  \t" << glGetString(GL_VENDOR)   << '\n'
        << "Version: \t" << glGetString(GL_VERSION)  << '\n'
        << "Renderer:\t" << glGetString(GL_RENDERER) << '\n'
        << "---------------------------------------------\n";
}

void updateModelBuffer(const VertexBuffer& modelBuffer)
{
    modelBuffer.bind();
    modelBuffer.fill(transforms);
    modelBuffer.unbind();
}

void render(const std::vector<Vertex>& vertices, const VertexArray& vao)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vao.bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), graph.getGraphResolution());
    vao.unbind();
}

int main()
{
    Window window(1027, 768, "Chimpey!");
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction)))
    {
        std::cout << "Failed to initialize GLAD!\n";
        return EXIT_FAILURE;
    }

    displayGpuInfo();

    Camera camera;
    Shader litShader("resources/shaders/lit/vertex.glsl", "resources/shaders/lit/fragment.glsl");
    Shader postProcessShader("resources/shaders/postprocess/vertex.glsl", "resources/shaders/postprocess/fragment.glsl");
    PostProcess postProcess(postProcessShader, window.getSize().x, window.getSize().y);

    std::vector<Vertex> vertices
    {
        // back face
        { { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f,  0.0f, -1.0f } },

        // front face
        { { -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },
        { { -0.5f,  0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },
        { { -0.5f, -0.5f,  0.5f }, { 0.0f,  0.0f,  1.0f } },

        // left face
        { { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f } },
        { { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f } },

        // right face
        { { 0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f,  0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f, -0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f } },
        { { 0.5f,  0.5f,  0.5f }, { 1.0f,  0.0f,  0.0f } },

        // bottom face
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f } },
        { {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f } },
        { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f } },
        { { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f,  0.0f } },
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f,  0.0f } },

        // top face
        { { -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f } },
        { {  0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f } },
        { {  0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f } },
        { { -0.5f,  0.5f,  0.5f }, { 0.0f,  1.0f,  0.0f } },
        { { -0.5f,  0.5f, -0.5f }, { 0.0f,  1.0f,  0.0f } }
    };

    VertexArray vao;
    vao.bind();

    VertexBuffer positionBuffer(VertexBuffer::Usage::Static);
    positionBuffer.bind();
    positionBuffer.fill(vertices);

    vao.enableAttribute(0, 3, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    vao.enableAttribute(1, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    VertexBuffer modelBuffer(VertexBuffer::Usage::Dynamic);
    modelBuffer.bind();
    modelBuffer.fill(transforms);

    const GLuint modelMatrixLocation = litShader.getAttribLocation("instanceMatrix");
    for (int i = 0; i < 4; ++i)
    {
        const int offset = i + modelMatrixLocation;

        vao.enableAttribute(offset, 4, sizeof(Transform), (void*)(i * sizeof(glm::vec4)));
        vao.divisor(offset, 1);
    }

    vao.unbind();

    FrameRateCounter fpsCounter(FrameRateCounter::Display::FPS);

    window.addInitCallback([]() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    });

    // handle inputs
    window.addEventCallback([&window, &postProcess](const sf::Event& event) {
        if (event.type == sf::Event::Closed) { window.close(); }
        if (event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
            postProcess.setSize(event.size.width, event.size.height);
        }
    });

    // simulate
    window.addUpdateCallback([&fpsCounter, &modelBuffer](float deltaTime) {
        fpsCounter.update(deltaTime);
        graph.update(deltaTime);
        updateModelBuffer(modelBuffer);
    });

    // rotate camera
    window.addLifeTimeCallback([&camera](float currentTime) {
        constexpr float cameraDistance = 3.0f;
        camera.Position = glm::vec3(glm::cos(currentTime), 1.0f, glm::sin(currentTime)) * cameraDistance;
    });

    // set shader uniforms
    window.addRenderCallback([&litShader, &camera, &window]() {
        litShader.use();
        litShader.setVec3("LightPosition", glm::vec3(0.0f, 1.5f, 0.0f));
        litShader.setVec3("ViewPosition", camera.Position);
        litShader.setMat4("View", camera.getViewMatrix());
        litShader.setMat4("Projection", camera.getProjectionMatrix(window.getAspectRatio()));
    });

    // render
    window.addRenderCallback([&postProcess, &vertices, &vao, &window]() {
        postProcess.begin();
        render(vertices, vao);
        postProcess.end();
        postProcess.render(window.getMousePosition().x);
    });

    // show fps in window title
    window.addRenderCallback([&fpsCounter, &window]() {
        std::ostringstream windowTitle;
        windowTitle << "Chimpey! ";
        windowTitle << fpsCounter.getUnit() << ':' << fpsCounter.getValue();
        window.setTitle(windowTitle.str());
    });

    window.display();

    return EXIT_SUCCESS;
}