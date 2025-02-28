#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "Transform.h"

class Scene
{
public:
    Scene(OpenGLWindow* window);
    ~Scene();

    bool init();
    void shutdown();
    void render(float dt);
    void update(float dt);
    OpenGLWindow* getWindow();

    void initializeCube();
    void drawCube(float dt);

    void initializeRobot();
    void initializeLightSource();
    void renderRobot();
    void updateLighting();
    void makeLightSourceVisible();

    void onKey(Key key, Action action, Modifier modifier);
    void onMouseMove(MousePosition mouseposition);
    void onMouseButton(MouseButton button, Action action, Modifier modifier);
    void onMouseScroll(double xscroll, double yscroll);
    void onFrameBufferResize(int width, int height);


private:
    OpenGLWindow* m_window;
    AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID, iboID, lightVBOID, lightVAOID, lightIBOID;
    Transform transformCube;
    Transform transformRobot;
    Transform transformTorso;
    Transform transformHead;
    Transform transformLeftUpperArm, transformRightUpperArm;
    Transform transformLeftShoulder, transformRightShoulder;
    Transform transformLeftLowerArm, transformRightLowerArm;
    Transform transformLeftElbow, transformRightElbow;
    Transform transformLeftLeg, transformRightLeg;
    Transform transformLeftHip, transformRightHip;

    glm::vec3 leftShoulder = glm::vec3(-0.6f, 0.5f, 0.25f);
    glm::vec3 rightShoulder = glm::vec3(0.6f, 0.5f, 0.25f);

    glm::vec3 leftElbow = glm::vec3(-1.0f, -0.8f, 0.1f);
    glm::vec3 rightElbow = glm::vec3(1.0f, -0.8f, 0.1f);

    glm::vec3 leftHip = glm::vec3(-0.4, -0.3f, 0.0f);
    glm::vec3 rightHip = glm::vec3(0.4f, -0.3f,0.0f);
};