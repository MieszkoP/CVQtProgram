#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(":/slownik/Slownik.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList list = line.split(QLatin1Char(','));
            EnglishWords.append(list[1]);
            PolishWords.append(list[0]);
        }
        length = EnglishWords.length();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LearningPolish(){
    ui->textPolish->setText(PolishWords[i%length]);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::LearningEnglish(){
    ui->textEnglish->setText(EnglishWords[i%length]);
    timer4->blockSignals(true);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::LearningReset(){
    ui->textEnglish->setText("");
    ui->textPolish->setText("");
    i+=1;
    timer5->blockSignals(true);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::LearningFunction(){
    if(stan==1){
    LearningPolish();
    qInfo() << "TimerWywolany";

    timer4 = new QTimer(this);
    timer4->connect(timer4, &QTimer::timeout, this, &MainWindow::LearningEnglish);
    timer4->start(3000);

    timer5 = new QTimer(this);
    timer5->connect(timer5, &QTimer::timeout, this, &MainWindow::LearningReset);
    timer5->start(4500);
    }
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::on_Learning_clicked()
{
    stan = 1;
    ui->Back->setEnabled(true);
    ui->Learning->setEnabled(false);
    ui->Test->setEnabled(false);
    i = 0;
    ui->textEnglish->setReadOnly(true);
    ui->textPolish->setEnabled(true);
    ui->textEnglish->setEnabled(true);
    LearningFunction();
    timer = new QTimer(this);
    timer->connect(timer, &QTimer::timeout, this, &MainWindow::LearningFunction);
    timer->start(5000);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::TestWriting(){
    if(stan==0){
    ui->textEnglish->setReadOnly(false);
    ui->textEnglish->setText("");
    ui->textEnglish->setTextColor(Qt::black);
    ui->textPolish->setText(PolishWords[i%length]);
    }
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::TestChecking(){
    ui->textEnglish->setReadOnly(true);
    if (wynik){
        ui->textEnglish->setTextColor(Qt::green);
    } else{
        ui->textEnglish->setTextColor(Qt::red);
    }
    ui->textEnglish->setText(EnglishWords[i%length]);
    TimeForCheck = 5000;
    timer3->blockSignals(true);
    i+=1;
    qInfo() << Q_FUNC_INFO;
    qInfo() << stan;
}

void MainWindow::Test(){
    TestWriting();
    qInfo() << "Czas w timerze3"<<TimeForCheck;
    qInfo() << "Timer2Wywolany";
    timer3 = new QTimer(this);
    timer3->connect(timer3, &QTimer::timeout, this, &MainWindow::TestChecking);
    timer3->start(TimeForCheck);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::on_Test_clicked()
{
    stan = 0;
    TimeForTest = 7000;
    ui->Back->setEnabled(true);
    ui->Learning->setEnabled(false);
    ui->Test->setEnabled(false);
    i = 0;
    ui->textPolish->setEnabled(true);
    ui->textEnglish->setEnabled(true);
    Test();
    timer2 = new QTimer(this);
    timer2->connect(timer2, &QTimer::timeout, this, &MainWindow::Test);
    timer2->start(TimeForTest);
    qInfo() << Q_FUNC_INFO;
}

void MainWindow::on_textEnglish_textChanged()
{
    if(EnglishWords[i%length] == ui->textEnglish->toPlainText()){
        wynik = true;}
    else{
        wynik = false;}
}

void MainWindow::on_Back_clicked()
{
    if(stan == 1){
        timer->stop();
        delete timer;
        timer4->stop();
        delete timer4;
        timer5->stop();
        delete timer5;

        }
    else if(stan == 0){
        timer2->stop();
        delete timer2;
        timer3->stop();
        delete timer3;
        ui->textEnglish->setTextColor(Qt::black);
    }
    ui->Test->setEnabled(true);
    ui->Learning->setEnabled(true);
    ui->Back->setEnabled(false);
    ui->textEnglish->setText("");
    ui->textPolish->setText("");
}

void MainWindow::on_Exit_clicked()
{
    MainWindow::close();
}
