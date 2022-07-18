#include "config.h"

Config::Config()
{
    shared_ptr<QDir> folderSp(new QDir( QDir::currentPath() ));
    QString configPath = folderSp->absolutePath();
    configPath += "/config.txt";
//    shared_ptr<QDir> configPathSp(new QDir(configPath));
//    qDebug() << configPath << endl;

//    if(!configPathSp->exists())
//    {
//        cout << configPathSp->exists() << endl;
//        qDebug() << configPathSp->absolutePath() << endl;
//        QString errinfo = "config.txt don't exist in current path";
//        qDebug() << errinfo << endl;
//        throw QException();
//    }
    ifstream configIf(configPath.toStdString().data());
    if(!configIf)
    {
        qDebug() << "config.txt open error" << endl;
        throw QException();
    }
    init(configIf);
    QString MapPath = folderSp->absolutePath();
    MapPath += "/map.txt";
    ifstream MapIf(MapPath.toStdString().data());
    if(!MapIf)
    {
        qDebug() << "map.txt open error" << endl;
        throw QException();
    }
    readMap(MapIf);
}

void Config::readMap(ifstream &MapIf)
{
    string Alinestr;
    while(getline(MapIf, Alinestr))
    {
        stringstream sin(Alinestr);
        string strx, stry;
        sin >> strx >> stry;
        cout << strx << stry << endl;
        if(strx.empty() || stry.empty()) break;
        int x = stoi(strx), y = stoi(stry);
        if(x < 0 || x > configmap["width"] || y < 0 || y > configmap["height"]) continue;
        try
        {
            map_xy.push_back({stoi(strx), stoi(stry)});
        }
        catch(...)
        {
            qDebug() << "pos in map.txt error" << endl;
            throw QException();
        }
    }
}

bool Config::init(ifstream &configIf)
{
    string Alinestr;
    while(getline(configIf, Alinestr))
    {
        if(Alinestr.front() == '#') continue;
        stringstream out(Alinestr);
        string configkey, configvalue;
        out >> configkey;
        //ignore "="
        out >> configvalue;

        out >> configvalue;
        cout << configkey << " " << configvalue << endl;
        configmap.insert({configkey, stoi(configvalue)});
    }
}

int Config::getConfigNum(const string &str)
{
    if(configmap.count(str))
    {
        return configmap[str];
    }
    return -1;
}
