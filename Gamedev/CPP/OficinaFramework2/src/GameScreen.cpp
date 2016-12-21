#include "GameScreen.hpp"
#include <oficina2/benchmark.hpp>
using namespace oficina;

void GameScreen::init() {
    vao.init();
    vbo.init();
    ebo.init();
    ofSetVSync(true);
}

void GameScreen::load() {
    vao.bind();

    float vertices[] = {
        //  Vertices         Colors              Texcoords
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f
    };

    vbo.setData(sizeof(vertices), vertices, ofBufferStaticDraw);

    shaderProgram = oficina::ofLoadDefaultShaderProgram();
    shaderProgram.use();

    

    attrPosition = shaderProgram.getAttributeLocation("position");
    attrColor    = shaderProgram.getAttributeLocation("color");
    attrTexcoord = shaderProgram.getAttributeLocation("texcoord");

    attrPosition.enable();
    attrColor.enable();
    attrTexcoord.enable();

    attrPosition.setProps(3, ofDataFloat, 8 * sizeof(float));
    attrColor.setProps(3, ofDataFloat, 8 * sizeof(float));
    attrTexcoord.setProps(2, ofDataFloat, 8 * sizeof(float));

    attrPosition.bindVertexArrayData(0);
    attrColor.bindVertexArrayData((void*)(3 * sizeof(float)));
    attrTexcoord.bindVertexArrayData((void*)(6 * sizeof(float)));

    uniMVP = shaderProgram.getUniformLocation("mvp");
    uniTex = shaderProgram.getUniformLocation("tex");

    kitten = ofTexturePool::load("sample.png");
    uniTex.set(0);

    unsigned int elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    ebo.setData(sizeof(elements), elements, ofBufferStaticDraw);
    ebo.setProps(6, ofDataUInt);


    view = glm::lookAt(
            glm::vec3(1.2f, 1.2f, -1.2f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, -1.0f));
    proj = glm::perspective(
            glm::radians(45.0f),
            1280.0f / 720.0f,
            1.0f, 10.0f);
    uniMVP.set(proj * view * model);

    ofBenchmarkStart(2.0f);
}

void GameScreen::unload() {
    ofBenchmarkEnd();
    ofTexturePool::unload(kitten);
    vbo.unload();
}

void GameScreen::update(float dt) {
    model = glm::rotate(model,
         glm::radians(90.0f) * dt,
            glm::vec3(0.0f, 0.0f, 1.0f));
    uniMVP.set(proj * view * model);
    ofBenchmarkUpdateCall();
}

void GameScreen::draw() {
    vao.bind();
    kitten.bind();
    ebo.draw(ofTriangles);
}
