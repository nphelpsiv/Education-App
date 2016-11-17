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
    //signup is a method from dummyServer.h
    //COMMENT OUT THIS BLOCK IF YOU DON'T WANT DUMMY SERVER STUFF
    /*if(signup(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString(), ui->teacherCheckBox->isChecked()))
    {
        if(ui->teacherCheckBox->isChecked())
        {
            ui->stackedWidget->setCurrentIndex(3);
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(2);
        }

    }*/

    //UNCOMMENT THIS IF YOU DON'T WANT THE DUMMY SERVER STUFF

    if(ui->teacherCheckBox->isChecked())
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(2);
    }

}

void MainWindow::on_loginButton_clicked()
{
    //login is dummyServer.h method
    //COMMENT OUT THIS BLOCK IF YOU WANT TO USE DUMMY SERVER STUFF.
    //use username = "justin" and password = "bush" for student login
    //use username = "john" and password = "young" for teacher login
    /*if(login(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString()))
    {
        if(isTeacher(ui->login_userNameText->text().toStdString()))
            ui->stackedWidget->setCurrentIndex(3);
        else
            ui->stackedWidget->setCurrentIndex(2);
    }*/

    //UNCOMMENT THIS LINE IF YOU DON'T WANT DUMMY SERVER STUFF.
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_playToolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
