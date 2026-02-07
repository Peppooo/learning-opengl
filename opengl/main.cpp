#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <iostream>

#include "stb_image.h"
#include "obj_load.h"
#include "shader.h"

using namespace glm;


void framebuffer_size_callback(GLFWwindow* window,int w,int h) {
    glViewport(0,0,w,h);
}

glm::vec3 origin; 

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if(key == GLFW_KEY_W) {
        origin.z += 0.01;
    }
}


void process_input(GLFWwindow* window) {
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window,true);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024,1024,"opengl sborra",0,0);

    if(window == 0) printf("failed to create window\n");

    glfwMakeContextCurrent(window); 

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) printf("failed to initialize glad\n");
    glViewport(0,0,1024,1024);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetKeyCallback(window,key_callback);
    
    // vec3 vertice position, vec2 texture coordinate, ...
    /*float vertices1[] = {
    -0.5f,-0.5f, 0.0f, 0.0f,0.0f, // bottom left
     0.5f,-0.5f, 0.0f, 1.0f,0.0f, // bottom right
    -0.5f, 0.5f, 0.0f, 0.0f,1.0f, // top left
     0.5f, 0.5f, 0.0f, 1.0f,1.0f  // top right
    };

    unsigned int indecies[] = {
        0,1,2,
        1,3,2
    }; // cube face*/

    //float* verticies = new float[1000]; size_t verticiesCount = 0;
    //unsigned int* indecies = new unsigned int[1000]; size_t indeciesCount = 0;

    /*float verticies[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };*/



    vector<Vert> verticies;
    load_obj("oak.obj",verticies);
    
    glEnable(GL_DEPTH_TEST);

    unsigned int VAO = 0;
    glGenVertexArrays(1,&VAO); // generate vertex array object (contains how to read verticies from vbo)
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1,&VBO); // generate vertex buffer object (contains verticies)
    

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,verticies.size()*sizeof(Vert),verticies.data(),GL_STATIC_DRAW); // sends verticies data to gpu as static draw since here we need fast reads but not necessariamente fast writes


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader shader("shade.vert","shade.frag");

    unsigned int textures[2];

    glGenTextures(2,textures);

    glBindTexture(GL_TEXTURE_2D,textures[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    int width,height,channels;
    unsigned char* texData = stbi_load("oak.png",&width,&height,&channels,0);
    if(!texData) printf("failed to load texture image\n");

    cout << "channels: " << channels << endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,texData);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texData);

    /*glBindTexture(GL_TEXTURE_2D,textures[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


    texData = stbi_load("awesomeface.png",&width,&height,&channels,0);
    if(!texData) printf("failed to load texture image\n");



    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,texData);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texData);*/

    shader.use();


    int modelLoc = glGetUniformLocation(shader.ID,"model");
    int viewLoc = glGetUniformLocation(shader.ID,"view");
    int projectionLoc = glGetUniformLocation(shader.ID,"projection");

    glUniform1i(glGetUniformLocation(shader.ID,"texture1"),0);


    glm::mat4 model=glm::mat4(1.0f),view = glm::mat4(1.0f),projection = glm::mat4(1.0f);
    view = glm::translate(view,vec3(0,0,-5.0f));
    model = glm::scale(model,vec3(1,1,1));
    projection = glm::perspective(glm::radians(80.0f),1.0f/1.0f,0.1f,100.0f);
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view)); // update view
    glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

    if(glGetError() != GL_NO_ERROR) {
        cout << "gl error: " << glGetError() << endl;
    }

    while(!glfwWindowShouldClose(window)) {

        process_input(window);
        glClearColor(0.2,0.2,0.2,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model = glm::rotate(model,glm::radians(0.1f),vec3(1,0,0));
        model = glm::rotate(model,glm::radians(0.15f),vec3(0,1,0));
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textures[0]);

        glBindVertexArray(VAO);
        
        glDrawArrays(GL_TRIANGLES,0,verticies.size());
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}