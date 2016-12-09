#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title = "Login";
    setWindowTitle(title);
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    ui->managePushButton->hide();

    setupConnectAndActions();

    gameScore = 0;
    highScore = 1000;

    aspectRatioWidth = 16;
    aspectRatioHeight = 9;

    worldInitialized = false;
    isTeacher = false;
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::setupConnectAndActions()
{
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(pageChanged(int)));
}

void MainWindow::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->signUpPage);
}

void MainWindow::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_submitButton_clicked()
{
    isTeacher = ui->teacherCheckBox->isChecked();
    QTimer::singleShot(0, this, SLOT(signUpToServer()));

    ui->stackedWidget->setCurrentWidget(ui->startPage);
}


void MainWindow::on_teacherPageRemoveButton_clicked()
{
    //Remove row from table
    QTimer::singleShot(0, this, SLOT(removeStudent()));
    //Call (using single shot) removeStudent from database using serverRequest()
}

void MainWindow::on_loginButton_clicked()
{
    //Start loginToServer() method on a new thread using a singleShot from QTimer
    //This keeps GUI responsive.
    QTimer::singleShot(0, this, SLOT(loginToServer()));
}

void MainWindow::on_playToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
}

void MainWindow::on_logOutPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_statsPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->statsPage);
    QTimer::singleShot(0, this, SLOT(populateStats()));
}

void MainWindow::on_leaderboardPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->leaderboardPage);
    QTimer::singleShot(0, this, SLOT(populateLeaderboards()));
}

void MainWindow::on_stats_backToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    ui->statsTableWidget->clearContents();
}

void MainWindow::on_managePushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->teacherPage);
    QTimer::singleShot(0, this, SLOT(populateManageboards()));
}

void MainWindow::on_teachers_backToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    ui->teacherTableWidget->clearContents();
}

void MainWindow::on_leaderboard_backToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    ui->leaderboardTableWidget->clearContents();
}

void MainWindow::on_startScreenPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::on_restartPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
}

void MainWindow::on_endGamePushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);
    emit gameEnded();

    endGame();
}

void MainWindow::pageChanged(int pageIndex)
{
    QString windowTitle;
    switch(pageIndex)
    {
        case pages::loginPage: //loginPage
        {
            isTeacher = false;
            setWindowTitle(windowTitle = "Login");
            break;
        }
        case pages::signUpPage: //signUpPage:
        {
            ui->teacherCheckBox->setChecked(false);
            setWindowTitle(windowTitle = "Sign Up");
            break;
        }

        case pages::startPage: //startPage
        {
            if(isTeacher)
                ui->managePushButton->show();
            else
                ui->managePushButton->hide();
            setWindowTitle(windowTitle = "Start Menu");
            break;
        }

        case pages::teacherPage: //teacherPage
            setWindowTitle(windowTitle = "Teachers Page");
        break;

        case pages::statsPage: //statsPage
            setWindowTitle(windowTitle = "Stats");
        break;

        case pages::leaderboardPage: //leaderboardPage
            setWindowTitle(windowTitle = "Leaderboards");
        break;

        case pages::gamePage: //gamePage
        {
            ui->answerLineEdit->clear();
            setWindowTitle(windowTitle = "Game");
            startGame();
            forceFocus(ui->answerLineEdit);
            break;
        }

        case pages::gameOverPage: //gameOverPage
            setWindowTitle(windowTitle = "Game Over");
        break;
    }
}
//Helps preserve the aspect ration while the window is resized.
void MainWindow::resizeEvent(QResizeEvent*)
{
    //ui->gameRenderFrame->resize(width() - 50, height() - 200);
    //world->reSize(width() - 50, height() - 200);
    if(worldInitialized)
    {
        ui->gameRenderFrame->setMinimumHeight(height() * 0.66);
        ui->gameRenderFrame->setMinimumWidth(width() * 0.95);
        world->resize(ui->gameRenderFrame->width(), ui->gameRenderFrame->height());
    }
}

void MainWindow::startGame()
{

    if(!worldInitialized)
    {
    world = new World(ui->gameRenderFrame, QPoint(0, 0), QSize(2000, 800));
    world->show();
    world->start();
    ui->gameRenderFrame->setMinimumHeight(height() * 0.66);
    world->resize(ui->gameRenderFrame->width(), ui->gameRenderFrame->height());
    QObject::connect(this, SIGNAL(answerEntered(QString)), world, SLOT(answerEntered(QString)));
    QObject::connect(world, SIGNAL(outOfHealth()), this, SLOT(gameOver()));
    QObject::connect(world, SIGNAL(scoreChanged(int)), this, SLOT(scoreChanged(int)));
    QObject::connect(this, SIGNAL(gameEnded()), world, SLOT(gameEnded()));
    QObject::connect(world, SIGNAL(phaseChanged(int,int)), this, SLOT(phaseChanged(int, int)));

    worldInitialized = true;
    }
    else {
        world->start();
    }

    ui->answerLineEdit->setFocus();
    gameScore = 0;


}

QString MainWindow::serverRequest(std::string request)
{
  //establish connection on the socket.
  status = socket.connect("127.0.0.1", 5016);
  if(status != sf::Socket::Done)
  {
      std::cout << "Couldn't connect" << std::endl;
  }

  ///TEST CODE
//    std::string s = "loginUser|" + user.toStdString() + "|" + pass.toStdString();
//    std::string s = "addStudent|"+ user.toStdString() + "|" + pass.toStdString() + "|" + "Test Names Mc Gee" + "|" + "1" + "|" + "why do we have a class code";
//    std::string s = "addGame|"+ std::to_string(151) + "|" + std::to_string(3503) + "|" + std::to_string(12);
//    std::string s = "getGameInfo|"+ std::to_string(298);
//    std::string s = "getHighScoreGameIDS|"+ std::to_string(20);
//    std::string s = "getTotalScore|"+ std::to_string(76);
//    std::string s = "getGamesPlayed|"+ std::to_string(142);
//    std::string s = "getAverageScore|"+ std::to_string(109);
//    std::string s = "removeStudent|"+ std::to_string(45);
//    std::string s = "getGameIDS|"+ std::to_string(109);
//    std::string s = "getStudentIDS";
  ///TEST CODE

  std::string s = request;

  //Use Packets to send to the server.
  //That way we don't have to worry about collecting a full packet.
  sf::Packet sendPacket;

  sendPacket << s;
  status = socket.send(sendPacket);
  if(status != sf::Socket::Done)
  {
      std::cout << "Couldn't send message to server" << std::endl;
  }

  //Receive a packet.
  sf::Packet recPacket;
  status = socket.receive(recPacket);
  if(status != sf::Socket::Done)
  {
      std::cout << "Didn't receive anything from server" << std::endl;
  }
  else
  {
      //This means that the connection was successfull and we received data back from server.
      std::string s;

      while(!recPacket.endOfPacket())
        recPacket >> s; QString qs(s.c_str()); qDebug() << qs; return qs;
  }
}

//This method attempts to login to the server.
void MainWindow::loginToServer()
{
    //Build string to send.
    QString user = ui->login_userNameText->text();
    QString pass = ui->login_passwordText->text();

    QString responseUserID = serverRequest("loginUser|" + user.toStdString() + "|" + pass.toStdString());

    if(responseUserID.toInt() > 0)
    {
       qDebug() << QString::fromStdString("logged in successfully."); userID = responseUserID.toInt(); qDebug() << userID;
       isTeacher = serverRequest("getStudentInfo|" + QString::number(userID).toStdString()).split("|").at(4) == "1";
       qDebug() << "we a teacher now";

       //ui->stackedWidget->setCurrentWidget(ui->startPage);
    }
    else
    {
      qDebug() << "Invalid username or password";
    }
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::signUpToServer()
{
    //Build string to send.
    QString user = ui->signup_userNameText->text();

    QString pass = ui->signup_passwordText->text();
    QString confPass = ui->signup_confirmPasswordText->text();
    bool teacherBool = ui->teacherCheckBox->isChecked();

    if(pass == confPass)
    {
      if(serverRequest("addStudent|" + user.toStdString() + "|" + pass.toStdString() + "|" + "N/A" + "|" + (teacherBool ? "1" : "0") + "|" + "N/A").toInt() > 0)
        qDebug() << QString::fromStdString("signed up successfully."); //ui->stackedWidget->setCurrentWidget(ui->loginPage);
    }

    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::populateStats()
{
   //Get User's Game ID's to get info on.
   QString gIDToProcess = serverRequest("getGameIDS|" + QString::number(userID).toStdString());
   QStringList splitGIDToProcess = gIDToProcess.split("|");

   //List of responses with each game's info played by the user.
   QStringList gIDInfoList;

   for (int i = 0; i < splitGIDToProcess.size(); ++i)
   {
       gIDInfoList.append(serverRequest("getGameInfo|" + ((QString)splitGIDToProcess.at(i)).toStdString() ) );
   }

   ui->statsTableWidget->setRowCount(gIDInfoList.size());

   QTableWidgetItem* newItem;
   for (int i = 0; i < gIDInfoList.size(); ++i)
   {
       //Split game into info.
       QStringList info = ((QString)gIDInfoList.at(i)).split("|");

       //Check if info is valid
       if(info.at(4) == "1")
       {
         //Game Number
         newItem = new QTableWidgetItem(tr("%1").arg(i + 1));
         ui->statsTableWidget->setItem(i,0, newItem);

         //Score
         newItem = new QTableWidgetItem(tr("%1").arg(info.at(2)));
         ui->statsTableWidget->setItem(i,1, newItem);

         //Level
         newItem = new QTableWidgetItem(tr("%1").arg(info.at(3)));
         ui->statsTableWidget->setItem(i,2, newItem);
       }
   }
}

void MainWindow::populateLeaderboards()
{
  //Get User's Game ID's to get info on. "10" is how many scores we want.
  QString gIDToProcess = serverRequest("getHighScoreGameIDS|10");
  QStringList splitGIDToProcess = gIDToProcess.split("|");

  //List of responses with each game's info played by the user.
  QStringList gIDInfoList;

  for (int i = 0; i < splitGIDToProcess.size(); ++i)
  {
      gIDInfoList.append(serverRequest("getGameInfo|" + ((QString)splitGIDToProcess.at(i)).toStdString() ) );
  }

  ui->leaderboardTableWidget->setRowCount(gIDInfoList.size());

  QTableWidgetItem* newItem;
  for (int i = 0; i < gIDInfoList.size(); ++i)
  {
      //Split game into info.
      QStringList info = ((QString)gIDInfoList.at(i)).split("|");

      //Check if info is valid
      if(info.at(4) == "1")
      {
        //Player
        QString username = serverRequest("getStudentInfo|" + ((QString)info.at(1)).toStdString() ).split("|").at(1);
        newItem = new QTableWidgetItem(tr("%1").arg(username));
        ui->leaderboardTableWidget->setItem(i,0, newItem);

        //Score
        newItem = new QTableWidgetItem(tr("%1").arg(info.at(2)));
        ui->leaderboardTableWidget->setItem(i,1, newItem);

        //Level
        newItem = new QTableWidgetItem(tr("%1").arg(info.at(3)));
        ui->leaderboardTableWidget->setItem(i,2, newItem);
      }
  }
}

void MainWindow::populateManageboards()
{
    //Get User's Game ID's to get info on. "10" is how many scores we want.
    QString allIDs = serverRequest("getStudentIDS|");
    QStringList splitIDToProcess = allIDs.split("|");

    //List of responses with each game's info played by the user.
    QStringList StudentsInfoList;

    for (int i = 0; i < splitIDToProcess.size(); ++i)
    {
        StudentsInfoList.append(serverRequest("getStudentInfo|" + ((QString)splitIDToProcess.at(i)).toStdString() ) );
    }

    ui->teacherTableWidget->setRowCount(StudentsInfoList.size());

    QTableWidgetItem* newItem;
    for (int i = 0; i < StudentsInfoList.size(); ++i)
    {
        //Split game into info.
        QStringList info = ((QString)StudentsInfoList.at(i)).split("|");

        //Check if info is valid
        if(info.at(6) == "1")
        {
          //Player
          QString Scores = serverRequest("getAverageScore|" + ((QString)info.at(0)).toStdString() ).split("|").at(0);
          QString acountType;
          QString gameCount = serverRequest("getGamesPlayed|" + ((QString)info.at(0)).toStdString() ).split("|").at(0);

          QString totalScore = serverRequest("getTotalScore|" + ((QString)info.at(0)).toStdString() ).split("|").at(0);
          if (info.at(4)=="1")
          {
              acountType = "Teacher";
          }
          else
          {
              acountType = "Student";
          }

          newItem = new QTableWidgetItem(tr("%1").arg(acountType));
          ui->teacherTableWidget->setItem(i,0, newItem);

          //Username
          newItem = new QTableWidgetItem(tr("%1").arg(info.at(1)));
          ui->teacherTableWidget->setItem(i,1, newItem);

          newItem = new QTableWidgetItem(tr("%1").arg(gameCount));
          ui->teacherTableWidget->setItem(i,2, newItem);

          newItem = new QTableWidgetItem(tr("%1").arg(totalScore));
          ui->teacherTableWidget->setItem(i,3, newItem);

          newItem = new QTableWidgetItem(tr("%1").arg(Scores));
          ui->teacherTableWidget->setItem(i,4, newItem);

          //Password
          newItem = new QTableWidgetItem(tr("%1").arg(info.at(2)));
          ui->teacherTableWidget->setItem(i,5, newItem);
        }
    }
}

void MainWindow::removeStudent()
{
  if(ui->teacherTableWidget->currentRow() > 0)
  {
     int userIDToRemove = serverRequest("loginUser|" + ui->teacherTableWidget->item(ui->teacherTableWidget->currentRow(), 1)->text().toStdString() + "|" +
                                                       ui->teacherTableWidget->item(ui->teacherTableWidget->currentRow(), 5)->text().toStdString()).toInt();

     //Tell Server to delete student from database
     serverRequest("removeStudent|" + QString::number(userIDToRemove).toStdString());

     //Delete row and select no row.
     ui->teacherTableWidget->removeRow(ui->teacherTableWidget->currentRow());
     ui->teacherTableWidget->selectRow(0);
  }
}

void MainWindow::on_answerLineEdit_returnPressed()
{
    emit answerEntered(ui->answerLineEdit->text());
    ui->answerLineEdit->clear();
}

void MainWindow::gameOver()
{
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);
    endGame();
}

void MainWindow::scoreChanged(int s)
{
    gameScore = s;
}

void MainWindow::phaseChanged(int phase, int operand)
{
    std::cout << "got the phase and operand" << std::endl;
    QString currentOperator;
    if(phase == 1)
    {
        currentOperator = "+";
    }
    else if (phase == 2)
    {
        currentOperator = "*";
    }
    else
    {
        currentOperator = "^2";
    }
    if (phase >= 3)
    {
        ui->operatorLabel->setText(QString("Ball ") + currentOperator);
    }
    else
    {
        ui->operatorLabel->setText(QString::number(operand) + currentOperator);
    }
}

void MainWindow::endGame()
{
    if(gameScore > highScore)
    {
        highScore = gameScore;
        QPalette palette = ui->gameOver_HighScoreLabel->palette();
        palette.setColor(ui->gameOver_HighScoreLabel->foregroundRole(), Qt::red);
        ui->gameOver_HighScoreLabel->setPalette(palette);
    }
    else
    {
        QPalette palette = ui->gameOver_HighScoreLabel->palette();
        palette.setColor(ui->gameOver_HighScoreLabel->foregroundRole(), Qt::black);
        ui->gameOver_HighScoreLabel->setPalette(palette);
    }

    ui->gameOver_HighScoreLabel->setText("High Score: " + QString::number(highScore));
    ui->gameOver_ScoreLabel->setText("Score: " + QString::number(gameScore));
}

void MainWindow::on_muteButton_clicked()
{
    emit world->toggleSound();
}

void MainWindow::on_openInBrowserButton_clicked()
{
    emit world->openBrowser();
}

void MainWindow::forceFocus(QWidget* widget)
{
    // unless set active, no stable set focus here
    widget->activateWindow();
    // the event object is released then in event loop (?)
    QFocusEvent* eventFocus = new QFocusEvent(QEvent::FocusIn);
    // posting event for forcing the focus with low priority
    qApp->postEvent(widget, (QEvent *)eventFocus, Qt::LowEventPriority);
}

