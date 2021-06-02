#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "gameWindow.h"

#include <QThread>
#include <QPixmap>
#include "mythread.h"
#include "mysocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool IsConnect READ IsConnect WRITE setIsConnect NOTIFY IsConnectChanged)
    Q_PROPERTY(bool IsCreateGame READ IsCreateGame WRITE setIsCreateGame NOTIFY IsCreateGameChanged)

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

    bool IsConnect() const
    {
        return m_IsConnect;
    }
    bool IsCreateGame() const
    {
        return m_IsCreateGame;
    }

public slots:
    void setIsConnect(bool IsConnect)
    {
        if (m_IsConnect == IsConnect)
            return;

        m_IsConnect = IsConnect;
        emit IsConnectChanged(m_IsConnect);
    }
    void setIsCreateGame(bool IsCreateGame)
    {
        if (m_IsCreateGame == IsCreateGame)
            return;

        m_IsCreateGame = IsCreateGame;
        emit IsCreateGameChanged(m_IsCreateGame);
    }

signals:
    void IsConnectChanged(bool IsConnect);
    void IsCreateGameChanged(bool IsCreateGame);

private slots:
    void on_shutdownWindow_clicked();
    void on_backMenuWindow_clicked();
    void on_connectGameButton_clicked();
    void on_startGameButton_clicked();
    void on_runGameButton_clicked();
    void on_nicknameEditButton_clicked();

    void clientReceiveSock(QString text);

    void on_regulationsButton_clicked();

private:
    Ui::mainWindow *ui;
    gameWindow *gameWin;

    QThread clientThread;
    MySocket clientSocket;
    bool m_IsConnect;
    bool m_IsCreateGame;
};
#endif // MENUWINDOW_H
