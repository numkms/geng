#ifndef SCORE_SERVICE_H
#define SCORE_SERVICE_H
#include "ScoreService.h"
#include <map>
#include <string>
#include <fstream>
#include "../../Constants.h"

class ScoreService
{
private:
    /* data */
public:
    static void AddScoreResult(std::string name, int score) {
        std::ofstream out;

        out.open(SCORE_FILE_PATH, std::ios::app);
        out << name << std::endl;
        out << std::to_string(score) << std::endl;;
        out.close();
    };
    
    static std::vector<std::pair<std::string, int> > GetResults() {
        std::fstream file;
        file.open(SCORE_FILE_PATH);
        std::string str;
        
        bool isScore = false;

        std::map<std::string, int> result;
        
        std::string name;
        int score;

        while(std::getline(file, str)) {
            if(isScore) {
                score = atoi(str.c_str());
                if(result.find(name) != result.end()) {
                    if(result[name] < score) {
                        result[name] = score;    
                    }
                } else {
                    result[name] = score;
                }
                
                isScore = false;
            } else {
                name = str;
                isScore = true;
            }
        }

        file.close();
        std::vector<std::pair<std::string, int> > A; 
        for (auto& it : result) { 
            A.push_back(it); 
        } 
        std::sort(A.begin(), A.end(), [](std::pair<std::string, int>& a, std::pair<std::string, int>& b) {
            return a.second > b.second; 
        }); 
        return A;
    };
    

};



#endif