#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent):
        image_(parent), bitimage_(parent),  bitmapPoint_(0,0)
{
    image_.show();
    pixelSpacingX_=pixelSpacingY_=1;
}

MyWidget::~MyWidget(){
}

void MyWidget::OpenAndEvaluate()
{
    ReadTextFile("point.txt");
    LoadDicomImage("CT-MONO2-8-abdo.dcm");
    CreateBinaryBitmap();
    QImage di=getOutputDicom();
    image_.setPixmap(QPixmap::fromImage(di));
    image_.setFixedSize(di.size());
    LoadBitmapBMP("bits.bmp");
    bitimage_.show();
    double mn, mx;
    dimage_->getMinMaxValues(mx,mn); // achtung kolejność
    int pxcount=0;
    double *min=&mn, *max=&mx;
    int *pxc=&pxcount;
    double average=calculateAverage(min,max,pxc);
    qDebug() << "average:" << average;
    qDebug() << "min:" << mn << "max" << mx;
    qDebug() << "pixel count:" << pxcount;
    qDebug() << "area:" << pxcount*pixelSpacingX_*pixelSpacingY_;
    qDebug() << "standard deviation:" << calculateStandardDeviation(average);
    update();
}

bool MyWidget::ReadTextFile(QString filename)
{
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return false;

        QVector<QString> tmp=QVector<QString>();
        QTextStream in(&file);
        QString line=in.readLine();
        while(!line.isNull()){
                tmp.append(line);
                line=in.readLine();
        }

        if(tmp.count()!=2)
            return false; //zly format pliku

        bitmapPoint_.setX(tmp.at(0).toInt());
        bitmapPoint_.setY(tmp.at(1).toInt());

        qDebug() << "bitmap starts at:" << bitmapPoint_;

        return true;
}

void MyWidget::LoadBitmapBMP(QString filename)
{
        QImage image;
        image.load(filename);
        bits_=image;
        bitimage_.setPixmap(QPixmap::fromImage(image));
        bitimage_.setFixedSize(image.size());
        if(!bitmapPoint_.isNull())
            bitimage_.setGeometry(QRect(bitmapPoint_.x(),bitmapPoint_.y(), image.width(), image.height()));
        update();
}

void MyWidget::CreateBinaryBitmap(){
        char* table=new char[bits_.width()*bits_.height()];
        for(int x=0; x<bitimage_.width(); x++){
                for(int y=0; y<bitimage_.height(); y++){
                    table[x+y*bits_.width()]=(QColor(bits_.pixel(x,y))==QColor(0,0,0))?1:0;
                }
        }
        QFile file("out.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        int size=bits_.width()*bits_.height();
        for(int i=0; i<size; ++i){
            out<< table[i];
            if(size%bits_.width()==0)
                out<< "\n";
        }

        file.close();
        qDebug() << "written successfully to file";
}

void MyWidget::LoadDicomImage(const char* filename, long flags, long fstart, long fcount)
{
        dimage_=new DicomImage(filename, flags, fstart, fcount);
        qDebug() << "frame count:" << dimage_->getFrameCount();
        qDebug() << "status:" << dimage_->getStatus();
}

QImage MyWidget::getOutputDicom(const unsigned long frame, const int planar)
{
        QImage img=QImage();
        //if(EIS_NORMAL == dimage_->getStatus()){
                qimageBuffer_=(uchar*)dimage_->getOutputData(8, frame, planar);
                pixelData_=(Uint8*)dimage_->getInterData()->getData();
                img=QImage(qimageBuffer_, dimage_->getWidth(), dimage_->getHeight(), dimage_->getWidth(), QImage::Format_Indexed8);
                //img=img.convertToFormat(QImage::Format_ARGB32);
        //}
        return img;
}

double MyWidget::calculateAverage(double *min, double *max, int *pixelCount)
{
        if(bitmapPoint_.isNull())
            return -1;
        double sum=0,avr=0, value;
        int width=bitimage_.width();
        int count=0;
        for(int x=bitmapPoint_.x(); x<bitimage_.width(); x++){
                for(int y=bitmapPoint_.y(); y<bitimage_.height(); y++){
                        if(isInROI(x,y)){
                                value=pixelData_[x+y*width];
                                sum+=value;
                                count++;
                                if(*min>value)
                                    *min=value;
                                if(*max<value)
                                    *max=value;
                        }
                }
        }
        *pixelCount=count;
        if(count==0)
            return -2;

        qDebug() << "sum:" << sum;
        qDebug() << "count:" << count;

        avr=sum/double(count);
        return avr;
}

double MyWidget::calculateStandardDeviation(double a)
{
    if(bitmapPoint_.isNull())
        return -1;
    int count=0;
    double v,variation=0.0,st_dev;
    int width=bitimage_.width();
    for(int x=bitmapPoint_.x(); x<bitimage_.width(); x++){
            for(int y=bitmapPoint_.y(); y<bitimage_.height(); y++){
                if(isInROI(x,y)){
                    v=pixelData_[x+y*width];
                    variation+=(v-a)*(v-a);
                    count++;
                }
            }
    }
    if(count!=0)
        variation=variation/count;
    st_dev=sqrt(variation);
    return st_dev;
}

bool MyWidget::isInROI(int x, int y)
{
        if(QColor(bits_.pixel(x,y))==QColor(0,0,0)){
//            bits_.setPixel(x,y,Qt::green);
            return true;
        }
//        bits_.setPixel(x,y,Qt::yellow);
        return false;
}
