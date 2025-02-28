#include "Scene.h"
#include <AssetManager.h>
#include "Cube.h"
#include "CubeWithNormals.h"

Scene::Scene(OpenGLWindow * window) :
        m_window(window)
{
    assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
    try
    {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        //setup light source
        glm::vec3 lightStartPos(0.0f, 2.0f, 2.0f);
        m_shader->setUniform("lightPos", lightStartPos);
        m_shader->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

        //initializeCube(); //aufgabe 2.2 (change vertex.glsl when trying)

        //Generate and activate VBO and upload data
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        //Generate and activate vao
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        //describe VBO in the VAO
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //the position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //the normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//color
        glEnableVertexAttribArray(2);

        //Setup IBO
        glGenBuffers(1,&iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        initializeLightSource();

        initializeRobot();

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        //unbind vao
        glBindVertexArray(0);

        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::updateLighting() {
}

void Scene::initializeLightSource() {
    //Setup vbo for light source
    glGenBuffers(1, &lightVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBOID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertWithNormals), &cubeVertWithNormals, GL_STATIC_DRAW);

    //generate and activate VAO for light
    glGenVertexArrays(1, &lightVAOID);
    glBindVertexArray(lightVAOID);

    //describe VBO in the VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float))); // Colors
    glEnableVertexAttribArray(2);
}

void Scene::initializeCube() {
    //aufgabe 2.2
    transformCube.setMatrix(glm::mat4(1.0f));
}

void Scene::initializeRobot() {
    //body
    transformTorso.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    transformTorso.setScale(glm::vec3(1.0f, 2.0f, 0.25f));

    //head
    transformHead.setPosition(glm::vec3(0.0f, 1.4f, 0.0f));
    transformHead.setScale(glm::vec3(0.5f, 0.3f, 0.5f));

    //RightArm
    // 1.0 right shoulder
    transformRightShoulder.setPosition(glm::vec3(0.6f, 0.5f, -0.25f));
    // 1.1 upper right arm
    transformRightUpperArm.setPosition(glm::vec3(0.7f, 0.25f, 0.2f));
    transformRightUpperArm.setScale(glm::vec3(0.2f, 0.4f, 0.2f));
    //1.2 right elbow
    transformRightElbow.setPosition(glm::vec3(0.7f, 0.4f, 0.0));
    //1.3 right bottom arm
    transformRightLowerArm.setPosition(glm::vec3(0.0f, -1.0f, 0.2f));
    transformRightLowerArm.setScale(glm::vec3(0.2f, 0.4f, 0.2f));

    //Left Arm
    //2.0 left shoulder
    transformLeftShoulder.setPosition(glm::vec3(0.6f, 0.5f, -0.25f));
    //2.1 upper left arm
    transformLeftUpperArm.setPosition(glm::vec3(-0.7f, 0.25f, 0.2f));
    transformLeftUpperArm.setScale(glm::vec3(0.2f, 0.4f, 0.2f));
    //2.2 left elbow
    transformLeftElbow.setPosition(glm::vec3(-0.7f, -0.4f, 0.0));
    //2.3 lower left arm
    transformLeftLowerArm.setPosition(glm::vec3(0.0f, -1.0f, 0.2f));
    transformLeftLowerArm.setScale(glm::vec3(0.2f, 0.4f, 0.2f));

    //Leg
    //left hip
    transformLeftHip.setPosition(glm::vec3(-0.4f, -1.5f, 0.0f));
    //left leg
    transformLeftLeg.setPosition(glm::vec3(-0.3f, -0.8f, 0.0f));
    transformLeftLeg.setScale(glm::vec3(0.45f, 0.45f, 0.2f));

    //Leg
    //right hip
    transformRightHip.setPosition(glm::vec3(0.4f, -1.5f, 0.0f));
    // right leg
    transformRightLeg.setPosition(glm::vec3(0.3f, -0.8f, 0.0f));
    transformRightLeg.setScale(glm::vec3(0.45f, 0.45f, 0.2f));
}

void Scene::renderRobot(){
    //camera properties
    glm::vec3 cameraPosition(3.0f, 3.0f, 5.0f); //camera position
    glm::vec3 targetPosition(0.0f, 0.0f, 0.0f); //looking at the origin
    glm::vec3 upVector(0.0f, 1.0f, 0.0f);

    //calculate view matrix
    glm::mat4 view = glm::lookAt(cameraPosition, targetPosition, upVector);
    //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    //pass matrices to shader
    m_shader->setUniform("view", view, false);
    m_shader->setUniform("projection", projection, false);

    float timeValue = glfwGetTime();
    float speed = 5.5f;
    float maxAngle = 2.0f;         // maximum rotation angle
    float swingAngle = maxAngle * glm::sin(timeValue * speed); // animate between -maxAngle and +maxAngle

    float red = 1.0f * glm::sin(timeValue);  // Oscillates between 0 and 1
    float green = 1.0f * glm::sin(timeValue); // Faster oscillation
    float blue = 1.0f * glm::cos(timeValue + 1); // Oscillates between 0 and 1

    glm::vec3 rainbowColor = glm::vec3(red, green, blue);

    // rotation for 3d look
    glm::mat4 robotRotation = glm::rotate(glm::mat4(1), 0.0f/*glm::sin(timeValue * 2.0f)*/, glm::vec3(0, 1, 0));

    // Draw body
    //m_shader->setUniform("color", rainbowColor);
    glm::mat4 torso = transformTorso.getMatrix() * robotRotation;
    m_shader->setUniform("model", torso, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //Body
    //m_shader->setUniform("color", glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 head = transformHead.getMatrix() * torso;
    m_shader->setUniform("model", head, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //3. Left arm
    //3.1 Top left arm
    //m_shader->setUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
    float armSwingAngle = maxAngle * glm::sin(timeValue * speed + glm::pi<float>()); // opposite of legs
    glm::quat leftArmRotation = glm::angleAxis(glm::radians(armSwingAngle), glm::vec3(1, 0, 0));
    glm::mat4 upperLeftArm = torso * transformLeftUpperArm.getMatrix();
    transformLeftUpperArm.rotateAroundPoint(leftShoulder, leftArmRotation);
    m_shader->setUniform("model", upperLeftArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // 3.2 Bottom left arm
    //m_shader->setUniform("color", glm::vec3(0.5f, 0.5f, 0.0f));
    float maxLowerAngle = 0.8f;
    float delayFactor = 0.05f;
    float lowerArmSwingAngle = maxLowerAngle * glm::cos(timeValue * speed); // add some delay
    glm::quat leftArmSwing = glm::angleAxis(glm::radians(lowerArmSwingAngle), glm::vec3(1, 0, 0));
    glm::mat4 lowerLeftArm = upperLeftArm * transformLeftLowerArm.getMatrix();
    transformLeftLowerArm.rotateAroundPoint(leftElbow, leftArmSwing);
    lowerLeftArm = glm::scale(lowerLeftArm, glm::vec3(5.0, 2.0, 3.0));
    m_shader->setUniform("model", lowerLeftArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //4. Right arm
    //4.1 upper Right arm
    float rightArmSwing = maxAngle * glm::sin(timeValue * speed);
    //m_shader->setUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rightArmRotation = glm::angleAxis(glm::radians(rightArmSwing), glm::vec3(1, 0, 0));
    glm::mat4 upperRightArm = torso * transformRightUpperArm.getMatrix();
    transformRightUpperArm.rotateAroundPoint(rightShoulder, rightArmRotation);
    m_shader->setUniform("model", upperRightArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //4.2 draw bottom right arm
    float lowerRightArmSwingAngle = maxLowerAngle * glm::cos(timeValue * speed);
    //m_shader->setUniform("color", glm::vec3(0.5f, 0.5f, 0.0f));
    glm::quat LowerRight = glm::angleAxis(glm::radians(lowerArmSwingAngle), glm::vec3(1, 0, 0));
    glm::mat4 lowerRightArm = upperRightArm * transformRightLowerArm.getMatrix();;
    transformRightLowerArm.rotateAroundPoint(rightElbow, rightArmRotation);
    lowerRightArm = glm::scale(lowerRightArm, glm::vec3(5.0, 2.0, 3.0));
    m_shader->setUniform("model", lowerRightArm, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    //5. Legs
    // Draw the left leg
    //m_shader->setUniform("color", glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 leftLeg = torso * transformLeftLeg.getMatrix();
    glm::quat legRotation = glm::angleAxis(glm::radians(swingAngle), glm::vec3(1, 0, 0));
    transformLeftLeg.rotateAroundPoint(leftHip, legRotation);
    leftLeg = glm::scale(leftLeg, glm::vec3(0.8, 1.0, 1.0));
    m_shader->setUniform("model", leftLeg, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // Draw the right leg
    //m_shader->setUniform("color", glm::vec3(0.5f, 0.5f, 0.5f));
    float rightSwingAngle = maxAngle * glm::sin(timeValue *  speed + glm::pi<float>()); // opposite of left leg swing
    glm::mat4 rightLeg = torso * transformRightLeg.getMatrix();
    glm::quat rightLegRotation = glm::angleAxis(glm::radians(rightSwingAngle), glm::vec3(1, 0, 0));
    transformRightLeg.rotateAroundPoint(rightHip, rightLegRotation);
    rightLeg = glm::scale(rightLeg, glm::vec3(0.8, 1.0, 1.0));
    m_shader->setUniform("model", rightLeg, false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void Scene::render(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Dark gray background

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);

    // Enable face culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Use shader and bind VAO
    m_shader->use();
    glBindVertexArray(vaoID);

    // Render the robot
    renderRobot();

    //If you want to see where the light source is
    makeLightSourceVisible();

    // Unbind VAO
    glBindVertexArray(0);
}

void Scene::makeLightSourceVisible() {
    //used to see where the light source is.
    glBindVertexArray(lightVAOID);

    glm::vec3 lightPos;
    float radius = 3.0f;
    float x = radius * glm::cos(glfwGetTime()); // Same calculation as update
    float z = radius * glm::sin(glfwGetTime());
    float y = 2.0f;

    lightPos = glm::vec3(x, y, z);

    glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f)); // Make light cube small

    m_shader->setUniform("model", lightModel, false);
    m_shader->setUniform("color", glm::vec3(1.0f, 1.0f, 0.0f));
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);*/
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Scene::update(float dt)
{
    static float timeAccumulator = 0.0f;
    timeAccumulator += dt;

    //light has a circular movement
    float radius = 3.0f;
    float x = radius * glm::cos(timeAccumulator);
    float z = radius * glm::sin(timeAccumulator);
    float y = 2.0f;

    glm::vec3 movingLightPos(x, y, z);

    //update light position in shader
    m_shader->use();
    m_shader->setUniform("lightPos", movingLightPos);
}

OpenGLWindow * Scene::getWindow()
{
    return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}