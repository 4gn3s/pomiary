#include <QtGui>
#include <QPushButton>
#include "MyWidget.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

        public:
                MainWindow(QWidget *parent=0);
                ~MainWindow();
  
        protected:
                MyWidget *myWidget_;
                QPushButton *button_;

};
