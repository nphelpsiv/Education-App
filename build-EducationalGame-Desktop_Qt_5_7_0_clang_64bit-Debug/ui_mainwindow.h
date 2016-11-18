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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEnd_Game;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLineEdit *login_userNameText;
    QPushButton *loginButton;
    QLineEdit *login_passwordText;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *signUpButton;
    QSpacerItem *verticalSpacer_4;
    QWidget *signUpPage;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *gridLayout_2;
    QLineEdit *signup_passwordText;
    QLineEdit *signup_userNameText;
    QLineEdit *signup_confirmPasswordText;
    QLabel *signUpLabel;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *cancelButton;
    QPushButton *submitButton;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_6;
    QWidget *startPage;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *gameTitleLabel;
    QSpacerItem *verticalSpacer_2;
    QToolButton *playToolButton;
    QSpacerItem *verticalSpacer;
    QPushButton *statsPushButton;
    QPushButton *leaderboardPushButton;
    QSpacerItem *verticalSpacer_11;
    QPushButton *logOutPushButton;
    QSpacerItem *verticalSpacer_7;
    QWidget *statsPage;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_13;
    QLabel *stats_HighScoreLabel;
    QToolButton *stats_backToolButton;
    QTableWidget *statsTableWidget;
    QWidget *leaderboardPage;
    QVBoxLayout *verticalLayout_8;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_14;
    QToolButton *leaderboard_backToolButton;
    QLabel *leaderboard_HighScoreLabel;
    QSpacerItem *horizontalSpacer_15;
    QTableWidget *leaderboardTableWidget;
    QWidget *gamePage;
    QVBoxLayout *verticalLayout_6;
    QPushButton *endGamePushButton;
    QWidget *gameWidget;
    QGroupBox *workPlaceGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QWidget *gameOverPage;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayout;
    QLabel *gameOverLabel;
    QGridLayout *gridLayout_7;
    QLabel *gameOver_ScoreLabel;
    QLabel *gameOver_HighScoreLabel;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_10;
    QGridLayout *gridLayout_5;
    QPushButton *restartPushButton;
    QPushButton *startScreenPushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_9;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(778, 628);
        actionEnd_Game = new QAction(MainWindow);
        actionEnd_Game->setObjectName(QStringLiteral("actionEnd_Game"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setMinimumSize(QSize(760, 588));
        stackedWidget->setSizeIncrement(QSize(1, 1));
        loginPage = new QWidget();
        loginPage->setObjectName(QStringLiteral("loginPage"));
        verticalLayout_7 = new QVBoxLayout(loginPage);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        login_userNameText = new QLineEdit(loginPage);
        login_userNameText->setObjectName(QStringLiteral("login_userNameText"));

        gridLayout->addWidget(login_userNameText, 0, 1, 1, 1);

        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName(QStringLiteral("loginButton"));

        gridLayout->addWidget(loginButton, 0, 2, 1, 1);

        login_passwordText = new QLineEdit(loginPage);
        login_passwordText->setObjectName(QStringLiteral("login_passwordText"));

        gridLayout->addWidget(login_passwordText, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        signUpButton = new QPushButton(loginPage);
        signUpButton->setObjectName(QStringLiteral("signUpButton"));

        verticalLayout_3->addWidget(signUpButton, 0, Qt::AlignHCenter);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        stackedWidget->addWidget(loginPage);
        signUpPage = new QWidget();
        signUpPage->setObjectName(QStringLiteral("signUpPage"));
        verticalLayout_5 = new QVBoxLayout(signUpPage);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        signup_passwordText = new QLineEdit(signUpPage);
        signup_passwordText->setObjectName(QStringLiteral("signup_passwordText"));
        signup_passwordText->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(signup_passwordText, 3, 1, 1, 1);

        signup_userNameText = new QLineEdit(signUpPage);
        signup_userNameText->setObjectName(QStringLiteral("signup_userNameText"));
        signup_userNameText->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(signup_userNameText, 2, 1, 1, 1);

        signup_confirmPasswordText = new QLineEdit(signUpPage);
        signup_confirmPasswordText->setObjectName(QStringLiteral("signup_confirmPasswordText"));
        signup_confirmPasswordText->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(signup_confirmPasswordText, 4, 1, 1, 1);

        signUpLabel = new QLabel(signUpPage);
        signUpLabel->setObjectName(QStringLiteral("signUpLabel"));

        gridLayout_2->addWidget(signUpLabel, 1, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 2, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        cancelButton = new QPushButton(signUpPage);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton, 0, Qt::AlignHCenter);

        submitButton = new QPushButton(signUpPage);
        submitButton->setObjectName(QStringLiteral("submitButton"));

        horizontalLayout_3->addWidget(submitButton, 0, Qt::AlignHCenter);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        stackedWidget->addWidget(signUpPage);
        startPage = new QWidget();
        startPage->setObjectName(QStringLiteral("startPage"));
        verticalLayout_4 = new QVBoxLayout(startPage);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gameTitleLabel = new QLabel(startPage);
        gameTitleLabel->setObjectName(QStringLiteral("gameTitleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gameTitleLabel->sizePolicy().hasHeightForWidth());
        gameTitleLabel->setSizePolicy(sizePolicy);
        gameTitleLabel->setSizeIncrement(QSize(1, 1));
        QFont font;
        font.setPointSize(100);
        gameTitleLabel->setFont(font);
        gameTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(gameTitleLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        playToolButton = new QToolButton(startPage);
        playToolButton->setObjectName(QStringLiteral("playToolButton"));
        QFont font1;
        font1.setPointSize(50);
        playToolButton->setFont(font1);

        verticalLayout_2->addWidget(playToolButton, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        statsPushButton = new QPushButton(startPage);
        statsPushButton->setObjectName(QStringLiteral("statsPushButton"));
        statsPushButton->setMinimumSize(QSize(125, 0));

        verticalLayout_2->addWidget(statsPushButton, 0, Qt::AlignHCenter);

        leaderboardPushButton = new QPushButton(startPage);
        leaderboardPushButton->setObjectName(QStringLiteral("leaderboardPushButton"));
        leaderboardPushButton->setMinimumSize(QSize(125, 0));
        leaderboardPushButton->setSizeIncrement(QSize(0, 0));

        verticalLayout_2->addWidget(leaderboardPushButton, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        verticalSpacer_11 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_11);

        logOutPushButton = new QPushButton(startPage);
        logOutPushButton->setObjectName(QStringLiteral("logOutPushButton"));
        logOutPushButton->setMinimumSize(QSize(125, 0));

        verticalLayout_2->addWidget(logOutPushButton, 0, Qt::AlignHCenter);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);


        verticalLayout_4->addLayout(verticalLayout_2);

        stackedWidget->addWidget(startPage);
        statsPage = new QWidget();
        statsPage->setObjectName(QStringLiteral("statsPage"));
        verticalLayout_10 = new QVBoxLayout(statsPage);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 0, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_13, 0, 3, 1, 1);

        stats_HighScoreLabel = new QLabel(statsPage);
        stats_HighScoreLabel->setObjectName(QStringLiteral("stats_HighScoreLabel"));

        gridLayout_3->addWidget(stats_HighScoreLabel, 0, 2, 1, 1);

        stats_backToolButton = new QToolButton(statsPage);
        stats_backToolButton->setObjectName(QStringLiteral("stats_backToolButton"));

        gridLayout_3->addWidget(stats_backToolButton, 0, 0, 1, 1);


        verticalLayout_10->addLayout(gridLayout_3);

        statsTableWidget = new QTableWidget(statsPage);
        if (statsTableWidget->columnCount() < 4)
            statsTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        statsTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        statsTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        statsTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        statsTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        statsTableWidget->setObjectName(QStringLiteral("statsTableWidget"));
        statsTableWidget->setSizeIncrement(QSize(0, 0));

        verticalLayout_10->addWidget(statsTableWidget);

        stackedWidget->addWidget(statsPage);
        leaderboardPage = new QWidget();
        leaderboardPage->setObjectName(QStringLiteral("leaderboardPage"));
        verticalLayout_8 = new QVBoxLayout(leaderboardPage);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_14, 0, 1, 1, 1);

        leaderboard_backToolButton = new QToolButton(leaderboardPage);
        leaderboard_backToolButton->setObjectName(QStringLiteral("leaderboard_backToolButton"));

        gridLayout_6->addWidget(leaderboard_backToolButton, 0, 0, 1, 1);

        leaderboard_HighScoreLabel = new QLabel(leaderboardPage);
        leaderboard_HighScoreLabel->setObjectName(QStringLiteral("leaderboard_HighScoreLabel"));

        gridLayout_6->addWidget(leaderboard_HighScoreLabel, 0, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_15, 0, 3, 1, 1);


        verticalLayout_8->addLayout(gridLayout_6);

        leaderboardTableWidget = new QTableWidget(leaderboardPage);
        if (leaderboardTableWidget->columnCount() < 3)
            leaderboardTableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        leaderboardTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        leaderboardTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        leaderboardTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        leaderboardTableWidget->setObjectName(QStringLiteral("leaderboardTableWidget"));

        verticalLayout_8->addWidget(leaderboardTableWidget);

        stackedWidget->addWidget(leaderboardPage);
        gamePage = new QWidget();
        gamePage->setObjectName(QStringLiteral("gamePage"));
        verticalLayout_6 = new QVBoxLayout(gamePage);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        endGamePushButton = new QPushButton(gamePage);
        endGamePushButton->setObjectName(QStringLiteral("endGamePushButton"));

        verticalLayout_6->addWidget(endGamePushButton, 0, Qt::AlignRight);

        gameWidget = new QWidget(gamePage);
        gameWidget->setObjectName(QStringLiteral("gameWidget"));

        verticalLayout_6->addWidget(gameWidget);

        workPlaceGroupBox = new QGroupBox(gamePage);
        workPlaceGroupBox->setObjectName(QStringLiteral("workPlaceGroupBox"));
        workPlaceGroupBox->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_4 = new QHBoxLayout(workPlaceGroupBox);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(workPlaceGroupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_16);

        label_2 = new QLabel(workPlaceGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineEdit = new QLineEdit(workPlaceGroupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);


        verticalLayout_6->addWidget(workPlaceGroupBox);

        stackedWidget->addWidget(gamePage);
        gameOverPage = new QWidget();
        gameOverPage->setObjectName(QStringLiteral("gameOverPage"));
        verticalLayout_9 = new QVBoxLayout(gameOverPage);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_8);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gameOverLabel = new QLabel(gameOverPage);
        gameOverLabel->setObjectName(QStringLiteral("gameOverLabel"));
        gameOverLabel->setFont(font);
        gameOverLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(gameOverLabel);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gameOver_ScoreLabel = new QLabel(gameOverPage);
        gameOver_ScoreLabel->setObjectName(QStringLiteral("gameOver_ScoreLabel"));

        gridLayout_7->addWidget(gameOver_ScoreLabel, 0, 3, 1, 1);

        gameOver_HighScoreLabel = new QLabel(gameOverPage);
        gameOver_HighScoreLabel->setObjectName(QStringLiteral("gameOver_HighScoreLabel"));

        gridLayout_7->addWidget(gameOver_HighScoreLabel, 0, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_11, 0, 2, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_10, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_7);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_10);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        restartPushButton = new QPushButton(gameOverPage);
        restartPushButton->setObjectName(QStringLiteral("restartPushButton"));

        gridLayout_5->addWidget(restartPushButton, 0, 2, 1, 1);

        startScreenPushButton = new QPushButton(gameOverPage);
        startScreenPushButton->setObjectName(QStringLiteral("startScreenPushButton"));

        gridLayout_5->addWidget(startScreenPushButton, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_5);


        verticalLayout_9->addLayout(verticalLayout);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_9);

        stackedWidget->addWidget(gameOverPage);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Main Window", 0));
        actionEnd_Game->setText(QApplication::translate("MainWindow", "End Game", 0));
#ifndef QT_NO_TOOLTIP
        stackedWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        login_userNameText->setText(QString());
        login_userNameText->setPlaceholderText(QApplication::translate("MainWindow", "Username", 0));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0));
        login_passwordText->setText(QString());
        login_passwordText->setPlaceholderText(QApplication::translate("MainWindow", "Password", 0));
        signUpButton->setText(QApplication::translate("MainWindow", "Sign Up", 0));
        signup_passwordText->setPlaceholderText(QApplication::translate("MainWindow", "Password", 0));
        signup_userNameText->setPlaceholderText(QApplication::translate("MainWindow", "Username", 0));
        signup_confirmPasswordText->setPlaceholderText(QApplication::translate("MainWindow", "Confirm Password", 0));
        signUpLabel->setText(QApplication::translate("MainWindow", "Sign up:", 0));
        cancelButton->setText(QApplication::translate("MainWindow", "Cancel", 0));
        submitButton->setText(QApplication::translate("MainWindow", "Submit", 0));
        gameTitleLabel->setText(QApplication::translate("MainWindow", "GAME TITLE", 0));
        playToolButton->setText(QApplication::translate("MainWindow", "PLAY!", 0));
        statsPushButton->setText(QApplication::translate("MainWindow", "My Stats", 0));
        leaderboardPushButton->setText(QApplication::translate("MainWindow", "Leaderboard", 0));
        logOutPushButton->setText(QApplication::translate("MainWindow", "Logout", 0));
        stats_HighScoreLabel->setText(QApplication::translate("MainWindow", "High Score:", 0));
        stats_backToolButton->setText(QApplication::translate("MainWindow", "Back", 0));
        QTableWidgetItem *___qtablewidgetitem = statsTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Game ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = statsTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Player", 0));
        QTableWidgetItem *___qtablewidgetitem2 = statsTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Score", 0));
        QTableWidgetItem *___qtablewidgetitem3 = statsTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Elapsed Time", 0));
        leaderboard_backToolButton->setText(QApplication::translate("MainWindow", "Back", 0));
        leaderboard_HighScoreLabel->setText(QApplication::translate("MainWindow", "High Score:", 0));
        QTableWidgetItem *___qtablewidgetitem4 = leaderboardTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Player", 0));
        QTableWidgetItem *___qtablewidgetitem5 = leaderboardTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Score", 0));
        QTableWidgetItem *___qtablewidgetitem6 = leaderboardTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Elapsed Time", 0));
        endGamePushButton->setText(QApplication::translate("MainWindow", "EndGame", 0));
        workPlaceGroupBox->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "Equation:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Answer", 0));
        gameOverLabel->setText(QApplication::translate("MainWindow", "GAME OVER!", 0));
        gameOver_ScoreLabel->setText(QApplication::translate("MainWindow", "Score:", 0));
        gameOver_HighScoreLabel->setText(QApplication::translate("MainWindow", "High Score:", 0));
        restartPushButton->setText(QApplication::translate("MainWindow", "Restart", 0));
        startScreenPushButton->setText(QApplication::translate("MainWindow", "Start Screen", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
