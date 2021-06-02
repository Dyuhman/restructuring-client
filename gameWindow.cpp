#include "gameWindow.h"
#include "ui_gameWindow.h"

int countDesc = 0;
int countCard = 0;

gameWindow::gameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWindow)
{
    ui->setupUi(this);

    ui->title->setAlignment(Qt::AlignCenter);
    ui->title->setText("ХОД ИГРЫ (1)");
    ui->description->setText("Игроки ходят друг за другом по часовой стрелке. Каждый игрок\n"
                             "совершает одно действие. Пропускать ход нельзя.\n"
                             "Два действия доступны всем игрокам: Прибыль и Перестройка.\n"
                             "Их игрок может применять без определенных карт. Остальные\n"
                             "действия привязаны к кнокретным персонажам. Выбирая их, вы\n"
                             "заявляете, что имеете авторитет на этого пресонажа (то есть\n"
                             "среди ваших закрытых карт авторитета есть такой персонаж). =>");

    ui->titleCard->setAlignment(Qt::AlignCenter);
    ui->titleCard->setStyleSheet("color: green");
    ui->titleCard->setText("Предприниматель");
    ui->descriptionCard->setText("Доход. Получите 3 монеты из бюджета.");

    ui->prevPageCardBTN->setEnabled(false);
    ui->prevPageDescBTN->setEnabled(false);

    QPixmap background(":/img/empty50.png");
    ui->background->setPixmap(background.scaled(ui->background->width(), ui->background->height()));
}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::flippingPageDesc()
{

    switch (countDesc)
    {
    case 0:
        ui->title->setText("ХОД ИГРЫ (1)");
        ui->description->setText("Игроки ходят друг за другом по часовой стрелке. Каждый игрок\n"
                                 "совершает одно действие. Пропускать ход нельзя.\n"
                                 "Два действия доступны всем игрокам: Прибыль и Перестройка.\n"
                                 "Их игрок может применять без определенных карт. Остальные\n"
                                 "действия привязаны к кнокретным персонажам. Выбирая их, вы\n"
                                 "заявляете, что имеете авторитет на этого пресонажа (то есть\n"
                                 "среди ваших закрытых карт авторитета есть такой персонаж). =>");
        break;
    case 1:
        ui->title->setText("ХОД ИГРЫ (2)");
        ui->description->setText("<= Таким образом любой игрок может блефовать и выбирать\n"
                                 "действие, привязанное к персонажу, на которого на самом деле\n"
                                 "у него нет авторитета.\n"
                                 "После того, как игрок объявляет свое действие, его оппоненты\n"
                                 "могут попататься заблокировать действие или же проверять\n"
                                 "легальность этого действия. Если никто из оппонентов не\n"
                                 "решается мешать то действие происходит беспрепятственно.");
        break;
    case 2:
        ui->title->setText("ПЕРСОНАЖИ И ДЕЙСТВИЯ");
        ui->description->setText("Описание основных действий");
        break;
    case 3:
        ui->title->setText("ПРОВЕРКА");
        ui->description->setText("Описание проверки");
        break;
    case 4:
        ui->title->setText("БЛОКИРОВКА КАРТ");
        ui->description->setText("Описание блокировки");
        break;
    case 5:
        ui->title->setText("ДВОЙНАЯ ПОТЕРЯ");
        ui->description->setText("Описание двойной потери карты");
        break;
    default:
        ui->title->setText("ERROR countDesc");
        ui->description->setText("Ошибка 404");
        break;
    }

}

void gameWindow::flippingPageCard()
{
    switch (countCard)
    {
    case 0:
        ui->titleCard->setStyleSheet("color: green");
        ui->titleCard->setText("Предприниматель");
        ui->descriptionCard->setText("Доход. Получите 3 монеты из бюджета.");
        break;
    case 1:
        ui->titleCard->setStyleSheet("color: green");
        ui->titleCard->setText("Фарцовщик");
        ui->descriptionCard->setText("Импорт. Получите 3 монеты из Бюджета. После чего\n"
                                     "заплатите 1 монету любому игроку.");
        break;
    case 2:
        ui->titleCard->setStyleSheet("color: green");
        ui->titleCard->setText("Сотрудник ОБХСС");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 3:
        ui->titleCard->setStyleSheet("color: green");
        ui->titleCard->setText("Цеховик");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 4:
        ui->titleCard->setStyleSheet("color: green");
        ui->titleCard->setText("Кооператор");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 5:
        ui->titleCard->setStyleSheet("color: blue");
        ui->titleCard->setText("Киллер");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 6:
        ui->titleCard->setStyleSheet("color: blue");
        ui->titleCard->setText("Риэлтор");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 7:
        ui->titleCard->setStyleSheet("color: blue");
        ui->titleCard->setText("Войска");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 8:
        ui->titleCard->setStyleSheet("color: blue");
        ui->titleCard->setText("Чекист");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 9:
        ui->titleCard->setStyleSheet("color: blue");
        ui->titleCard->setText("Братва");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 10:
        ui->titleCard->setStyleSheet("color: yellow");
        ui->titleCard->setText("Журналист");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 11:
        ui->titleCard->setStyleSheet("color: yellow");
        ui->titleCard->setText("Радиодиктор");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 12:
        ui->titleCard->setStyleSheet("color: yellow");
        ui->titleCard->setText("Телеведущий");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 13:
        ui->titleCard->setStyleSheet("color: yellow");
        ui->titleCard->setText("Агент влияния");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 14:
        ui->titleCard->setStyleSheet("color: yellow");
        ui->titleCard->setText("Пропагандист");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 15:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Бюрократ");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 16:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Нотариус");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 17:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Диссидент");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 18:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Священник");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 19:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Анархист");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 20:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Повстанец");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 21:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Реформатор");
        ui->descriptionCard->setText("Описание карты");
        break;
    case 22:
        ui->titleCard->setStyleSheet("color: red");
        ui->titleCard->setText("Страховщик");
        ui->descriptionCard->setText("Описание карты");
        break;
    default:
        ui->titleCard->setStyleSheet("color: black");
        ui->titleCard->setText("ERROR countCard");
        ui->descriptionCard->setText("Ошибка 404");
        break;
    }
}

void gameWindow::on_nextPageDescBTN_clicked()
{
    countDesc++;

    switch(countDesc)
    {
    case 0:
        ui->prevPageDescBTN->setEnabled(false);
        break;
    case 4:
        ui->nextPageDescBTN->setEnabled(false);
        break;
    default:
        ui->prevPageDescBTN->setEnabled(true);
        ui->nextPageDescBTN->setEnabled(true);
        break;
    }

    flippingPageDesc();
}

void gameWindow::on_prevPageDescBTN_clicked()
{
    countDesc--;

    switch(countDesc)
    {
    case 0:
        ui->prevPageDescBTN->setEnabled(false);
        break;
    case 4:
        ui->nextPageDescBTN->setEnabled(false);
        break;
    default:
        ui->prevPageDescBTN->setEnabled(true);
        ui->nextPageDescBTN->setEnabled(true);
        break;
    }

    flippingPageDesc();
}

void gameWindow::on_nextPageCardBTN_clicked()
{
    countCard++;

    switch(countCard)
    {
    case 0:
        ui->prevPageCardBTN->setEnabled(false);
        break;
    case 22:
        ui->nextPageCardBTN->setEnabled(false);
        break;
    default:
        ui->prevPageCardBTN->setEnabled(true);
        ui->nextPageCardBTN->setEnabled(true);
        break;
    }

    flippingPageCard();
}

void gameWindow::on_prevPageCardBTN_clicked()
{
    countCard--;

    switch(countCard)
    {
    case 0:
        ui->prevPageCardBTN->setEnabled(false);
        break;
    case 22:
        ui->nextPageCardBTN->setEnabled(false);
        break;
    default:
        ui->prevPageCardBTN->setEnabled(true);
        ui->nextPageCardBTN->setEnabled(true);
        break;
    }

    flippingPageCard();
}

void gameWindow::on_capitalButton_clicked()
{
    countCard = 0;
    ui->prevPageCardBTN->setEnabled(false);
    ui->nextPageCardBTN->setEnabled(true);
    flippingPageCard();
}

void gameWindow::on_agresssionButton_clicked()
{
    countCard = 5;
    ui->prevPageCardBTN->setEnabled(true);
    ui->nextPageCardBTN->setEnabled(true);
    flippingPageCard();
}

void gameWindow::on_mediaButton_clicked()
{
    countCard = 10;
    ui->prevPageCardBTN->setEnabled(true);
    ui->nextPageCardBTN->setEnabled(true);
    flippingPageCard();
}

void gameWindow::on_blatButton_clicked()
{
    countCard = 15;
    ui->prevPageCardBTN->setEnabled(true);
    ui->nextPageCardBTN->setEnabled(true);
    flippingPageCard();
}
