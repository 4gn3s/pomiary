#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
{
        QWidget *centralWidget=new QWidget(this);
        setCentralWidget(centralWidget);

        myWidget_=new MyWidget(this);
        button_=new QPushButton(this);
        button_->setText("Open and evaluate");

        connect(button_, SIGNAL(clicked()), myWidget_, SLOT(OpenAndEvaluate()));

        QVBoxLayout *layout=new QVBoxLayout;
        layout->addWidget(myWidget_);
        layout->addWidget(button_);
        centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
}
