#pragma once
#include <fstream>
#include <vector>
#include <glad/glad.h>

using namespace std;

#define CHECK_SHADER_COMPILE_ERROR(idx) { int  success; char infoLog[512]; glGetShaderiv(idx,GL_COMPILE_STATUS,&success); if(!success) { glGetShaderInfoLog(idx,512,NULL,infoLog); printf("shader compilation failed line: %d\n%s\n",__LINE__,infoLog); } } // checks for errors

class Shader {
public:
	unsigned int ID = 0; // program ID
	Shader(const char* vertex_path,const char* fragment_path): ID(0) {
        ifstream vertF(vertex_path,ios::binary | ios::ate),fragF(fragment_path,ios::binary|ios::ate);
        if(!vertF || !fragF) throw std::runtime_error("Failed to open shader source file");

        int vSize = vertF.tellg(),fSize = fragF.tellg();
        vertF.seekg(0,ios::beg);
        fragF.seekg(0,ios::beg);

        char *vBuf = new char[vSize+1],*fBuf = new char[fSize+1];
        vertF.read(vBuf,vSize);
        fragF.read(fBuf,fSize);
        vBuf[vSize] = '\0';
        fBuf[fSize] = '\0';
        
        
        unsigned int vertShader=0,fragShader = 0;
        
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader,1,&vBuf,0);
        glCompileShader(vertShader);

        CHECK_SHADER_COMPILE_ERROR(vertShader);

        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader,1,&fBuf,0);
        glCompileShader(fragShader);

        CHECK_SHADER_COMPILE_ERROR(fragShader);

        ID = glCreateProgram();
        glAttachShader(ID,vertShader);
        glAttachShader(ID,fragShader);
        glLinkProgram(ID);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        delete[] vBuf,fBuf; // free code memory
    }
    void use() {
        glUseProgram(ID);
    }
};