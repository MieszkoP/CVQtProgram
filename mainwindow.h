#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <thread>
#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTimer>
#include<QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Learning_clicked();
    void LearningFunction();
    void LearningPolish();
    void LearningEnglish();
    void LearningReset();
    void on_Test_clicked();
    void on_textEnglish_textChanged();
    void TestWriting();
    void TestChecking();
    void Test();

    void on_Back_clicked();

    void on_Exit_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    QStringList EnglishWords = {};
    QStringList PolishWords = {};
    int i = 0;
    int length;
    bool wynik;
    QTimer *timer;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;

    int stan = 2; //0 means learning stan, 1 means test stan
    int TimeForCheck = 5000;
    int TimeForTest = 7000;
};
#endif // MAINWINDOW_H
