#include "mainWindow.h"
#include "ui_mainWindow.h"

QString nameClients[6];
int readyClients[6] = {2,-1,-1,-1,-1,-1};
QString PlayerName = "";
int PlayerIndex = -1;
int countConnectedPlayers = 0;

int menuFormWidth = 521;
int menuFormHeight = 441;
int gameFormWidth = 1300;
int gameFormHeight = 640;

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    ui->nameOponent3->setVisible(false);
    ui->statusOponent3->setVisible(false);
    ui->iconCoinsOponent3->setVisible(false);
    ui->countCoinsOponent3->setVisible(false);
    ui->oponent3Card1->setVisible(false);
    ui->oponent3Card2->setVisible(false);

    QPixmap main(":/img/restructuring.jpg");
    ui->mainIMG->setAlignment(Qt::AlignCenter);
    ui->mainIMG->setPixmap(main.scaled(ui->mainIMG->width(), ui->mainIMG->height()));

    QPixmap background(":/img/empty50.png");
    ui->background1->setPixmap(background.scaled(ui->background1->width(), ui->background1->height()));
    ui->background2->setPixmap(background.scaled(ui->background2->width(), ui->background2->height()));

    QPixmap shirt(":/img/cards/shirt.png");
    ui->oponent1Card1->setPixmap(shirt.scaled(ui->oponent1Card1->width(), ui->oponent1Card1->height(), Qt::KeepAspectRatio));
    ui->oponent1Card2->setPixmap(shirt.scaled(ui->oponent1Card2->width(), ui->oponent1Card2->height(), Qt::KeepAspectRatio));
    ui->oponent2Card1->setPixmap(shirt.scaled(ui->oponent2Card1->width(), ui->oponent2Card1->height(), Qt::KeepAspectRatio));
    ui->oponent2Card2->setPixmap(shirt.scaled(ui->oponent2Card2->width(), ui->oponent2Card2->height(), Qt::KeepAspectRatio));
    ui->oponent3Card1->setPixmap(shirt.scaled(ui->oponent3Card1->width(), ui->oponent3Card1->height(), Qt::KeepAspectRatio));
    ui->oponent3Card2->setPixmap(shirt.scaled(ui->oponent3Card2->width(), ui->oponent3Card2->height(), Qt::KeepAspectRatio));

    QPixmap coins(":/img/coins.png");
    ui->iconCoins->setPixmap(coins.scaled(ui->iconCoins->width(), ui->iconCoins->height(), Qt::KeepAspectRatio));
    ui->iconCoinsOponent1->setPixmap(coins.scaled(ui->iconCoinsOponent1->width(), ui->iconCoinsOponent1->height(), Qt::KeepAspectRatio));
    ui->iconCoinsOponent2->setPixmap(coins.scaled(ui->iconCoinsOponent2->width(), ui->iconCoinsOponent2->height(), Qt::KeepAspectRatio));
    ui->iconCoinsOponent3->setPixmap(coins.scaled(ui->iconCoinsOponent3->width(), ui->iconCoinsOponent3->height(), Qt::KeepAspectRatio));

    QPixmap card1(":/img/cards/businessman.png");
    QPixmap card2(":/img/cards/killer.png");
    //QPixmap card3(":/img/cards/news.png");
    //QPixmap card4(":/img/cardsburokrat.png");
    //QPixmap card5(":/img/cards/dissident.png");

    ui->playerCard1->setPixmap(card1.scaled(ui->playerCard1->width(), ui->playerCard1->height(), Qt::KeepAspectRatio));
    ui->playerCard2->setPixmap(card2.scaled(ui->playerCard2->width(), ui->playerCard2->height(), Qt::KeepAspectRatio));

    ui->playerCard1BTN->setStyleSheet("QPushButton{border-style: solid;"
                                              "border-width: 3px;"
                                              "border-color: green;"
                                              "border-radius: 6px}");
    ui->playerCard2BTN->setStyleSheet("QPushButton{border-style: solid;"
                                              "border-width: 3px;"
                                              "border-color: blue;"
                                              "border-radius: 6px}");

    gameWin = new gameWindow();
    connect(gameWin, &gameWindow::firstwindow, this, &mainWindow::show);

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setGeometry(0,0,menuFormWidth,menuFormHeight);
    this->setGeometry(0,0,menuFormWidth,menuFormHeight);

    setIsConnect(false);
    setIsCreateGame(false);

    connect(&clientThread, &QThread::started, &clientSocket, &MySocket::clientRecvSock);
    connect(&clientSocket, &MySocket::clientListenSock, this, &mainWindow::clientReceiveSock);
    clientSocket.moveToThread(&clientThread);
}

mainWindow::~mainWindow()
{
    delete ui;
}

int getStatus (QString msg) // получить статус
{
    int status = -1;
    QString statusString = "";
    for (int i = 0; i < 4; i++)
    {
        if (msg[i] == ':') break;
        if (msg[i] == '0' || msg[i] == '1' || msg[i] == '2' || msg[i] == '3' || msg[i] == '4' || msg[i] == '5' || msg[i] == '6' || msg[i] == '7' || msg[i] == '8' || msg[i] == '9')
        statusString += msg[i];
    }
    if (statusString != "") status = statusString.toInt();
    return status;
}

QString getMessage (QString msg) //получить сообщение
{
    QString nonStatus;
    bool firstDblDot = false;
    for (int i = 0; i < msg.length(); i++)
    {
        if (!firstDblDot && msg[i] == ':')
        {
            firstDblDot = true;
            continue;
        }
        if (firstDblDot) nonStatus += msg[i];
    }
    return nonStatus;
}

void setReadyClient(int index)
{
    if (readyClients[index] == 0) readyClients[index] = 1;
    else if (readyClients[index] == 1) readyClients[index] = 0;
}

void mainWindow::on_shutdownWindow_clicked()
{
    this->close();
}

void mainWindow::on_backMenuWindow_clicked()
{
    setIsConnect(false);
    setIsCreateGame(false);
    //Закрываем поток
    clientSocket.setClientRunSock(false);
    clientThread.terminate();
    //Отключение от сервера
    clientSocket.clientDisconnect();

    this->ui->stackedWidget->setCurrentIndex(0);
}

void mainWindow::on_connectGameButton_clicked()
{
    if (IsConnect())
    {
        //предупреждение о том, что клиент уже подключен к серверу
        return;
    }
    else
    {
        //Подключение к серверу
        if (clientSocket.connectToServer())
        {
            setIsCreateGame(false);
            ui->startGameButton->setText("Не готов");
            setIsConnect(true);
            clientSocket.setClientRunSock(true);
            clientThread.start();

            this->ui->stackedWidget->setCurrentIndex(1);
        }
        else
        {
            //Предупреждение об ошибки подключения
            return;
        }
    }
}

void mainWindow::on_runGameButton_clicked()
{
    if (IsConnect())
    {
        //предупреждение о том, что клиент уже подключен к серверу
        return;
    }
    else
    {
        //Подключение к серверу
        if (clientSocket.connectToServer())
        {
            setIsCreateGame(true);
            ui->startGameButton->setText("Начать перестройку");
            ui->startGameButton->setEnabled(false);
            setIsConnect(true);
            clientSocket.setClientRunSock(true);
            clientThread.start();

            this->ui->stackedWidget->setCurrentIndex(1);
        }
        else
        {
            //Предупреждение об ошибки подключения
            return;
        }
    }
}

void mainWindow::clientReceiveSock(QString text)
{
    int status = getStatus(text);
    QString message = getMessage(text);
    QString name;
    int count;
    switch(status)
    {
    case 7: //Открытие слоя с игрой
        this->ui->stackedWidget->setCurrentIndex(2);
        ui->stackedWidget->setGeometry(0,0,gameFormWidth,gameFormHeight);
        this->setGeometry(0,0,gameFormWidth,gameFormHeight);
        break;

    case 8: //Обновление готовности игроков
        for (int i = 0; i < countConnectedPlayers; i++)
        {
            if (nameClients[i] == message)
            {
                setReadyClient(i);
                break;
            }
        }
        ui->listPlayers->setPlainText("");
        for (int i = 0; i < countConnectedPlayers; i++)
        {
            switch (readyClients[i])
            {
            case 2:
                ui->listPlayers->setTextColor("red");
                ui->listPlayers->insertPlainText(nameClients[i] + '\n');
                break;
            case 0:
                ui->listPlayers->setTextColor("blue");
                ui->listPlayers->insertPlainText(nameClients[i] + '\n');
                break;
            case 1:
                ui->listPlayers->setTextColor("green");
                ui->listPlayers->insertPlainText(nameClients[i] + '\n');
                break;
            case -1:
                qDebug() << "ОШИБКА В ПОДСЧЕТЕ КОЛИЧЕСТВА ПОДКЛЮЧЕНИЙ (8): " << countConnectedPlayers;
                break;
            default:
                qDebug() << "НЕ ПОНЯТНОЕ ЗНАЧЕНИЕ В МАССИВЕ ГОТОВНОСТИ ИГРОКОВ (8): " << readyClients[i];
                break;
            }
        }
        if (PlayerName == nameClients[0] && countConnectedPlayers > 2) //Проверка для активации запуска игры
        {
            int summ = 0;
            for (int i = 0; i < countConnectedPlayers; i++)
            {
                summ += readyClients[i];
            }
            if (summ == countConnectedPlayers + 1)
                ui->startGameButton->setEnabled(true);
            else
                ui->startGameButton->setEnabled(false);
        }
        break;

    case 9: //Обновление списка игроков при добавлении игроков или смены имени
        name = "";
        count = 0;
        ui->listPlayers->setPlainText("");
        for (int i = 0; i < message.length(); i++)
        {
            if (message[i] == ':')
            {
                qDebug() << "PLAYER: " << nameClients[count] << ";  STATUS: " << readyClients[count];
                switch (readyClients[count])
                {
                case 2:
                    nameClients[count] = name;
                    ui->listPlayers->setTextColor("red");
                    break;
                case 1:
                    nameClients[count] = name;
                    ui->listPlayers->setTextColor("green");
                    break;
                case 0:
                    nameClients[count] = name;
                    ui->listPlayers->setTextColor("blue");
                    break;
                case -1:
                    readyClients[count] = 0;
                    nameClients[count] = name;
                    ui->listPlayers->setTextColor("blue");
                    break;
                default:
                    qDebug() << "ОБНОВЛЕНИЕ СПИСКА ИГРОКОВ ПРОШЛО НЕ ГЛАДКО (9)";
                    break;
                }
                name = "";
                ui->listPlayers->insertPlainText(nameClients[count] + '\n');
                count++;
                continue;
            }
            name += message[i];
        }
        countConnectedPlayers = count;
        if (PlayerName == "" && PlayerIndex == -1)
        {
            PlayerName = nameClients[count - 1];
            PlayerIndex = count - 1;
            qDebug() << PlayerName << " " << PlayerIndex;
        }
        break;
    }
}

void mainWindow::on_startGameButton_clicked()
{
    QString message;
    if (IsCreateGame())
    {
        //переход в игру
        message = "7:Start";
        clientSocket.clientSendSock(message);
    }
    else
    {
        if (ui->startGameButton->text() == "Не готов")
        {
            //Игрок готов к игре
            message = "8:" + PlayerName;
            clientSocket.clientSendSock(message);

            ui->startGameButton->setText("Готов");
            ui->nicknameEdit->setEnabled(false);
            ui->nicknameEditButton->setEnabled(false);
            ui->backMenuWindow->setEnabled(false);
        }
        else
        {
            //Игрок не готов к игре
            message = "8:" + PlayerName;
            clientSocket.clientSendSock(message);

            ui->startGameButton->setText("Не готов");
            ui->nicknameEdit->setEnabled(true);
            ui->nicknameEditButton->setEnabled(true);
            ui->backMenuWindow->setEnabled(true);
        }

    }
}

void mainWindow::on_nicknameEditButton_clicked()
{
    PlayerName = ui->nicknameEdit->text();
    QString message = "9:" + ui->nicknameEdit->text();
    if (message == "") return;
    ui->nicknameEdit->setText("");
    clientSocket.clientSendSock(message);
    Sleep(10);
    //Необходимо добавить проверку на одинаковые имена
}

void mainWindow::on_regulationsButton_clicked()
{
    gameWin->show();
}

