#include "lab4.h"
#include "ui_lab4.h"
# define M_PI           3.14159265358979323846  /* pi */


Lab4::Lab4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lab4),
    Px{{190,230,190,230},{190,230,190,230}},
    Py{{200,200,200,200},{250,250,250,250}},
    Pz{{0,0,20,20},{0,0,20,20}}
{
    image = new QImage();
    ui->setupUi(this);
}

Lab4::Lab4(QWidget *parent, QImage &imageFromMain) :
    QDialog(parent), image(&imageFromMain), ui(new Ui::Lab4),
    Px{{190,230,190,230},{190,230,190,230}},
    Py{{200,200,200,200},{250,250,250,250}},
    Pz{{0,0,20,20},{0,0,20,20}}

{
    ui->setupUi(this);
}


Lab4::~Lab4()
{
    delete ui;
}


void Lab4::on_buttonFigure_clicked()
{    
    Draw(Px, Py, Pz);
    emit endFunc();
    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(true);
}

void Lab4::on_zoomButton_clicked()
{
    double sx = ui->lineEdit->text().toDouble();
    double sy = ui->lineEdit->text().toDouble();
    double sz = ui->lineEdit->text().toDouble();

    int px = ui->linePX->text().toInt();
    int py = ui->linePY->text().toInt();
    int pz = ui->linePZ->text().toInt();

    int tX[2][4];
    int tY[2][4];
    int tZ[2][4];

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<4; j++)
        {
            tX[i][j] = Px[i][j];
            tY[i][j] = Py[i][j];
            tZ[i][j] = Pz[i][j];
        }
    }


    double Mashtab[4][4] = {{sx, 0, 0, (1-sx)*px},
                            {0, sy, 0, (1-sy)*py},
                            {0, 0, sz, (1-sz)*pz},
                            {0, 0, 0, 1}};
    double fun[4][1];
    double Fun[4][1];

    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fun[0][0] = tX[i][j];
            fun[1][0] = tY[i][j];
            fun[2][0] = tZ[i][j];
            fun[3][0] = 1;
            for(int I = 0; I<4; I++)
            {
                for(int J = 0; J<1; J++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        Fun[I][J] += Mashtab[I][k] * fun[k][J];
                    }
                }
            }

            tX[i][j] = (int)Fun[0][0];
            tY[i][j] = (int)Fun[1][0];
            tZ[i][j] = (int)Fun[2][0];

            for (int I = 0; I < 4; I++)
            {
                for (int J = 0; J < 1; J++)
                {
                    Fun[I][J] = 0;
                    fun[I][J] = 0;
                }
            }
        }
    }

    Draw(tX, tY, tZ);
    emit endFunc();
}


void Lab4::on_turnButton_clicked()
{
    int Q = ui->lineGrad->text().toInt();
    double Povorot[4][4] = {{cos(Q*M_PI/180), sin(Q*M_PI/180), 0, 0},
                            {-sin(Q*M_PI/180), cos(Q*M_PI/180),0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}

    };
    double fun[4][1];
    double Fun[4][1];

    int tX[2][4];
    int tY[2][4];
    int tZ[2][4];

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<4; j++)
        {
            tX[i][j] = Px[i][j];
            tY[i][j] = Py[i][j];
            tZ[i][j] = Pz[i][j];
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fun[0][0] = tX[i][j];
            fun[1][0] = tY[i][j];
            fun[2][0] = tZ[i][j];
            fun[3][0] = 1;

            for (int I = 0; I < 4; I++)
            {
                for (int J = 0; J < 1; J++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        Fun[I][J] += Povorot[I][k] * fun[k][J];
                    }
                }
            }

            tX[i][j] = Fun[0][0];
            tY[i][j] = Fun[1][0];
            tZ[i][j] = Fun[2][0];
            for (int I = 0; I < 4; I++)
            {
                for (int J = 0; J < 1; J++)
                {
                    Fun[I][J] = 0;
                    fun[I][J] = 0;
                }
            }
        }
    }

    Draw(tX, tY, tZ);
    emit endFunc();

}


void Lab4::on_translationButton_clicked()
{
    int sx = ui->lineX->text().toInt();
    int sy = ui->lineY->text().toInt();
    int sz = ui->lineZ->text().toInt();

    int tX[2][4];
    int tY[2][4];
    int tZ[2][4];

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<4; j++)
        {
            tX[i][j] = Px[i][j];
            tY[i][j] = Py[i][j];
            tZ[i][j] = Pz[i][j];
        }
    }


    double Translation[4][4] = {{1, 0, 0, sx},
                            {0, 1, 0, sy},
                            {0, 0, 1, sz},
                            {0, 0, 0, 1}};
    double fun[4][1];
    double Fun[4][1];

    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fun[0][0] = tX[i][j];
            fun[1][0] = tY[i][j];
            fun[2][0] = tZ[i][j];
            fun[3][0] = 1;
            for(int I = 0; I<4; I++)
            {
                for(int J = 0; J<1; J++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        Fun[I][J] += Translation[I][k] * fun[k][J];
                    }
                }
            }

            tX[i][j] = (int)Fun[0][0];
            tY[i][j] = (int)Fun[1][0];
            tZ[i][j] = (int)Fun[2][0];

            for (int I = 0; I < 4; I++)
            {
                for (int J = 0; J < 1; J++)
                {
                    Fun[I][J] = 0;
                    fun[I][J] = 0;
                }
            }
        }
    }

    Draw(tX, tY, tZ);
    emit endFunc();
}

void Lab4::Draw(int x[n][m], int y[n][m], int z[n][m])
{
    QPainter g(image);

    for(int i=0; i<2; i++)
    {
    for(int j=0; j<4; j++)
    {
        x[i][j] = x[i][j] - z[i][j]*cos(60*M_PI/180);
        y[i][j] = y[i][j] - z[i][j]*sin(60*M_PI/180);
    }
    }

    g.drawLine(x[0][0], y[0][0], x[0][1], y[0][1]);
    g.drawLine(x[0][2], y[0][2], x[0][3], y[0][3]);
    g.drawLine(x[0][0], y[0][0], x[0][2], y[0][2]);
    g.drawLine(x[0][1], y[0][1], x[0][3], y[0][3]);
    g.drawLine(x[1][0], y[1][0], x[1][1], y[1][1]);
    g.drawLine(x[1][2], y[1][2], x[1][3], y[1][3]);
    g.drawLine(x[1][0], y[1][0], x[1][2], y[1][2]);
    g.drawLine(x[1][1], y[1][1], x[1][3], y[1][3]);
    g.drawLine(x[0][0], y[0][0], x[1][0], y[1][0]);
    g.drawLine(x[0][1], y[0][1], x[1][1], y[1][1]);
    g.drawLine(x[0][2], y[0][2], x[1][2], y[1][2]);
    g.drawLine(x[0][3], y[0][3], x[1][3], y[1][3]);
}
