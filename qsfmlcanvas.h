#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

/*
 * This class is to be inherited by any class that will be a SFML Render Window
 */

#include <SFML/Graphics.hpp>
#include <QTimer>
#include <qwidget.h>
#include <qtimer.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);

    virtual ~QSFMLCanvas();

private :

    //This method initializes the
    virtual void OnInit();

    virtual void OnUpdate();

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif // QSFMLCANVAS_H
