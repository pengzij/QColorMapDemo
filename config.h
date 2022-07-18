#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDir>
#include <memory>
#include <QDebug>
#include <QException>
#include <sstream>
#include <unordered_map>

using namespace std;


class Config
{
public:
    //singleton mode to get config class
    static Config& getInstance()
    {
        static Config* singleton = new Config();
        return *singleton;
    }
    int getConfigNum(const string &str);
    const vector<pair<int, int>>& getmap() const
    {
        return map_xy;
    }


    ~Config();
private:
    Config();
    bool init(ifstream& );
    void readMap(ifstream& );


    // save key-value in config.txt
    unordered_map<string, int> configmap;
    vector<pair<int, int>> map_xy;
};

#endif // CONFIG_H
