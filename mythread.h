#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(bool isRun READ isRun WRITE setIsRun NOTIFY isRunChanged)
    Q_PROPERTY(bool IsRunSock READ IsRunSock WRITE setIsRunSock NOTIFY IsRunSockChanged)

    QString m_message;
    bool m_isRun;
    bool m_IsRunSock;

public:
    explicit MyThread(QObject *parent = 0);
    QString message() const;
    bool isRun() const;
    bool IsRunSock() const;

public slots:
    void running();
    void runListenSock();
    void setMessage(QString message);
    void setIsRun(bool isRun);
    void setIsRunSock(bool IsRunSock);

signals:
    void send(QString);
    void reading();
    void finished();
    void messageChanged(QString message);
    void isRunChanged(bool isRun);
    void IsRunSockChanged(bool IsRunSock);
};

#endif // MYTHREAD_H
