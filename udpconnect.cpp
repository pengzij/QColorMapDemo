#include "udpconnect.h"


UDP::UDP(int _MaxChannelNum, QString ip, int udp_ctl, int port, shared_ptr<CirQueue<float>> sp) //default read spec
    : writeBuffer(QByteArray::fromHex(COMMAND[udp_ctl]) ),
      timersp(new QTimer),
      waitTimersp(new QTimer),
      bombTimersp(new QTimer),
      pSocket(make_shared<QUdpSocket>(this)),
      maxChannelNum(_MaxChannelNum),
      isSave(Config::getInstance().getConfigNum("save")),
      HeatmapDataSp(sp)
{
    timersp->setTimerType(Qt::PreciseTimer);
    waitTimersp->setTimerType(Qt::PreciseTimer);
    bombTimersp->setTimerType(Qt::PreciseTimer);

    if(udp_ctl == 1)
    {
        timersp->setInterval(60000);//1min定时器
        //waitTimersp->setInterval(2000);//2ms
        bombTimersp->setInterval(60000 * 60 * 4);//5h bomb

        of.resize(maxChannelNum);
        WaveDataSp = make_shared<CirQueue<float>>(100 * maxChannelNum * 60 * 1000);//100 FBG 60s * 1kHz
        MessagequeSp = make_shared<CirQueue<pair<int,int>>>(maxChannelNum * 10000); //maxChannelNum * 100

        pSocket->bind(QHostAddress::AnyIPv4, 8080);

        pSocket->writeDatagram(QByteArray::fromHex(DISCONNECT), QHostAddress(ip), port);
        //sleep(1);
        pSocket->writeDatagram(writeBuffer, QHostAddress(ip), port);

        saveFile.resize(maxChannelNum);
        of.resize(maxChannelNum);
        flashFileName_wave();

        connect(pSocket.get(), SIGNAL(readyRead()),this, SLOT(readWLDataSlot()));
        connect(this, SIGNAL(sendWriteAble_wave()), this, SLOT(restoreWLData()));
        connect(timersp.get(), SIGNAL(timeout()), this, SLOT(flashFileName_wave()) );
        connect(bombTimersp.get(), SIGNAL(timeout()), this, SLOT(exit()) );
        timersp->start();
        bombTimersp->start();
        cout << "Init Read Wave Lenght" << endl;
    }
    else if(udp_ctl == 0)
    {
        timersp->setInterval(60000);//1min定时器
        waitTimersp->setInterval(2000);//2ms
        bombTimersp->setInterval(60000 * 60 * 4);//5h bomb

        pSocket->bind(QHostAddress::AnyIPv4, 8080);
        //maxChannelNum = 5;
        OriDataQueSp = make_shared<CirQueue<QByteArray>>(5 * maxChannelNum * 10000);//6024 * 5 * maxChannelNum * 20一个包6024字节， 5个包， 通道数， 频率低于20Hz
        MessagequeSp = make_shared<CirQueue<pair<int,int>>>(maxChannelNum * 10000); //maxChannelNum * 100
        SpOriData.resize(maxChannelNum);
        cout << SpOriData.size() << endl;
        recivedPacNum = 0;
        curChannelNum = 0;

        writeBuffer += QByteArray::fromHex("0");
        pSocket->writeDatagram(writeBuffer, QHostAddress(ip), port);
        waitTimersp->start();

        saveFile.resize(maxChannelNum);
        of.resize(maxChannelNum);
        flashFileName();
        timersp->start();

        bombTimersp->start();
        connect(waitTimersp.get(), SIGNAL(timeout()), this, SLOT(reSend()));
        connect(this, SIGNAL(sendWriteAble()), this, SLOT(restoreSPData()));
        connect(timersp.get(), SIGNAL(timeout()), this, SLOT(flashFileName()) );
        connect(pSocket.get(), SIGNAL(readyRead()),this, SLOT(readSPDataSlot()));
        connect(bombTimersp.get(), SIGNAL(timeout()), this, SLOT(exit()) );
        cout << "Init Read Spectrum" << endl;
//
    }
}




void UDP::exit()
{
    cout << "exit" << endl;
    //this->deleteLater();
    sendExit();

}

UDP::UDP(QString ip, int port)
    : writeBuffer(QByteArray::fromHex(STARTCONNECT) ),
      pSocket(make_shared<QUdpSocket>(this))
{
    pSocket->bind(QHostAddress::AnyIPv4, 8080);
    pSocket->writeDatagram(writeBuffer, QHostAddress(ip), port);
    connect(pSocket.get(), SIGNAL(readyRead()),this, SLOT(readDate()));
}

UDP::~UDP()
{
    writeBuffer = QByteArray::fromHex(DISCONNECT);
    pSocket->writeDatagram(writeBuffer, QHostAddress(IP), PORT);
    pSocket->close();
    while(pSocket->isOpen());
    cout << "UDP disconnect" << endl;
}

void UDP::reSend()
{
    waitTimersp->stop();
    auto disconnectbuff = QByteArray::fromHex(DISCONNECT);
    pSocket->writeDatagram(disconnectbuff, QHostAddress(IP), PORT);
    Sleep(200);//2s
    pSocket->writeDatagram(writeBuffer, QHostAddress(IP), PORT);
    cout << "resend : recivedPacNum = " << recivedPacNum << " curChannelNum = " << curChannelNum << endl;
    waitTimersp->start();//restart
    //emit sendReinit();
}

void UDP::flashFileName()
{
    QMutexLocker locker(&writeLock);
    for(auto& off : of)
    {
        off.close();
    }
    QDateTime systemDate = QDateTime::currentDateTime();
    QTime systemTime = QTime::currentTime();
    QString fileTime = systemDate.toString("yyyyMMdd")+systemTime.toString("hhmmss");
    shared_ptr<QDir> folderSp(new QDir( QDir::currentPath() ));
    QString absolutePath = folderSp->absolutePath();
    QString savePath = absolutePath + "/spectrum data";
    shared_ptr<QDir> saveFolderSp(new QDir(savePath));
    qDebug() << savePath << endl;
    if(!saveFolderSp->exists())
    {
        saveFolderSp->mkdir(savePath);
        qDebug() << "存储光谱数据文件夹创建成功";
    }
    for(int i = 0; i < maxChannelNum; i++)
    {
        saveFile[i] = savePath + QString("/[CH")+QString::number(i + 1)
                +QString("]") + fileTime + QString(".bin");
        of[i] = ofstream(saveFile[i].toStdString().data(), ofstream::binary);
    }
}

void UDP::flashFileName_wave()
{
    QMutexLocker locker(&writeLock);
    for(auto& off : of)
    {
        off.close();
    }
    QDateTime systemDate = QDateTime::currentDateTime();
    QTime systemTime = QTime::currentTime();
    QString fileTime = systemDate.toString("yyyyMMdd")+systemTime.toString("hhmmss");
    shared_ptr<QDir> folderSp(new QDir( QDir::currentPath() ));
    QString absolutePath = folderSp->absolutePath();
    QString savePath = absolutePath + "/wavelen data";
    shared_ptr<QDir> saveFolderSp(new QDir(savePath));
    qDebug() << savePath << endl;
    if(!saveFolderSp->exists())
    {
        saveFolderSp->mkdir(savePath);
        qDebug() << "save waveDate file create success";
    }
    for(int i = 0; i < maxChannelNum; i++)
    {
        saveFile[i] = savePath + QString("/[CH")+QString::number(i + 1)
                +QString("]") + fileTime + QString(".bin");
        of[i] = ofstream(saveFile[i].toStdString().data(), ofstream::binary);
    }
}

/* write spectrum data in file
 */
void UDP::restoreSPData()
{
    QMutexLocker locker(&writeLock);
    int Messquelen = MessagequeSp->size();
    while(Messquelen--)
    {
        int CHnum = MessagequeSp->front().first;
        MessagequeSp->pop();
        const QByteArray &CHData = OriDataQueSp->front();
        for(int j = 1; j < CHData.size(); j += 2)
        {
            unsigned short Di = static_cast<unsigned short>(CHData[j - 1]) + static_cast<unsigned short>(CHData[j]) << 8;
            float Df = static_cast<float>(Di) / 10;
            of[CHnum].write((const char*) &Df, sizeof(float));
        }
        OriDataQueSp->pop();
    }
}

/* write Wave data in file
 */
void UDP::restoreWLData()
{
    QMutexLocker locker(&writeLock);
    int Messquelen = MessagequeSp->size();
    cout << "Messquelen = " << Messquelen << endl;
    while(Messquelen-- && !WaveDataSp->isEmpty())
    {
        int CHnum = MessagequeSp->front().first;
        int wavelen = MessagequeSp->front().second;
        cout << "CHnum = " << CHnum << " wavelen = " << wavelen << endl;
        MessagequeSp->pop();
        //int i = 0;
        //if(basewave.size() < wavelen) basewave.resize(wavelen, 0);
        while(wavelen-- && !WaveDataSp->isEmpty())
        {
            float waveData = WaveDataSp->front();
            cout << "waveData = " << waveData << endl;
            //if(basewave[i] < 1.0) basewave[i] = waveData;
            of[CHnum].write((const char*) &waveData, sizeof(float));
            WaveDataSp->pop();
        }
    }
}

/* send next spectrum channel number
 */
void UDP::send(const QByteArray &wbuff)
{
    pSocket->writeDatagram(wbuff, QHostAddress(IP), PORT);
    waitTimersp->start();//restart
}

/* read spectrum ori data */
/* only first 5 packages are needed */
void UDP::readSPDataSlot()
{
    //QMutexLocker locker(&writeLock);

    QByteArray buff;
    buff.resize(pSocket->bytesAvailable());
    pSocket->readDatagram(buff.data(), buff.size());
    cout << buff.toStdString() << endl;
    //cout << "buff.size() = " << buff.size() << endl;
    buff.remove(0, 4);//去掉包头
    //cout << "recivedPacNum = " << recivedPacNum << endl;
    if(recivedPacNum == 5)
    {
        buff.clear();
        curChannelNum++;
        recivedPacNum = 0;
        if(curChannelNum >= maxChannelNum)
        {
            curChannelNum = 0;
            sendWriteAble();
        }
        /* write next channelNum Datagram */
        QByteArray CHn;
        CHn.setNum(curChannelNum);
        writeBuffer = QByteArray::fromHex(RDSPECTRUM) + QByteArray::fromHex(CHn);
        send(writeBuffer);
    }
    else if(recivedPacNum == 4)
    {
        buff.clear();
        recivedPacNum++;
    }
    else
    {
        //cout << "curChannelNum = " << curChannelNum << endl;
        OriDataQueSp->push(buff);
        //cout << "OriDataQueSp.size() = " << OriDataQueSp->size() << endl;
        MessagequeSp->push({curChannelNum, recivedPacNum});
        //cout << "OriDataQueSp.size() = " << MessagequeSp->size() << endl;
        recivedPacNum++;
    }

}


void UDP::readWLDataSlot()
{
    QByteArray buffer;
    buffer.clear();
    buffer.resize(pSocket->bytesAvailable());
    pSocket->readDatagram(buffer.data(), buffer.size());
    //cout << buffer.toStdString() << endl;
    //cout << "buffer.size() = " << buffer.size() << endl;
    if(buffer.size() == 4) return;//first packet is 01 0a 55 00
    if(buffer.size() == 34)
    {
        // no channel is connected
        cout << "no connected channel" << endl;
        return ;
    }
    if(buffer.size() < 34 || (buffer.size() % 2))
    {
        cout << "packet length error!" << endl;
        return ;
    }
    buffer.remove(0, 2);// remove 01 0c
//    for(auto &u : buffer)
//    {
//        cout << hex << static_cast<short>(u) << " ";
//    }
//    cout << endl;
    int cnt = 0;
    cout << "buffer.size() = " << buffer.size() << endl;
    while(cnt < buffer.size())
    {
        //cout << hex << static_cast<short>(buffer[cnt]) << " ";
        int chNum = static_cast<int>(buffer[cnt]);
        cout << "chNum = " << chNum << endl;
        if(chNum < 0 || chNum + 1 > maxChannelNum) break;
        cnt++;
        int wavelen = static_cast<int>(buffer[cnt]);
        cnt++;
        if(wavelen <= 0) break;
        int j = 0;
        for(int i = 0; i < wavelen * 2; i ++)
        {
            if(basewave.size() > 0 && j < basewave.size())
            {
                //qDebug() << "basewave = " << basewave[j] << endl;
                float tmp = getWave(buffer[cnt + i], buffer[cnt + i + 1]);
                //qDebug() << "abs float = " <<  abs(tmp - basewave[j]) << endl;
                HeatmapDataSp->push(abs(tmp - basewave[j++]));
            }
            else
            {
                basewave.clear();
                basewave.push_back(getWave(buffer[cnt + i], buffer[cnt + i + 1]));
            }
            if(isSave) WaveDataSp->push(getWave(buffer[cnt + i], buffer[cnt + i + 1]));
        }
        cnt += wavelen * 2;
        cout << "cnt = " << cnt << endl;
        MessagequeSp->push({chNum, wavelen});
    }
    cout << "readWLDataSlot" << endl;
    sendWriteAble_wave();
    if(!HeatmapDataSp->isEmpty()) sendUpdataHeatmap();
}

void UDP::setBaseWavelen()
{

}

float UDP::getWave(const char &dataL, const char &dataH)
{
    float wave = dataL + dataH << 8;
    wave /= 1000;
    wave += 1520.0;
    return wave;
}
