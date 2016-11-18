/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EducationalGame/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[394];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_signUpButton_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(4, 60, 23), // "on_submitButton_clicked"
QT_MOC_LITERAL(5, 84, 22), // "on_loginButton_clicked"
QT_MOC_LITERAL(6, 107, 25), // "on_playToolButton_clicked"
QT_MOC_LITERAL(7, 133, 27), // "on_logOutPushButton_clicked"
QT_MOC_LITERAL(8, 161, 26), // "on_statsPushButton_clicked"
QT_MOC_LITERAL(9, 188, 32), // "on_leaderboardPushButton_clicked"
QT_MOC_LITERAL(10, 221, 31), // "on_stats_backToolButton_clicked"
QT_MOC_LITERAL(11, 253, 37), // "on_leaderboard_backToolButton..."
QT_MOC_LITERAL(12, 291, 32), // "on_startScreenPushButton_clicked"
QT_MOC_LITERAL(13, 324, 28), // "on_restartPushButton_clicked"
QT_MOC_LITERAL(14, 353, 28), // "on_endGamePushButton_clicked"
QT_MOC_LITERAL(15, 382, 11) // "pageChanged"

    },
    "MainWindow\0on_signUpButton_clicked\0\0"
    "on_cancelButton_clicked\0on_submitButton_clicked\0"
    "on_loginButton_clicked\0on_playToolButton_clicked\0"
    "on_logOutPushButton_clicked\0"
    "on_statsPushButton_clicked\0"
    "on_leaderboardPushButton_clicked\0"
    "on_stats_backToolButton_clicked\0"
    "on_leaderboard_backToolButton_clicked\0"
    "on_startScreenPushButton_clicked\0"
    "on_restartPushButton_clicked\0"
    "on_endGamePushButton_clicked\0pageChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_signUpButton_clicked(); break;
        case 1: _t->on_cancelButton_clicked(); break;
        case 2: _t->on_submitButton_clicked(); break;
        case 3: _t->on_loginButton_clicked(); break;
        case 4: _t->on_playToolButton_clicked(); break;
        case 5: _t->on_logOutPushButton_clicked(); break;
        case 6: _t->on_statsPushButton_clicked(); break;
        case 7: _t->on_leaderboardPushButton_clicked(); break;
        case 8: _t->on_stats_backToolButton_clicked(); break;
        case 9: _t->on_leaderboard_backToolButton_clicked(); break;
        case 10: _t->on_startScreenPushButton_clicked(); break;
        case 11: _t->on_restartPushButton_clicked(); break;
        case 12: _t->on_endGamePushButton_clicked(); break;
        case 13: _t->pageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
