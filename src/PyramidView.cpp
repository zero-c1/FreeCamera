#include "PyramidView.hpp"
#include <GLFW/glfw3.h>
#include <math.h>

#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void MyApp::PyramidView::init()
{
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TRN_INDICES), TRN_INDICES, GL_STATIC_DRAW);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TRN_VERTICES), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(TRN_VERTICES), TRN_VERTICES);
    // glBufferSubData(GL_ARRAY_BUFFER, sizeof(VERTICES), sizeof(TEXTURE_COORDS), TEXTURE_COORDS);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(VERTICES)));
    // glEnableVertexAttribArray(1);

    mShader.init("shaders/vertex.glsl", "shaders/fragment.glsl");
    mShader.use();
	glEnable(GL_DEPTH_TEST);

    mCamera.setCameraView(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    mModel = glm::mat4(1.0f);
    // model = glm::rotate(glm::mat4(1.0f), glfw_time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
    glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "model"), 1, GL_FALSE, glm::value_ptr(mModel));

    mView = mCamera.getViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "view"), 1, GL_FALSE, glm::value_ptr(mView));
    
    mProjection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(mProjection));
}

void genTableRow(const glm::vec3& vec, const char* name)
{
    for (int column = 0; column < 3; column++)
    {
        ImGui::TableSetColumnIndex(column);
        ImGui::Text("%.3f", vec[column]);
    }
    ImGui::TableSetColumnIndex(3);
    ImGui::Text(name);
}

void MyApp::PyramidView::renderGUI()
{
    ImGui::Begin("Control");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    if (ImGui::Button("Reset view"))
    {
        mCamera.setCameraView(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "view"), 1, GL_FALSE, glm::value_ptr(mCamera.getViewMatrix()));
    }
    if (ImGui::BeginTable("table1", 4))
    {
        ImGui::TableNextRow();
        genTableRow(mCamera.getEye(), "eye");
        ImGui::TableNextRow();
        genTableRow(mCamera.getRightVector(), "right");
        ImGui::TableNextRow();
        genTableRow(mCamera.getUpVector(), "up");

        ImGui::EndTable();
    }

    ImGui::End();
}


void MyApp::PyramidView::render()
{
    glBindVertexArray(mVAO);
    float glfw_time {static_cast<float>(glfwGetTime())};
    glUniform1f(glGetUniformLocation(mShader.getHandle(), "onTime"), glfw_time);
    
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
}

void MyApp::PyramidView::update()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.NavActive) return;
    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left, 1.0f))
    {
        mCamera.arcballRotate(io.MouseDelta.x * 0.5f, io.MouseDelta.y * 0.5f);
        glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "view"), 1, GL_FALSE, glm::value_ptr(mCamera.getViewMatrix()));
    }
    else if (ImGui::IsMouseDragging(ImGuiMouseButton_Right, 1.0f))
    {
        mCamera.pan(io.MouseDelta.x * 0.01f, io.MouseDelta.y * 0.01f);
        glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "view"), 1, GL_FALSE, glm::value_ptr(mCamera.getViewMatrix()));
    }
    else if (ImGui::IsKeyDown(ImGuiKey_MouseWheelY))
    {
        mCamera.scale(-io.MouseWheel * 0.1);
        glUniformMatrix4fv(glGetUniformLocation(mShader.getHandle(), "view"), 1, GL_FALSE, glm::value_ptr(mCamera.getViewMatrix()));
    }
}