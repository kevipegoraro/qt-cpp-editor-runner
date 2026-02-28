#include "mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    editor = new QTextEdit(this);
    output = new QPlainTextEdit(this);
    output->setReadOnly(true);

    layout->addWidget(editor, 3);
    layout->addWidget(output, 1);

    setCentralWidget(central);

    process = new QProcess(this);

    setupMenu();
}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("File");
    QToolBar *toolbar = addToolBar("Main");

    openAction = new QAction("Open", this);
    saveAction = new QAction("Save", this);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);

    connect(openAction, &QAction::triggered,
            this, &MainWindow::openFile);

    connect(saveAction, &QAction::triggered,
            this, &MainWindow::saveFile);

    runAction = new QAction("Run", this);

    fileMenu->addAction(runAction);
    toolbar->addAction(runAction);

    connect(runAction, &QAction::triggered,
            this, &MainWindow::runCode);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "Text Files (*.txt *.cpp *.h)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        editor->setPlainText(in.readAll());
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save File",
        "",
        "Text Files (*.txt)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << editor->toPlainText();
    }
}

void MainWindow::runCode()
{
    output->clear();

    QString sourceFile = "temp.cpp";
    QString exeFile = "temp.exe";

    // Write editor content to file
    QFile file(sourceFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();

    // Compile
    process->start("g++", QStringList() << sourceFile << "-o" << exeFile);
    process->waitForFinished();

    QString compileOutput = process->readAllStandardOutput();
    QString compileError = process->readAllStandardError();

    if (!compileError.isEmpty())
    {
        output->setPlainText("Compilation Error:\n" + compileError);
        return;
    }

    // Run executable
    process->start(exeFile);
    process->waitForFinished();

    QString runOutput = process->readAllStandardOutput();
    QString runError = process->readAllStandardError();

    output->setPlainText(runOutput + runError);
}
