#include "mythread.h"
#include <QDebug>
#include <windows.h>

//ExampleObject::ExampleObject(QObject *parent) :
//    QObject(parent),
//    m_message("")

MyThread::MyThread(QObject *parent) :
    QObject(parent),
    m_message("")
{
}

QString MyThread::message() const
{
    return m_message;
}

bool MyThread::isRun() const
{
    return m_isRun;
}

bool MyThread::IsRunSock() const
{
    return m_IsRunSock;
}

void MyThread::running()
{
    while (m_isRun)
    {
        emit reading();
        Sleep(5);
        emit send(m_message);
        //qDebug() << "Message: " << m_message;
    }
    emit finished();
}

void MyThread::runListenSock()
{
//    while (m_IsRunSock)
//    {
//        emit listenSock();
//        Sleep(10);
//    }
}

void MyThread::setMessage(QString message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(m_message);
}

void MyThread::setIsRun(bool isRun)
{
    if (m_isRun == isRun)
        return;

    m_isRun = isRun;
    emit isRunChanged(m_isRun);
}

void MyThread::setIsRunSock(bool IsRunSock)
{
//    if (m_IsRunSock == IsRunSock)
//        return;

//    m_IsRunSock = IsRunSock;
//    emit IsRunSockChanged(m_IsRunSock);
}
