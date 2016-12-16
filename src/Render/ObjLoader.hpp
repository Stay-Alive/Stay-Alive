#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../Model/RawModel.hpp"
#include "Loader.hpp"
#include <vector>
#include <string>

using namespace std;

class ObjLoader
{
public:
    static RawModel LoadModel(const string& fileName, Loader& loader);
private:
    static void Split(const string& str, char delim, vector<string>& tokens);
};


#endif
