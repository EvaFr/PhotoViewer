#include "mainwindow.h"
#include "ui_mainwindow.h"


/*
- Recognize changes on the file system and update display accordingly
- Test environment and test cases
- Error handling
- comment
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   QHBoxLayout* layoutH0 = new QHBoxLayout;
   QHBoxLayout* layoutH1 = new QHBoxLayout;
   QVBoxLayout* layoutV = new QVBoxLayout;

   QWidget *centralWidget = new QWidget(this);
   QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
   imageTitle = new QLabel;
   imageTitle->setText("");

   createMenu();
   createToolBar();

   menuBar->setFixedWidth(200);
   layoutH0->addWidget(menuBar);
   layoutH0->addWidget(ui->mainToolBar);
   layoutH0->addWidget(imageTitle);

   scrollArea = new QScrollArea;
   imageLabel = new QLabel;

   scrollArea->setBackgroundRole(QPalette::Light);
   scrollArea->setWidget(imageLabel);
   scrollArea->setVisible(true);
   layoutH1->addWidget(scrollArea);

   layoutV->addLayout(layoutH0);
   layoutV->addLayout(layoutH1);

    mainLayout->addLayout(layoutV);

    setCentralWidget(centralWidget);
    show();

    setImageTypes();
    imageNum = 0;

    if (params.size() > 0){
        bool b0 = true;
        std::string s;
        s.clear();
        if (params.size() == 3){

            if ((params[1] == "0")||(params[1] == displayToStretch)) settings.setDisplayType(toStretch);
            else if ((params[1] == "1")||(params[1] == displayToCenter)) settings.setDisplayType(toCenter);
            else if ((params[1] == "2")||(params[1] == displayToFit)) settings.setDisplayType(toFit);

            QStringList ss0;
            ss0.clear();
            ss0.append(QString::fromStdString(params[0]));
            loadFiles(ss0);

            if ((params[2] == "0")||(params[2] == orderingName)) settings.setFileOrdering(byName);
            else if ((params[2] == "1")||(params[2] == orderingTime)) settings.setFileOrdering(byTime);

            if (fileManagement.getNumOfFiles() == 0) b0 = false;
            else {
               fileManagement.orderFiles(settings.getFileOrdering());
               imageNum = 0;
               getImageName();
               loadImage();
            }
       }
       else b0 = false;
       if ((!b0)&&(params.size() != 0)){
           if (params.size() != 3) {
               QMessageBox::information(this, QGuiApplication::applicationDisplayName(),tr("Bad parameters"));
           }
           else {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),tr("Bad path"));
           }
       }
    }

   }

    void MainWindow::resizeEvent(QResizeEvent* event){
     //    QMainWindow::resizeEvent(event);
          setImage();
    }
    void MainWindow::keyPressEvent(QKeyEvent *event){
         if((event->key() == Qt::Key_Left)||(event->key() == Qt::Key_PageUp)){
             previousImage();
         }
         else if ((event->key() == Qt::Key_Right)||(event->key() == Qt::Key_PageDown)){
             nextImage();
         }
         else if (event->key() == Qt::Key_Home){
             imageNum = 0;
             getImageName();
             loadImage();
         }
         else if (event->key() == Qt::Key_End){
             imageNum = fileManagement.getNumOfFiles() - 1;
             getImageName();
             loadImage();
         }
    }

   void MainWindow::setTitle(){
       QString s;
       s = QString::fromStdString(fileManagement.getName(imageNum)) + "  " +
           QString::fromStdString(fileManagement.getCreationTime(imageNum));
       imageTitle->setText(s);
   }

   void MainWindow::setImage(){
       if (!image.isNull()) {
          setAspectRatio();
          setAlignment();
          setImageSize();

          QImage img0 = image.scaled(imageWidth, imageHeight, asp);

          imageLabel->setPixmap(QPixmap::fromImage(img0));
          scrollArea->setVisible(true);

          imageLabel->adjustSize();
          setTitle();
       }
   }

   void MainWindow::loadImage(){
       if (!imageName.isEmpty()) {
           QImageReader reader(imageName);
           reader.setAutoTransform(true);
           image = reader.read();
           if (image.isNull()) {
               QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                            tr("Cannot load %1: %2").arg(QDir::toNativeSeparators(imageName), reader.errorString()));
           }
           else {
             setWindowTitle(pathName);
             setImage();
           }
       }
   }

   void MainWindow::setImageTypes(){
       QString si;
       for (int j = 0; j <  ImageFileTypesNum; j++) {
           si = QString::fromStdString(ImageFileTypes[j]);
           imageTypes.append(si);
       }
   }

   void MainWindow::getImageName(){
      imageName = QString::fromStdString(fileManagement.getImageName(imageNum));
      pathName = QString::fromStdString(fileManagement.getPath(imageNum));
      QString s = QString::fromStdString(fileManagement.getName(imageNum));
      pathName.remove(s);
   }

   void MainWindow::drawImage(){
     getImageName();
     loadImage();
   }

   void MainWindow::loadFiles(QStringList dir){
       FileType f0;

       fileManagement.reset();
       for (int i = 0; i < dir.size(); i++){
           setWindowTitle(dir[i]);
           QDirIterator it(dir[i], imageTypes, QDir::Files, QDirIterator::Subdirectories);
           while (it.hasNext()){
               QFileInfo InfoAboutCurrentFile (it.next());
               QDateTime fileCreated = InfoAboutCurrentFile.created();
               f0.setCreationTime(fileCreated.toString().toStdString());

               f0.set(it.filePath().toStdString(),it.fileName().toStdString() ,fileCreated.toTime_t());
               fileManagement.push_back(f0);
            //   f0.print();
           }
       }

       fileManagement.orderFiles(settings.getFileOrdering());
       imageNum = 0;
       getImageName();
       loadImage();
   }

//****** private slots*************
    void MainWindow::exit(){qApp->quit();}

    void MainWindow::open(){
        QFileDialog dialog(this);

        dialog.setFileMode(QFileDialog::Directory);
        QStringList dirNames;
        if (dialog.exec()) dirNames = dialog.selectedFiles();
        loadFiles(dirNames);
    }

    void MainWindow::help(){

        const char * c =  helpText.c_str();
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr(c));

    }
    void MainWindow::about(){
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("About PhotoViewer\nHomework program\nAuthor: Eva Katai\n "));

    }

    void MainWindow::orderingByName(){
        settings.setFileOrdering(byName);
        fileManagement.orderFiles(settings.getFileOrdering());
//        fileManagement.print();
        imageNum = 0;
        getImageName();
        loadImage();
    }
    void MainWindow::orderingByTime(){
        settings.setFileOrdering(byTime);
        fileManagement.orderFiles(settings.getFileOrdering());
      //  fileManagement.print();
        imageNum = 0;
        getImageName();
        loadImage();
    }
    void MainWindow::displayStrecht(){
        settings.setDisplayType(toStretch);
        setImage();
    }
    void MainWindow::displayCenter(){
        settings.setDisplayType(toCenter);
        setImage();
    }
    void MainWindow::displayFit(){
        settings.setDisplayType(toFit);
        setImage();
    }

    void MainWindow::nextImage(){
        if (imageNum < fileManagement.getNumOfFiles() - 1) {
            imageNum++;
            getImageName();
            loadImage();
        }
    }
    void MainWindow::previousImage(){
        if (imageNum > 0) {
            imageNum--;
            getImageName();
            loadImage();
        }
    }
//*********************************
void MainWindow::createToolBar(){

    actionOrderingByName = new QAction("&Name", this);
    actionOrderingByName->setToolTip("Ordedring by name");
    connect(actionOrderingByName, SIGNAL(triggered()), this, SLOT(orderingByName()));

    actionOrderingByTime = new QAction("&Time", this);
    connect(actionOrderingByTime, SIGNAL(triggered()), this, SLOT(orderingByTime()));
    actionOrderingByTime->setToolTip("Ordering by time");

    actionDisplayStrecht = new QAction("&Strecht", this);
    connect(actionDisplayStrecht, SIGNAL(triggered()), this, SLOT(displayStrecht()));
    actionDisplayStrecht->setToolTip("Strecht");

    actionDisplayCenter = new QAction("&Center", this);
    connect(actionDisplayCenter, SIGNAL(triggered()), this, SLOT(displayCenter()));
    actionDisplayCenter->setToolTip("Center");

    actionDisplayFit = new QAction("&Fit", this);
    connect(actionDisplayFit, SIGNAL(triggered()), this, SLOT(displayFit()));
    actionDisplayFit->setToolTip("Fit");

    actionNext = new QAction("&Next", this);
    connect(actionNext, SIGNAL(triggered()), this, SLOT(nextImage()));
    actionNext->setToolTip("Next image");

    actionPrevious = new QAction("&Prev", this);
    connect(actionPrevious, SIGNAL(triggered()), this, SLOT(previousImage()));
    actionPrevious->setToolTip("Previous image");

    actionOpen->setToolTip("Open files");

    ui->mainToolBar->addAction(actionOpen);
    ui->mainToolBar->addAction(actionOrderingByName);
    ui->mainToolBar->addAction(actionOrderingByTime);
    ui->mainToolBar->addAction(actionDisplayStrecht);
    ui->mainToolBar->addAction(actionDisplayCenter);
    ui->mainToolBar->addAction(actionDisplayFit);
    ui->mainToolBar->addAction(actionNext);
    ui->mainToolBar->addAction(actionPrevious);

}

void MainWindow::createMenu(){
   menuBar = new QMenuBar;

//*******File Menu***********
    fileMenu = new QMenu(tr("&File"), this);

    actionOpen = fileMenu->addAction(tr("O&pen"));
    actionExit = fileMenu->addAction(tr("E&xit"));

    connect(actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(exit()));

//*******Help Menu***********
    helpMenu = new QMenu(tr("&Help"), this);

    actionHelp = helpMenu->addAction(tr("H&elp"));
    actionAbout = helpMenu->addAction(tr("A&bout"));

    connect(actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));

//*****
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);
}

//****
void MainWindow::setAspectRatio(){
    if (settings.getDisplayType() == toStretch) asp = Qt::IgnoreAspectRatio;
    else if(settings.getDisplayType() == toCenter) asp = Qt::KeepAspectRatio;
    else if(settings.getDisplayType() == toFit) asp = Qt::KeepAspectRatioByExpanding;
}
void MainWindow::setAlignment(){
    if (settings.getDisplayType() == toStretch) imageLabel->setAlignment(Qt::AlignCenter);
    else if(settings.getDisplayType() == toCenter)imageLabel->setAlignment(Qt::AlignCenter);
    else if(settings.getDisplayType() == toFit) imageLabel->setAlignment(Qt::AlignCenter);
}
void MainWindow::setImageSize(){
    if (settings.getDisplayType() == toStretch) {
       imageWidth = this->width()- 40; imageHeight =  this->height() -80;
    }
    else if(settings.getDisplayType() == toCenter){
       imageWidth = this->width()- 40; imageHeight =  this->height() -80;
    }
    else if(settings.getDisplayType() == toFit) {
       if (!image.isNull()) {
          if (image.height() != 0){
             double r = image.width();
             r /= image.height();
             if (r < 0.01) r = 1;
             imageWidth = this->width()- 40;
             imageHeight = (this->height() - 80)/r;
          }
          else {imageWidth = image.width(); imageHeight = image.height();}
       }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
