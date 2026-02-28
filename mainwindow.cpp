#include "mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    editor = new QTextEdit(this);

    output = new QPlainTextEdit(this);
    output->setReadOnly(true);

    inputBox = new QLineEdit(this);
    enterButton = new QPushButton("Enter", this);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputBox);
    inputLayout->addWidget(enterButton);

    layout->addWidget(editor, 3);
    layout->addWidget(output, 1);
    layout->addLayout(inputLayout);

    setCentralWidget(central);

    process = new QProcess(this);

    setupMenu();

    connect(process, &QProcess::readyReadStandardOutput,
            this, [=]()
            {
                output->appendPlainText(
                    QString::fromUtf8(
                        process->readAllStandardOutput()));
            });

    connect(process, &QProcess::readyReadStandardError,
            this, [=]()
            {
                output->appendPlainText(
                    QString::fromUtf8(
                        process->readAllStandardError()));
            });

    connect(enterButton, &QPushButton::clicked,
            this, [=]()
            {
                if (process->state() != QProcess::Running)
                    return;

                QString text = inputBox->text();

                process->write(text.toUtf8());
                process->write("\n");

                output->appendPlainText(text); // echo like terminal
                inputBox->clear();
            });

    connect(inputBox, &QLineEdit::returnPressed,
            enterButton, &QPushButton::click);


}

void MainWindow::setupMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("File");
    QToolBar *toolbar = addToolBar("Main");

    openAction = new QAction("Open", this);
    saveAction = new QAction("Save", this);
    runAction  = new QAction("Run", this);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(runAction);

    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(runAction);

    connect(openAction, &QAction::triggered,
            this, &MainWindow::openFile);

    connect(saveAction, &QAction::triggered,
            this, &MainWindow::saveFile);

    connect(runAction, &QAction::triggered,
            this, &MainWindow::runCode);

    editor->setPlainText(
        "// This program reads two floating-point values from the user,\n"
        "// displays them, swaps their values, and prints the result.\n\n"
        "#include <iostream>\n"
        "using namespace std;\n\n"
        "int main()\n"
        "{\n"
        "    float firstNumber = 0.0f;\n"
        "    float secondNumber = 0.0f;\n\n"
        "    cout << \"Enter the first number and press Enter:\" << endl;\n"
        "    if (!(cin >> firstNumber))\n"
        "    {\n"
        "        cout << \"Invalid input. Program terminated.\" << endl;\n"
        "        return 1;\n"
        "    }\n\n"
        "    cout << \"Enter the second number and press Enter:\" << endl;\n"
        "    if (!(cin >> secondNumber))\n"
        "    {\n"
        "        cout << \"Invalid input. Program terminated.\" << endl;\n"
        "        return 1;\n"
        "    }\n\n"
        "    cout << \"\\nYou entered: \" << firstNumber\n"
        "         << \" and \" << secondNumber << endl;\n\n"
        "    float temp = firstNumber;\n"
        "    firstNumber = secondNumber;\n"
        "    secondNumber = temp;\n\n"
        "    cout << \"After swapping: \"\n"
        "         << firstNumber << \" and \" << secondNumber << endl;\n\n"
        "    return 0;\n"
        "}\n"
        );
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "C++ Files (*.cpp *.h *.txt)");

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
        "C++ Files (*.cpp)");

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
#ifdef Q_OS_WIN
    QString exeFile = "temp.exe";
#else
    QString exeFile = "./temp";
#endif

    // write source
    QFile file(sourceFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();

    // compile (blocking allowed here)
#ifdef Q_OS_WIN
    process->start("g++",
                   QStringList() << sourceFile << "-o" << "temp.exe");
#else
    process->start("g++",
                   QStringList() << sourceFile << "-o" << "temp");
#endif

    process->waitForFinished();

    QString compileError =
        process->readAllStandardError();

    if (!compileError.isEmpty())
    {
        output->setPlainText(
            "Compilation Error:\n" + compileError);
        return;
    }

    // RUN ASYNC (critical change)
    process->start(exeFile);
}
