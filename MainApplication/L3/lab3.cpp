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
    a = (POINT*)(new int[sizeof(POINT)]);
    b = (POINT*)(new int[sizeof(POINT)]);
    c = (POINT*)(new int[sizeof(POINT)]);
    ui->setupUi(this);
}

Lab3::Lab3(QWidget *parent, QImage &imageFromMain) :
    QDialog(parent),
    image(&imageFromMain),
    ui(new Ui::Lab3)
{
    ui->setupUi(this);
    rect = (RECT*)(new int[sizeof(RECT)]);
    a = (POINT*)(new int[sizeof(POINT)]);
    b = (POINT*)(new int[sizeof(POINT)]);
    c = (POINT*)(new int[sizeof(POINT)]);
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

void Lab3::on_lineButton_clicked()
{
    a->x = ui->lineX0Edit->text().toInt();
    a->y = ui->lineY0Edit->text().toInt();
    b->x = ui->lineX1Edit->text().toInt();
    b->y = ui->lineY1Edit->text().toInt();
    QPainter *g = new QPainter(image);
    g->drawLine(a->x, a->y, b->x, b->y);
    delete g;
    cohen_sutherland();
    emit endFunc();
}

int Lab3::cohen_sutherland()
{
    int code_a, code_b, code;
    code_a = vcode('a');
    code_b = vcode('b');

    while(code_a | code_b)
    {
        if(code_a)
        {
            code = code_a;
            c = a;
        }
        else
        {
            code = code_b;
            c = b;
        }

        if (code & LEFT)
        {
            c->y += (a->y - b->y) * (rect->x_min - c->x) / (a->x - b->x);
            c->x = rect->x_min;
        } else if (code & RIGHT) {
            c->y += (a->y - b->y) * (rect->x_max - c->x) / (a->x - b->x);
            c->x = rect->x_max;
        }/* если c ниже r, то передвигаем c на прямую y = r->y_min
                    если c выше r, то передвигаем c на прямую y = r->y_max */
        else if (code & BOT) {
            c->x += (a->x - b->x) * (rect->y_max - c->y) / (a->y - b->y);
            c->y = rect->y_max;
        } else if (code & TOP) {
            c->x += (a->x - b->x) * (rect->y_min - c->y) / (a->y - b->y);
            c->y = rect->y_min;
        }

        /* обновляем код */
        if (code == code_a) {
            a = c;
            code_a = vcode('a');
        } else {
            b = c;
            code_b = vcode('b');
        }

    }

    QPainter *g = new QPainter(image);
    QColor color(255, 0, 0, 255);
    g->setPen(color);
    g->drawLine(a->x, a->y, b->x, b->y);
    delete g;
}

int Lab3::vcode(char ch)
{
    int result = 0;
    switch (ch) {
    case 'a':
        if(a->x < rect->x_min)
            result += LEFT;
        if(a->x > rect->x_max)
            result += RIGHT;
        if(a->y < rect->y_min)
            result += TOP;
        if(a->y > rect->y_max)
            result += BOT;
        break;
    case 'b':
        if(b->x < rect->x_min)
            result += LEFT;
        if(b->x > rect->x_max)
            result += RIGHT;
        if(b->y < rect->y_min)
            result += TOP;
        if(b->y > rect->y_max)
            result += BOT;
        break;
    default:
        QMessageBox::information(this, "Warning", "Choose A or B in argument");
        break;
    }

return result;
}


