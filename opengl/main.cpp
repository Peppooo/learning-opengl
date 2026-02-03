#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0); \n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 vertColor;"
"void main() {\n"
"FragColor = vertColor;\n"
"}\0";


#define WIN_SIZE 1024,1024

void framebuffer_size_callback(GLFWwindow* window,int w,int h) {
    glViewport(0,0,w,h);
}

void process_input(GLFWwindow* window) {
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window,true);
}

#define CHECK_SHADER_COMPILE_ERROR(idx) { int  success; char infoLog[512]; glGetShaderiv(idx,GL_COMPILE_STATUS,&success); if(!success) { glGetShaderInfoLog(idx,512,NULL,infoLog); printf("shader compilation failed line: %d\n%s\n",__LINE__,infoLog); } } // checks for errors

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(WIN_SIZE,"opengl sborra",0,0);

    if(window == 0) printf("failed to create window\n");

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) printf("failed to initialize glad\n");

    glViewport(0,0,WIN_SIZE);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    float vertices1[] = {
     0.5f,  0.5f, 0.0f,  // top right   0
     0.5f, -0.5f, 0.0f,  // bottom right1
    -0.5f, -0.5f, 0.0f,  // bottom left 2
    -0.5f,  0.5f, 0.0f   // top left    3
    };

    unsigned int indecies1[] = {
        3,2,1,
        1,3,0
    }; // cube 1

    unsigned int VAO = 0;
    glGenVertexArrays(1,&VAO); // generate vertex array object (contains how to read verticies from vbo)
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1,&VBO); // generate vertex buffer object (contains verticies)
    

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW); // sends verticies data to gpu as static draw since here we need fast reads but not necessariamente fast writes

    unsigned int EBO = 0; // generate element buffer object (defines what elements of the VBO each primitive gets)

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indecies1),indecies1,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader = 0;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,0);
    glCompileShader(vertexShader); // compiles vertex shader

    CHECK_SHADER_COMPILE_ERROR(vertexShader);

    unsigned int fragmentShader = 0;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragShaderSource,0);
    glCompileShader(fragmentShader);

    CHECK_SHADER_COMPILE_ERROR(fragmentShader);

    unsigned int shaderProgram = 0;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);


    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while(!glfwWindowShouldClose(window)) {
        process_input(window);
           
        glClearColor(1,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        float greenChannel = sin(glfwGetTime()) * 0.5f + 0.5f;

        int vertColorLoc = glGetUniformLocation(shaderProgram,"vertColor");
        glUniform4f(vertColorLoc,1.0f,greenChannel,1.0f,1.0f);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}