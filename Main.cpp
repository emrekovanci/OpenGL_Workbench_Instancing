#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <Core/Vertex.hpp>
#include <Core/Shader.hpp>
#include <Core/Camera.hpp>
#include <Core/FrameRateCounter.hpp>

#include <Math/Graph.hpp>

#include <Graphics/PostProcess.hpp>

constexpr unsigned int AntiAliasingLevel = 4;
constexpr float CameraDistance = 3.0f;

std::vector<glm::mat4> ModelMatrices;
Graph graph(&ModelMatrices);

void updateModelBuffer(GLuint modelBuffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * ModelMatrices.size(), ModelMatrices.data(), GL_DYNAMIC_DRAW);
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
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    //settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode(800, 600), "Chimpey!", sf::Style::Default, settings);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction)))
    {
        std::cout << "Failed to initialize GLAD!\n";
        return EXIT_FAILURE;
    }

    std::cout << "Vendor:" << glGetString(GL_VENDOR) << '\n';
    std::cout << "Version:" << glGetString(GL_VERSION) << '\n';
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << '\n';
    std::cout << "-----------\n";

    Camera camera;

    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(window.getSize().x) / window.getSize().y,
        0.1f,
        100.0f
    );

    // blinn-pong shader
    Shader litShader("resources/shaders/lit/vertex.glsl", "resources/shaders/lit/fragment.glsl");

    // post-process shader
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
    glBindVertexArray(0);

    GLuint modelBuffer;
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * ModelMatrices.size(), ModelMatrices.data(), GL_DYNAMIC_DRAW);
    glBindVertexArray(vao);
    GLuint modelMatrixLocation = litShader.getAttribLocation("instanceMatrix");
    for (int i = 0; i < 4; ++i)
    {
        const int offset = i + modelMatrixLocation;

        glEnableVertexAttribArray(offset);
        glVertexAttribPointer(offset, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i *  sizeof(glm::vec4)));
        glVertexAttribDivisor(offset, 1);
    }
    glBindVertexArray(0);

    sf::Clock clock;
    float previousTime = clock.getElapsedTime().asSeconds();
    float currentTime = 0.0f;
    FrameRateCounter fpsCounter(FrameRateCounter::Display::FPS);

    // glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                postProcess.setSize(event.size.width, event.size.height);
            }
        }

        // timing
        currentTime = clock.getElapsedTime().asSeconds();
        const float deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        // simulate
        fpsCounter.update(deltaTime);
        graph.update(deltaTime);
        updateModelBuffer(modelBuffer);

        // camera
        camera.Position = glm::vec3(glm::cos(currentTime), 1.0f, glm::sin(currentTime)) * CameraDistance;

        litShader.use();
        litShader.setVec3("LightPosition", glm::vec3(0.0f, 1.5f, 0.0f));
        litShader.setVec3("ViewPosition", camera.Position);
        litShader.setMat4("View", camera.getViewMatrix());
        litShader.setMat4("Projection", projectionMatrix);

        postProcess.begin();
        render(vertices, vao);
        postProcess.end();
        postProcess.render();

        std::cout << '\r' << fpsCounter.getUnit() << ':' << fpsCounter.getValue();

        window.display();
    }

    return EXIT_SUCCESS;
}