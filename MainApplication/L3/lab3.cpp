#include "lab3.h"
#include "ui_lab3.h"

#define LEFT  1  /* двоичное 0001 */
#define RIGHT 2  /* двоичное 0010 */
#define BOT   4  /* двоичное 0100 */
#define TOP   8  /* двоичное 1000 */

Lab3::Lab3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lab3)
{
    image = new QImage();
    
    ui->setupUi(this);
}

Lab3::Lab3(QWidget *parent, QImage &imageFromMain) :
    QDialog(parent),
    image(&imageFromMain),
    ui(new Ui::Lab3)
{
    ui->setupUi(this);
    
}


Lab3::~Lab3()
{
    delete ui;
}

void Lab3::on_windowButton_clicked()
{
    
    int XL = ui->windowXLEdit->text().toInt();
    int YL = ui->windowYLEdit->text().toInt();
    int XR = ui->windowXREdit->text().toInt();
    int YR = ui->windowYREdit->text().toInt();
    
    rect = (RECT*)(new char[sizeof(RECT)]);
    rect->x_max = XR;
    rect->x_min = XL;
    rect->y_max = YR;
    rect->y_min = YL;
    
    QRgb black;
    black = qRgb(0, 0, 0);
    
    for(int i=0; i<4; i++)
    {
        int x1=0, x2=0, y=0, y1=0, y2=0;
        int x=0;
        switch (i) {
        case 0:
            x1 = XL;
            x2 = XR;
            y1 = YL;
            y2 = YL;
            drawLine(x1, y1, x2, y2, 'y', black);
            break;
        case 1:
            x1 = XR;
            x2 = XR;
            y1 = YL;
            y2 = YR;
            drawLine(x1, y1, x2, y2, 'x', black);
            
            break;
        case 2:
            x1 = XL;
            x2 = XR;
            y1 = YR;
            y2 = YR;
            drawLine(x1, y1, x2, y2, 'y', black);
            break;
        case 3:
            x1 = XL;
            x2 = XL;
            y1 = YL;
            y2 = YR;
            drawLine(x1, y1, x2, y2, 'x', black);
            break;
        default:
            break;
        }
    }
    
    emit endFunc();
    
    
}

void Lab3::on_lineButton_clicked()
{
    QRgb black;
    black = qRgb(0, 0, 0);
    QRgb red;
    red = qRgb(255, 0, 0);
    char ch = 'y';

    int P1x = ui->lineX0Edit->text().toInt();
    int P1y = ui->lineY0Edit->text().toInt();
    int P2x = ui->lineX1Edit->text().toInt();
    int P2y = ui->lineY1Edit->text().toInt();

    if(P1x > P2x)
    {
        int x = P1x;
        P1x = P2x;
        P2x = x;
        int y = P1y;
        P1y = P2y;
        P2y = y;
    }


    drawLine(P1x, P1y, P2x, P2y, ch, black);

    int val = KolSozLine(P1x, P1y, P2x, P2y);
    switch (val) {
    case -1:
        drawLine(P1x, P1y, P2x, P2y, ch, black);
        break;
    case 1:
        drawLine(P1x, P1y, P2x, P2y, ch, red);
        break;
    default:
        break;
    }

    emit endFunc();
}

int Lab3::Code(int x, int y)
{
    int c = 0;
    if(x < rect->x_min)
        c = c | LEFT;
    if(x > rect->x_max)
        c =  c | RIGHT;
    if(y < rect->y_min)
        c = c | TOP;
    if(y > rect->y_max)
        c = c | BOT;
    return c;
}

int Lab3::KolSozLine(int P1x, int P1y, int P2x, int P2y)
{
    QRgb red;
    red = qRgb(255,0,0);

    int C=0, Px = 0, Py = 0;
    int C1 = Code(P1x, P1y);
    int C2 = Code(P2x, P2y);

    while(C1 != 0 || C2 != 0)
    {
        if(C1 == 0 && C2 == 0)
        {
            return 1;
        }

        if((C1&C2) != 0)
        {
            return -1;
        }
        
        if (C1)
        {
            C = C1;
            Px = P1x;
            Py = P1y;
        }
        else if(C2)
        {
            C = C2;
            Px = P2x;
            Py = P2y;
        }
        
        if(C & LEFT)
        {
            Px = rect->x_min;
            //Py += (P1y-P2y)*(rect->x_min-Px)/(P1x- P2x);
            Py += (P2y - P1y) / (P2x - P1x) * (rect->x_min - P1x);
        }
        else
            if (C & RIGHT)
            {
                Px = rect->x_max;
                //Py += (P1y-P2y)*(rect->x_max-Px)/(P1x-P2x);
                Py += (P2y - P1y) / (P2x - P1x) * (rect->x_max - P1x);
            }
            else
                if(C & BOT)
                {
                    Py = rect->y_min;
                    //Px += (P1x-P2x)*(rect->y_min-Py)/(P1y-P2y);
                    Py += (P2y - P1y) / (P2x - P1x) * (rect->y_min - P1x);
                }
                else
                    if(C & TOP)
                    {
                        Py = rect->y_max;
                        //Px += (P1x-P2x)*(rect->y_max-Py)/(P1y-P2y);
                        Py += (P2y - P1y) / (P2x - P1x) * (rect->y_max - P1x);
                    }

        if(C == C1)
        {
            P1x = Px;
            P1y = Py;
            C1 = Code(P1x, P1y);
        }
        else
        {
            P2x = Px;
            P2y = Py;
            C2 = Code(P2x, P2y);
        }
    }
    drawLine(P1x, P1y, P2x, P2y, 'y', red);
    return 0;
}

void Lab3::drawLine(int x1, int y1, int x2, int y2, char ch, QRgb color)
{
    double x=0, y=0;
    switch (ch) {
    case 'y':
        for(x = x1; x<x2; x+=0.01)
        {
            y = ((x-x1)*(y2-y1)) / (x2-x1) + y1;
            image->setPixel(x, y, color);
        }
        break;
    case 'x':
        for(y=y1; y<y2; y+=0.01)
        {
            x = ((x2-x1)*(y2-y1)) / (y2-y1) + x1;
            image->setPixel(x, y, color);
        }
        break;
    default:
        QMessageBox::information(this, "Warning", "Bad parameter. Need x or y.");
        break;
    }
}



