#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>
#include <OGRE/OgreVector3.h>

class Split{
private:
static bool space(char c){
    return std::isspace(c);
}
 
static bool notspace(char c){
    return !std::isspace(c);
}
public:
//break a sentence into words
static std::vector<Ogre::Real> split(const std::string& s){
    typedef std::string::const_iterator iter;
    std::vector<Ogre::Real> ret;
    iter i = s.begin();
    while(i!=s.end()){
        i = std::find_if(i, s.end(), notspace); // find the beginning of a word
        iter j= std::find_if(i, s.end(), space); // find the end of the same word
        if(i!=s.end()){
			ret.push_back(std::atof(std::string(i, j).c_str())); //insert the word into vector
            i = j; // repeat 1,2,3 on the rest of the line.
        }
    }
    return ret;
}
};
