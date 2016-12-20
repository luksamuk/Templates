#pragma once

#include <oficina2/canvas.hpp>
#include <oficina2/render.hpp>

using namespace oficina;

class GameScreen : public oficina::ofCanvas
{
private:
    ofVertexArray   vao;
    ofVertexBuffer  vbo;
    ofElementBuffer ebo;

    ofShaderProgram shaderProgram;

    ofShaderAttribute attrPosition;
    ofShaderAttribute attrColor;
    ofShaderAttribute attrTexcoord;

    ofShaderUniform uniMVP;
    ofShaderUniform uniTex;

    ofTexture kitten;

    glm::mat4 model,
              view,
              proj;
public:
    void init();
    void load();
    void unload();
    void update(float dt);
    void draw();
};
