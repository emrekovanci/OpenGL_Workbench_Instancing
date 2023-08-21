#include <iostream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

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

void updateModelBuffer(GLuint modelBuffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Transform) * transforms.size(), transforms.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void render(const std::vector<Vertex>& vertices, GLuint vao)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), graph.getGraphResolution());
    glBindVertexArray(0);
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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    GLuint modelBuffer;
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Transform) * transforms.size(), transforms.data(), GL_DYNAMIC_DRAW);

    const GLuint modelMatrixLocation = litShader.getAttribLocation("instanceMatrix");
    for (int i = 0; i < 4; ++i)
    {
        const int offset = i + modelMatrixLocation;

        glEnableVertexAttribArray(offset);
        glVertexAttribPointer(offset, 4, GL_FLOAT, GL_FALSE, sizeof(Transform), (void*)(i * sizeof(glm::vec4)));
        glVertexAttribDivisor(offset, 1);
    }
    glBindVertexArray(0);

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