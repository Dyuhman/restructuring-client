#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <QThread>

class MySocket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ClientRunSock READ ClientRunSock WRITE setClientRunSock NOTIFY ClientRunSockChanged)
    Q_PROPERTY(QString Message READ Message WRITE setMessage NOTIFY MessageChanged)

    QString m_Message;
    bool m_ClientRunSock;

public:
    explicit MySocket(QObject *parent = nullptr);
    QString Message() const
    {
        return m_Message;
    }

    SOCKET ClientConnection;
    bool ClientRunSock() const
    {
        return m_ClientRunSock;
    }

public slots:
    void setMessage(QString Message)
    {
        if (m_Message == Message)
            return;

        m_Message = Message;
        emit MessageChanged(m_Message);
    }

    void setClientRunSock(bool ClientRunSock)
    {
        if (m_ClientRunSock == ClientRunSock)
            return;

        m_ClientRunSock = ClientRunSock;
        emit ClientRunSockChanged(m_ClientRunSock);
    }
    bool connectToServer();
    void clientSendSock(QString msg);
    void clientRecvSock();
    void clientDisconnect();

signals:
    void MessageChanged(QString Message);

    void ClientRunSockChanged(bool ClientRunSock);
    void clientListenSock(QString);
};

#endif // MYSOCKET_H
