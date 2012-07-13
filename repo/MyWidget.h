#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <iostream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/ofstd/ofstring.h>
#include <dcmtk/ofstd/ofconsol.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmimgle/dcmimage.h>
//#include <dcmtk/dcmimage/diregist.h>
#include <dcmtk/dcmjpeg/djdecode.h>
#include <dcmtk/dcmdata/dcrledrg.h>

#include <dcmtk/dcmimgle/diciefn.h>
#include <dcmtk/dcmimgle/digsdfn.h>

class MyWidget : public QLabel
{
        Q_OBJECT

        public:
                MyWidget(QWidget *parent=0);
                ~MyWidget();

        public slots:
                void OpenAndEvaluate();

        protected:
                QLabel image_;
                QLabel bitimage_;
                QPoint bitmapPoint_;

        private:
                bool ReadTextFile(QString name);
                void LoadBitmapBMP(QString name);
                void CreateBinaryBitmap();
                void LoadDicomImage(const char* name, long flags=0, long fstart=0, long fount=0);
                QImage getOutputDicom(const unsigned long frame=0, const int planar=0);
                double calculateAverage(double *min, double *max, int *pixelCount);
                double calculateStandardDeviation(double average);
                bool isInROI(int x, int y);

                DicomImage *dimage_;
                uchar *qimageBuffer_;
                Uint8 *pixelData_;
                double pixelSpacingX_, pixelSpacingY_;
                QImage bits_;
};
