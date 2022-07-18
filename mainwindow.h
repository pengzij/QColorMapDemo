/*====================================================================
 * Filename:      mainwindow.h
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:20:02 2013
 * Modified at:   Wed Jul 10 19:12:07 2013
 * Description:   
 *==================================================================*/
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QWidget>
#include <memory>
#include "HotPlot.h"
#include "config.h"
#include "udpconnect.h"

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

class HeatMapper;
class GradientPalette;

class MainWindow : public QWidget
{
public:
    shared_ptr<HotPlot> wsp;
    shared_ptr<CirQueue<float>> waveDataqueSp;

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void addpoint_xy(const int &x, const int &y, float val);
    int multiVal(const float&);
    void udpinit();
    void init();



private slots:
    void addpoint_map();


private:
    //udp object
    std::shared_ptr<UDP> udpsocketSp;
	// 绘图对象指针
    //map vector
    vector<pair<int, int>> mapvec;
    //map lastdata
    vector<float> lastdata;
    int multiCnt;
    int base;
};

#endif /* _MAINWINDOW_H_ */

















