#ifndef UDPCONNECT_H
#define UDPCONNECT_H
#include <QUdpSocket>
#include <string>
#include <QDebug>
#include <queue>
#include <iostream>
#include <fstream>
#include <memory>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QMutex>
#include <QFile>
#include <QDir>
#include <windows.h>
#include "CirQueue.h"
#include "config.h"
using namespace std;

class UDP : public QObject
{
    Q_OBJECT
public:
    //UDP() = delete;
    UDP(int _MaxChannelNum = 0, QString ip = "192.168.0.119",int udp_ctl = 0, int port = 4010, shared_ptr<CirQueue<float>> sp = nullptr);
    //UDP(int _MaxChannelNum = 0, QString ip = "192.168.0.119",int udp_ctl = 0, int port = 4010, vector<float> &vec);
    UDP(QString ip = "192.168.0.119",int udp_ctl = 0, int port = 4010);
    UDP(QString ip, int port);
    ~UDP();


public:
    queue<char> charQue;


private slots:
    void readWLDataSlot();
    void readSPDataSlot();
    void restoreSPData();
    void restoreWLData();
    void flashFileName();
    void flashFileName_wave();
    void reSend();
    void exit();

signals:
    void sendWriteAble();
    void sendWriteAble_wave();
    void sendUpdataHeatmap();
    void sendReinit();
    void sendExit();

private:
    void send(const QByteArray&);
    float getWave(const char&, const char&);
    inline void setBaseWavelen();
private:   
    const QString IP = "192.168.0.119";
    const int PORT = 4010;
    const QByteArray RDSPECTRUM = "0116"; //0x0116, read spectrum
    const QByteArray DISCONNECT = "10a00";//0x010a00
    const QByteArray STARTCONNECT = "10a55";//0x010a55 read wavelength
    const QByteArray COMMAND[2] = {RDSPECTRUM, STARTCONNECT};

    shared_ptr<QUdpSocket> pSocket;

    QByteArray writeBuffer;
    //QByteArray buffer;

    shared_ptr<CirQueue<QByteArray>> OriDataQueSp;
    shared_ptr<CirQueue<float>> WaveDataSp, HeatmapDataSp;
    shared_ptr<CirQueue<pair<int, int>>> MessagequeSp;
    vector<QByteArray> SpOriData;
    vector<float> SpData;

    shared_ptr<QTimer> timersp;
    shared_ptr<QTimer> waitTimersp;
    shared_ptr<QTimer> bombTimersp;

    int curChannelNum;//0 ~ n
    int recivedPacNum;
    int maxChannelNum;//0 ~ n

    QMutex writeLock;

    vector<QString> saveFile;
    vector<ofstream> of;

    bool isSave;

    vector<float> basewave;
};




#endif // UDPCONNECT_H
