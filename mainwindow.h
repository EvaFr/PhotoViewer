#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QtWidgets>
#include <QScrollArea>
#include <qnamespace.h>
#include <QtCore/QDateTime>
#include <QDirIterator>
#include <QDebug>

#include "filemanagement.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//value of the int argc, char *argv[] paramters
    int numOfParams;
    std::vector<std::string> params;
    void resetParams(){params.clear();}

private:
    Ui::MainWindow *ui;

    QGroupBox *horizontalGroupBox;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QLabel *imageTitle;

    QLabel *imageLabel;
    QScrollArea *scrollArea;

    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionHelp;
    QAction *actionAbout;

    QAction *actionOrderingByName;
    QAction *actionOrderingByTime;
    QAction *actionDisplayStrecht;
    QAction *actionDisplayCenter;
    QAction *actionDisplayFit;

    QAction *actionNext;
    QAction *actionPrevious;

    void createMenu();
    void createToolBar();

//*****************
    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent *event);

//****************

    QImage image;

    FileManagementType fileManagement;
    SettingsType settings;

    QStringList imageTypes;
    void setImageTypes();

    int imageNum;
    QString imageName;
    QString pathName;
    Qt::AspectRatioMode asp;
    int imageWidth, imageHeight;

    void loadImage();
    void loadFiles(QStringList dir);
    void setAspectRatio();
    void setAlignment();
    void setImageSize();

    void getImageName();
    void setImage();
    void drawImage();
    void setTitle();


private slots:
    void exit();
    void open();
    void help();
    void about();

    void orderingByName();
    void orderingByTime();
    void displayStrecht();
    void displayCenter();
    void displayFit();
    void nextImage();
    void previousImage();

};

#endif // MAINWINDOW_H
