/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_2;
    QWidget *signUp;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *signUpLabel;
    QWidget *startPage;
    QLabel *label_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QToolButton *toolButton;
    QComboBox *comboBox;
    QToolButton *toolButton_2;
    QWidget *teacherPage;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QTableView *tableView;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *gamePage;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QPushButton *q3_Button;
    QPushButton *q2_Button;
    QPushButton *q1_Button;
    QPushButton *q4_Button;
    QLabel *questionLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(741, 632);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setGeometry(QRect(0, 0, 741, 591));
        loginPage = new QWidget();
        loginPage->setObjectName(QStringLiteral("loginPage"));
        gridLayoutWidget = new QWidget(loginPage);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 220, 341, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 0, 0, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(loginPage);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 390, 80, 24));
        stackedWidget->addWidget(loginPage);
        signUp = new QWidget();
        signUp->setObjectName(QStringLiteral("signUp"));
        gridLayoutWidget_2 = new QWidget(signUp);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(130, 130, 450, 198));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_3, 2, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        checkBox = new QCheckBox(gridLayoutWidget_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_2->addWidget(checkBox, 3, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(signUp);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(360, 400, 79, 24));
        pushButton_4 = new QPushButton(signUp);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(270, 400, 79, 24));
        signUpLabel = new QLabel(signUp);
        signUpLabel->setObjectName(QStringLiteral("signUpLabel"));
        signUpLabel->setGeometry(QRect(130, 40, 60, 16));
        stackedWidget->addWidget(signUp);
        startPage = new QWidget();
        startPage->setObjectName(QStringLiteral("startPage"));
        label_3 = new QLabel(startPage);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 90, 551, 111));
        QFont font;
        font.setPointSize(100);
        label_3->setFont(font);
        gridLayoutWidget_3 = new QWidget(startPage);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(220, 300, 322, 80));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(gridLayoutWidget_3);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QFont font1;
        font1.setPointSize(15);
        toolButton->setFont(font1);

        gridLayout_3->addWidget(toolButton, 0, 1, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget_3);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setFont(font1);

        gridLayout_3->addWidget(comboBox, 0, 0, 1, 1);

        toolButton_2 = new QToolButton(gridLayoutWidget_3);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setFont(font1);

        gridLayout_3->addWidget(toolButton_2, 0, 2, 1, 1);

        stackedWidget->addWidget(startPage);
        teacherPage = new QWidget();
        teacherPage->setObjectName(QStringLiteral("teacherPage"));
        dockWidget_2 = new QDockWidget(teacherPage);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setGeometry(QRect(0, 0, 201, 401));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        scrollArea = new QScrollArea(dockWidgetContents_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 181, 391));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 179, 389));
        scrollArea->setWidget(scrollAreaWidgetContents);
        dockWidget_2->setWidget(dockWidgetContents_2);
        dockWidget_3 = new QDockWidget(teacherPage);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidget_3->setGeometry(QRect(6, 410, 731, 331));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        tableView = new QTableView(dockWidgetContents_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 731, 141));
        dockWidget_3->setWidget(dockWidgetContents_3);
        scrollArea_2 = new QScrollArea(teacherPage);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(200, 30, 531, 371));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 529, 369));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        stackedWidget->addWidget(teacherPage);
        gamePage = new QWidget();
        gamePage->setObjectName(QStringLiteral("gamePage"));
        gridLayoutWidget_4 = new QWidget(gamePage);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 380, 711, 191));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        q3_Button = new QPushButton(gridLayoutWidget_4);
        q3_Button->setObjectName(QStringLiteral("q3_Button"));
        q3_Button->setIconSize(QSize(16, 16));

        gridLayout_4->addWidget(q3_Button, 1, 0, 1, 1);

        q2_Button = new QPushButton(gridLayoutWidget_4);
        q2_Button->setObjectName(QStringLiteral("q2_Button"));
        q2_Button->setIconSize(QSize(16, 16));

        gridLayout_4->addWidget(q2_Button, 0, 1, 1, 1);

        q1_Button = new QPushButton(gridLayoutWidget_4);
        q1_Button->setObjectName(QStringLiteral("q1_Button"));
        q1_Button->setIconSize(QSize(16, 16));

        gridLayout_4->addWidget(q1_Button, 0, 0, 1, 1);

        q4_Button = new QPushButton(gridLayoutWidget_4);
        q4_Button->setObjectName(QStringLiteral("q4_Button"));
        q4_Button->setIconSize(QSize(16, 16));

        gridLayout_4->addWidget(q4_Button, 1, 1, 1, 1);

        questionLabel = new QLabel(gamePage);
        questionLabel->setObjectName(QStringLiteral("questionLabel"));
        questionLabel->setGeometry(QRect(30, 30, 681, 331));
        questionLabel->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(gamePage);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
#ifndef QT_NO_TOOLTIP
        stackedWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("MainWindow", "Login", 0));
        lineEdit_4->setText(QString());
        lineEdit_4->setPlaceholderText(QApplication::translate("MainWindow", "Username", 0));
        lineEdit_5->setText(QString());
        lineEdit_5->setPlaceholderText(QApplication::translate("MainWindow", "Password", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Sign Up", 0));
        lineEdit_3->setPlaceholderText(QApplication::translate("MainWindow", "Confirm Password", 0));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Username", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Teacher", 0));
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Password", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Submit", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Cancel", 0));
        signUpLabel->setText(QApplication::translate("MainWindow", "Sign up:", 0));
        label_3->setText(QApplication::translate("MainWindow", "GAME TITLE", 0));
        toolButton->setText(QApplication::translate("MainWindow", "PLAY!", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Select Question Set", 0)
        );
        toolButton_2->setText(QApplication::translate("MainWindow", "My Profile", 0));
        q3_Button->setText(QApplication::translate("MainWindow", "Q3", 0));
        q2_Button->setText(QApplication::translate("MainWindow", "Q2", 0));
        q1_Button->setText(QApplication::translate("MainWindow", "Q1", 0));
        q4_Button->setText(QApplication::translate("MainWindow", "Q4", 0));
        questionLabel->setText(QApplication::translate("MainWindow", "Question Text", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
