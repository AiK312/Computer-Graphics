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
    rect = (RECT*)(new int[sizeof(RECT)]);
    c = (POINT*)(new int[sizeof(POINT)]);
    ui->setupUi(this);
    srand(time(0));
}

Lab3::Lab3(QWidget *parent, QImage &imageFromMain) :
    QDialog(parent),
    image(&imageFromMain),
    ui(new Ui::Lab3)
{
    ui->setupUi(this);
    rect = (RECT*)(new int[sizeof(RECT)]);
    c = (POINT*)(new int[sizeof(POINT)]);
    srand(time(0));
}


Lab3::~Lab3()
{
    delete ui;
}

void Lab3::on_windowButton_clicked()
{
    rect->x_min = ui->windowXLEdit->text().toInt();
    rect->y_min = ui->windowYLEdit->text().toInt();
    rect->x_max = ui->windowXREdit->text().toInt();
    rect->y_max = ui->windowYREdit->text().toInt();

    QPainter *g = new QPainter(image);
    g->drawLine(rect->x_min, rect->y_min, rect->x_max, rect->y_min);
    g->drawLine(rect->x_max, rect->y_min, rect->x_max, rect->y_max);
    g->drawLine(rect->x_max, rect->y_max, rect->x_min, rect->y_max);
    g->drawLine(rect->x_min, rect->y_max, rect->x_min, rect->y_min);

    delete g;
    emit endFunc();

}

void Lab3::Colen_Sutherland(int x1, int y1, int x2, int y2)
{
    int code_a, code_b, code;
    code_a = VCODE(x1, y1);
    code_b = VCODE(x2, y2);

    if(code_a & code_b)
        return;

    while(code_a | code_b)
    {
        if(code_a)
        {
            code = code_a;
            c->x = x1;
            c->y = y1;
        }
        else
        {
            code = code_b;
            c->x = x2;
            c->y = y2;
        }

        if (code & LEFT)
        {
            c->y += (y1 - y2) * (rect->x_min - c->x) / (x1 - x2);
            c->x = rect->x_min;
        } else if (code & RIGHT) {
            c->y += (y1 - y2) * (rect->x_max - c->x) / (x1 - x2);
            c->x = rect->x_max;
        }/* если c ниже r, то передвигаем c на прямую y = r->y_min
                    если c выше r, то передвигаем c на прямую y = r->y_max */
        else if (code & BOT) {
            c->x += (x1 - x2) * (rect->y_max - c->y) / (y1 - y2);
            c->y = rect->y_max;
        } else if (code & TOP) {
            c->x += (x1 - x2) * (rect->y_min - c->y) / (y1 - y2);
            c->y = rect->y_min;
        }

        /* обновляем код */
        if (code == code_a) {
            x1 = c->x;
            y1 = c->y;
            code_a = VCODE(x1, y1);
        } else {
            x2 = c->x;
            y2 = c->y;
            code_b = VCODE(x2, y2);
        }

    }

    QPainter *g = new QPainter(image);
    QColor color(255, 0, 0, 255);
    g->setPen(color);
    g->drawLine(x1, y1, x2, y2);
    delete g;
}

int Lab3::VCODE(int x, int y)
{
    int result = 0;
    if(x < rect->x_min)
        result += LEFT;
    if(x > rect->x_max)
        result += RIGHT;
    if(y < rect->y_min)
        result += TOP;
    if(y > rect->y_max)
        result += BOT;
    return result;
}

void Lab3::on_areaButton_clicked()
{
    int count = ui->countSideLine->text().toInt();
    int h = image->height();
    int w = image->width();
    int x1=0, x2=0, y1=0, y2=0;

    coordinateList = new QMap<int, int>();
    QMap<int, int>::iterator it;

    for(int i = 0; i < count; i++)
    {
         coordinateList->insert(1+rand()%(w-1), 1+rand()%(h-1));
    }

    for(it = coordinateList->begin(); it != coordinateList->end(); it++)
    {
        if(it == coordinateList->end()-1)
        {
            x1 = it.key();
            y1 = it.value();
            it = coordinateList->begin();
            x2 = it.key();
            y2 = it.value();
            it = coordinateList->end()-1;

        }
        else
        {
            x1 = it.key();
            y1 = it.value();
            it++;
            x2 = it.key();
            y2 = it.value();
            it--;
        }
        QPainter *g = new QPainter(image);
        g->drawLine(x1,y1,x2,y2);
        delete g;
        Colen_Sutherland(x1, y1, x2, y2);
        emit endFunc();
    }
    emit endFunc();
}
