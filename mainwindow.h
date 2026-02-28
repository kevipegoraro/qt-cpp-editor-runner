#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QAction>
#include <QProcess>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupMenu();
    void openFile();
    void saveFile();
    void runCode();

    QTextEdit *editor;
    QPlainTextEdit *output;

    QAction *openAction;
    QAction *saveAction;
    QAction *runAction;

    QProcess *process;
};

#endif
