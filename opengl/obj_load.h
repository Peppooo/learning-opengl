#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "utils.h"

using namespace std;

vector<string> split_string(const string& s,const char div) {
    size_t start = 0;
    size_t end = s.find(div);
    vector<string> split;
    while(end != string::npos) {
        split.push_back(s.substr(start,end - start));
        start = end + 1;
        end = s.find(div,start);
    }
    split.push_back(s.substr(start));
    return split;
}

void load_obj(const char* filename,vector<Vert>& vertices){ // 3 floats vertice,3 float normal,2 float texture
    ifstream file(filename);// here i will use fstream since its easier to use for reading line by line obj files
    vertices.clear();
    vector<Vec3> loadedVerts;

    vector<Vec3> loadedNorms;

    vector<Vec2> loadedTexC;

    if(!file) printf("Error opening file\n");
    string line;
    while(getline(file,line)) {

        vector<string> split_space = split_string(line,' ');

        if(split_space[0] == "v") {
            loadedVerts.push_back(Vec3(stof(split_space[1]),stof(split_space[2]),stof(split_space[3])));
        }
        else if(split_space[0] == "vn") {
            loadedNorms.push_back(Vec3(stof(split_space[1]),stof(split_space[2]),stof(split_space[3])));

            //printf("VN: %f %f %f\n",loadedNorms[countLoadN * 3],loadedNorms[countLoadN * 3 + 1],loadedNorms[countLoadN * 3 + 2]);
        }
        else if(split_space[0] == "vt") {
            loadedTexC.push_back(Vec2(stof(split_space[1]),stof(split_space[2])));
        }
        else if(split_space[0] == "f") {
            for(int i = 1; i < 4; i++) {
                vector<string> split_indexs = split_string(split_space[i],'/');
                // format: v/vt/vn
                int vIdx = (stoi(split_indexs[0])-1);
                int tIdx = (stoi(split_indexs[1])-1);
                int nIdx = (stoi(split_indexs[2])-1);

                vertices.push_back(Vert(
                    loadedVerts[vIdx],
                    loadedNorms[nIdx],
                    loadedTexC[tIdx]
                ));

                

                //indecies[indeciesCount]=(stoul(split_indexs[0]) - 1);
                //printf("index: %ul\n",indecies[indeciesCount]);
                //indeciesCount++;
            }
        }
    }

    file.close();
}