/*====================================================================
 * Filename:      mainwindow.cpp
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:42:06 2013
 * Modified at:   Tue Jul  9 22:10:59 2013
 * Description:   
 *==================================================================*/
#include "mainwindow.h"
#include <QPainter>
#include <QRadialGradient>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>

/*
 * 构造函数
 */
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    init();
    udpinit();
    wsp = make_shared<HotPlot>(nullptr, 100, waveDataqueSp);
    wsp->resize(500, 400);
    wsp->show();
    //connect(udpsocketSp.get(), &UDP::sendUpdataHeatmap, wsp.get(), &HotPlot::handleWavelen, Qt::DirectConnection);
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    this->mapvec = Config::getInstance().getmap();
    this->multiCnt = Config::getInstance().getConfigNum("multiCnt");
    this->base = Config::getInstance().getConfigNum("base");
    waveDataqueSp = make_shared<CirQueue<float>>(100 * Config::getInstance().getConfigNum("CHnum") * 60 * 1000);
}


void MainWindow::udpinit()
{
    //only channel 1 is useful;
    int channel = Config::getInstance().getConfigNum("CHnum");
    int mode = Config::getInstance().getConfigNum("mode");
    cout << "mode = " << mode << endl;
    udpsocketSp = std::make_shared<UDP>(channel, "192.168.0.119", mode, 4010, waveDataqueSp);
}

//void MainWindow::addpoint_map()
//{
//    cout << "xx" << endl;
//    for(int i = 0; i < mapvec.size(); i++)
//    {
//        if(waveDataqueSp->isEmpty()) break;
//        cout << "waveDataqueSp.size() = " << waveDataqueSp->size() << endl;
//        auto m = mapvec[i];
//        cout << "data = " << waveDataqueSp->front() << endl;
//        addpoint_xy(m.first, m.second, abs(waveDataqueSp->front() - lastdata[i]));
//        //lastdata[i] = waveDataqueSp->front();
//        lastdata[i] = waveDataqueSp->front();
//        waveDataqueSp->pop();
//        cout << m.first << m.second << endl;
//    }

//    this->update();
//}

//* painta a point(x, y) to add a color point in map
// *
// */
//void MainWindow::addpoint_xy(const int &x, const int &y, float val)
//{
//   // mapper_->addPoint(x, y, multiVal(val));
//    //this->update();
//}

//int MainWindow::multiVal(const float &n)
//{
//    return (n - base) * multiCnt;
//}


















