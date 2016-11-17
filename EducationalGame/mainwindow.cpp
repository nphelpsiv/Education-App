#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dummyserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_signup_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_signup_submitButton_clicked()
{
    if(signup(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString(), ui->teacherCheckBox->isChecked()))
    {
        if(ui->teacherCheckBox->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(3);
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(2);
        }

    }
}

void MainWindow::on_loginButton_clicked()
{
    if(login(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString()))
    {
        if(isTeacher(ui->login_userNameText->text().toStdString()))
            ui->stackedWidget->setCurrentIndex(3);
        else
            ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::on_playToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
