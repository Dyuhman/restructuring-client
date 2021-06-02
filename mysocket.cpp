#include "mysocket.h"
#include <QDebug>
#include <windows.h>

MySocket::MySocket(QObject *parent) : QObject(parent)
{

}

//===========================================CLIENT=============================================
bool MySocket::connectToServer() //Клиент подключается к серверу (2 этап)
{
    WSAData wsaData;
    WORD DLLersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLersion, &wsaData) != 0)
    {
        WSACleanup();
        return false;
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    ClientConnection = socket(AF_INET, SOCK_STREAM, NULL);
    if (::connect(ClientConnection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        closesocket(ClientConnection);
        WSACleanup();
        return false;
    }
    return true;
}

void MySocket::clientSendSock(QString msg) //Клиент отправляет сообщение серверу (2 этап)
{
    int msg_size = msg.size();
    QByteArray bArr = msg.toLocal8Bit();
    const char *msgChar = bArr.data();
    send(ClientConnection, (char*)&msg_size, sizeof(int), NULL);
    send(ClientConnection, msgChar, msg_size, NULL);
}

void MySocket::clientRecvSock() //Клиент принимает сообщение от сервера (1 этап)
{
    while(m_ClientRunSock)
    {
        int msg_size;
        recv(ClientConnection, (char*)&msg_size, sizeof(int), NULL);
        char *msgChar = new char[msg_size + 1];
        msgChar[msg_size] = '\0';
        int recieve;
        recieve = recv(ClientConnection, msgChar, msg_size, NULL);
        qDebug() << "RECIEVE" << recieve;
        QString msg = msgChar;
        delete[] msgChar;
        setMessage(msg);
        emit clientListenSock(m_Message);
        qDebug() << msg;
        Sleep(10);
    }
}

void MySocket::clientDisconnect()
{
    closesocket(ClientConnection);
    WSACleanup();
}


//===========================================SERVER=============================================
//======================================ЕБИСЬ ОНО КОНЕМ=========================================
