#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTimer>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <vector>

#include "../Service/Includes/Common.h"
#include "../Service/Includes/DataDumper.h"
#include "../Service/Includes/DataTypes.h"
#include "../Service/Includes/Utils.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief The AnimStyle enum - enumerate animation types
 */
enum AnimStyle
{
    AS_BOTOM_TOP,   // from bottom to top
    AS_TOP_BOTTOM,  // from top to bottom
    AS_RIGHT_LEFT   // from right to left
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ReloadSettings();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

protected:
    /**
     * @brief AnimateFrameSwap
     * @param frame
     * @param speed
     * @param style
     */
    void AnimateFrameSwap(QWidget* frame, const int speed, AnimStyle style = AnimStyle::AS_RIGHT_LEFT);

    void ShowWidget(QWidget* widget);

private slots:
    /**
     * @brief on_btCancel_clicked - exit button event from login panel
     */
    void on_btCancel_clicked();

    /**
     * @brief on_btLogin_clicked - login button event
     */
    void on_btLogin_clicked();

    void on_btLock_clicked();

    void on_btExit_clicked();

   // void on_btSettings_clicked();

    void on_btWeb_clicked();

    void on_btApps_clicked();

    void on_btSettings_clicked();

    void on_txtPassword_returnPressed();

private:
    // active frame
    bool _swapped = true;

    // selected frame index
    int _currentFrame = 0;

    // animation speed
    const int _animSpeed = 500;

    // minimum & maximum window size
    const int _windowWidth = 850;
    const int _windowHeight = 540;

    // animation for widgets
    QPropertyAnimation* _animFrame1;
    QPropertyAnimation* _animFrame2;

    bool _Locked;
    QPoint _OldPoint;

    QWidget* _prevFrame;

    pAppData _appSettings;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
