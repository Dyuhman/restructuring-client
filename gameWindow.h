#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class gameWindow;
}

class gameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = nullptr);
    ~gameWindow();

signals:
    void firstwindow();

private slots:
    void flippingPageDesc();
    void flippingPageCard();
    void on_nextPageDescBTN_clicked();
    void on_prevPageDescBTN_clicked();

    void on_nextPageCardBTN_clicked();

    void on_prevPageCardBTN_clicked();

    void on_capitalButton_clicked();

    void on_agresssionButton_clicked();

    void on_mediaButton_clicked();

    void on_blatButton_clicked();

private:
    Ui::gameWindow *ui;
};

#endif // GAMEWINDOW_H
