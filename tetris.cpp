#include "tetris.h"
#include "ui_tetris.h"
#include <QArrayData>

Tetris::Tetris(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tetris)
{
    ui->setupUi(this);

    setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
    setWindowTitle("Tetris -- ZRJ");
//            qDebug() << __cplusplus;

//        connect(push_button_1, &QPushButton::clicked, this, &Tetris::drop_pic);

//        random seed


    initial_widget();


    QTimer *time1 = new QTimer(this);
    time1->start(speed);
    connect(time1, &QTimer::timeout, this, &Tetris::drop_pic);

    initial_point_ctrl();  //this function should be call only once at the begin of program


}

Tetris::~Tetris()
{
    delete ui;
}



void Tetris::initial_widget()
{

    Line_edit_1->move(0, 1040);
    Line_edit_1->resize(240, 80);
    Line_edit_1->setFont(QFont("Consolas", 12));
    Line_edit_1->setReadOnly(true);
    Line_edit_1->show();
    Line_edit_1->setFocusPolicy(Qt::NoFocus);

    Line_edit_2->move(240, 1040);
    Line_edit_2->resize(560, 80);
    Line_edit_2->setFont(QFont("Consolas", 12));
    Line_edit_2->setReadOnly(true);
    Line_edit_2->show();
    Line_edit_2->setFocusPolicy(Qt::NoFocus);

    Line_edit_3->move(560, 1040);
    Line_edit_3->resize(240, 80);
    Line_edit_3->setFont(QFont("Consolas", 12));
    Line_edit_3->setReadOnly(true);
    Line_edit_3->show();
    Line_edit_3->setFocusPolicy(Qt::NoFocus);
    /////////////////////////////////////////////////////////////////

    push_button_1->move(0, 1120);
    push_button_1->resize(200, 80);
    push_button_1->setFont(QFont("Consolas", 12));
    push_button_1->show();
    push_button_1->setFocusPolicy(Qt::NoFocus);

    push_button_2->move(200, 1120);
    push_button_2->resize(200, 80);
    push_button_2->setFont(QFont("Consolas", 12));
    push_button_2->show();
    push_button_2->setFocusPolicy(Qt::NoFocus);

    push_button_3->move(400, 1120);
    push_button_3->resize(200, 80);
    push_button_3->setFont(QFont("Consolas", 12));
    push_button_3->show();
    push_button_3->setFocusPolicy(Qt::NoFocus);

    push_button_4->move(600, 1120);
    push_button_4->resize(200, 80);
    push_button_4->setFont(QFont("Consolas", 12));
    push_button_4->show();
    push_button_4->setFocusPolicy(Qt::NoFocus);

    Line_edit_3->setText("Speed : " + QString::number((5000 - speed)/1000) + " Lv");
}

void Tetris::paintEvent(QPaintEvent *)
{
    paint_board();
    paint_move_pic();
    check_if_touch_bottom();
    check_if_line_full();

}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    move_change_pic( event->key() );
    finally_move_pic(event->key());
    update();
}

void Tetris::paint_board()
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::darkCyan, 2));
    for( int i = 0; i <= ROW_COUNT; i++ )
    {
        painter.drawLine(0, i*BLOCK_SIDE_LENGTH, BOARD_WIDTH, i*BLOCK_SIDE_LENGTH); //ROW
        if(i <= COLUMN_COUNT)
        {
            painter.drawLine(i*BLOCK_SIDE_LENGTH, 0, i*BLOCK_SIDE_LENGTH, BOARD_HEIGHT - SCORE_PANEL_HEIGHT);
        }
    }
    painter.setPen(QPen(Qt::red, 4));
    painter.drawLine(0, 160, 800, 160);
    update();
}

void Tetris::paint_move_pic(int pic_sel_, int col_sel_)
{
    //call initial function/////////////////////////////////////////////////////////////////change pic here
    if( create_flag == 1 )
    {
//        qsrand( QTime().currentTime().msec() % 100 );
//        picture_select =  ( qrand() % 5 );
        srand(time(nullptr));
        picture_select =  ( rand() % 5 );


//        qDebug() << "the number of pic_sel : " << picture_select;
//        system("pause");

        color_select = ( rand() % 3 );

        pic_sel_ = picture_select;
        col_sel_ = color_select;

        initial_point( col_sel_ , pic_sel_ );
        create_flag = 0;
    }
    interpreter_point();

    update();
}

void Tetris::interpreter_point()
{
    QPainter painter(this);
    painter.setBrush(Qt::red);
    for( int i = 0; i < 13; i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            if( point_ctrl[i][j].exist == 1 )
            {
                painter.drawRect(point_ctrl[i][j].x, point_ctrl[i][j].y, BLOCK_SIDE_LENGTH, BLOCK_SIDE_LENGTH);
            }
        }
    }
    update();
}

void Tetris::clear_full_line()
{
    if( clear_flag == 1 )
    {
        for( int i = clear_line_count; i >= 0; i-- )
        {
            for( int j = 0; j < 10; j++ )
            {
                if( ( point_ctrl[i][j].exist == 1 ) && ( point_ctrl[i][j].move == 0 ) )
                {
                    point_ctrl[i+1][j].exist = 1;
                    point_ctrl[i+1][j].move = 0;

                    point_ctrl[i][j].exist = 0;
                    point_ctrl[i][j].move = 0;
                }
            }
        }
        score += 10;
        Line_edit_1->setText("Score : " + QString::number(score) );
        clear_flag = 0;
        update();
    }
}

void Tetris::initial_point(int col_sel, int pic_sel )
{
    QPainter painter(this);
    switch (col_sel)
    {
    case 0:
        painter.setBrush(Qt::red);
        break;
    case 1:
        painter.setBrush(Qt::yellow);
        break;
    case 2:
        painter.setBrush(Qt::blue);
        break;
    case 3:
        painter.setBrush(Qt::black);
        break;
    default:
        break;
    }


    if(pic_sel == 0)
    {
        point_ctrl[1][3].exist = 1;
        point_ctrl[1][3].move = 1;
        point_ctrl[1][4].exist = 1;
        point_ctrl[1][4].move = 1;
        point_ctrl[1][5].exist = 1;
        point_ctrl[1][5].move = 1;
        point_ctrl[1][6].exist = 1;
        point_ctrl[1][6].move = 1;
    }
    else if (pic_sel == 1)
    {
        point_ctrl[0][4].exist = 1;
        point_ctrl[0][4].move = 1;
        point_ctrl[1][4].exist = 1;
        point_ctrl[1][4].move = 1;
        point_ctrl[0][5].exist = 1;
        point_ctrl[0][5].move = 1;
        point_ctrl[1][5].exist = 1;
        point_ctrl[1][5].move = 1;
    }
    else if (pic_sel == 2)
    {
        point_ctrl[1][4].exist = 1;
        point_ctrl[1][4].move = 1;
        point_ctrl[1][5].exist = 1;
        point_ctrl[1][5].move = 1;
        point_ctrl[1][6].exist = 1;
        point_ctrl[1][6].move = 1;
        point_ctrl[0][5].exist = 1;
        point_ctrl[0][5].move = 1;
    }
    else if (pic_sel == 3)
    {
        point_ctrl[1][4].exist = 1;
        point_ctrl[1][4].move = 1;
        point_ctrl[1][5].exist = 1;
        point_ctrl[1][5].move = 1;
        point_ctrl[0][5].exist = 1;
        point_ctrl[0][5].move = 1;
        point_ctrl[0][6].exist = 1;
        point_ctrl[0][6].move = 1;
    }
    else if (pic_sel == 4)
    {
        point_ctrl[1][4].exist = 1;
        point_ctrl[1][4].move = 1;
        point_ctrl[1][5].exist = 1;
        point_ctrl[1][5].move = 1;
        point_ctrl[1][6].exist = 1;
        point_ctrl[1][6].move = 1;
        point_ctrl[0][4].exist = 1;
        point_ctrl[0][4].move = 1;
    }
    else
    {

    }
}

void Tetris::initial_point_apex() //remove
{
    for( int i = 0; i < 10; i++ )
    {
        point_apex[i*80] = BOARD_HEIGHT - SCORE_PANEL_HEIGHT;
    }
}

void Tetris::initial_point_ctrl()
{
    for( int i = 0; i < 13; i++ )
    {
        for( int j = 0; j < 10; j++ )
        {
            point_ctrl[i][j].x = j*80;  // x -> row
            point_ctrl[i][j].y = i*80;  // y -> column
            point_ctrl[i][j].move = 0;
            point_ctrl[i][j].exist = 0;
        }
    }
}

void Tetris::drop_pic()
{
    for( int i = 12; i >= 0; i-- )
    {
        for( int j = 0; j < 10; j++ )
        {
            if( point_ctrl[i][j].move == 1)
            {
//                Point_c point_temp;
                int _x = point_ctrl[i][j].y/80;
                int _y = point_ctrl[i][j].x/80;

                point_ctrl[_x + 1][_y].exist = 1;
                point_ctrl[_x + 1][_y].move = 1;

                point_ctrl[i][j].exist = 0;
                point_ctrl[i][j].move = 0;
//                point_ctrl[i][j].y += BLOCK_SIDE_LENGTH;
            }
        }
    }
//    paint_move_pic();

    update();
    qDebug() << "this drop_func has run " << count++ << " times";
}

void Tetris::move_change_pic(int key_sel)
{
    //check
    check_if_touch_side();

    if(key_sel == Qt::Key_Left && move_left == 1)
    {
        for( int i = 0; i < 10; i++ )
        {
            for( int j = 0; j < 13; j++ )
            {
                if( point_ctrl[j][i].move == 1)
                {
                    int _x = point_ctrl[j][i].y/80;
                    int _y = point_ctrl[j][i].x/80;

                    point_ctrl[_x][_y - 1].exist = 1;
                    point_ctrl[_x][_y - 1].move = 1;

                    point_ctrl[j][i].exist = 0;
                    point_ctrl[j][i].move = 0;
                }
            }
        }
    }
    else if( key_sel == Qt::Key_Right && move_right == 1 )
    {
        for( int i = 9; i >= 0; i-- )
        {
            for( int j = 0; j < 13; j++ )
            {
                if( point_ctrl[j][i].move == 1)
                {
                    int _x = point_ctrl[j][i].y/80;
                    int _y = point_ctrl[j][i].x/80;

                    point_ctrl[_x][_y + 1].exist = 1;
                    point_ctrl[_x][_y + 1].move = 1;

                    point_ctrl[j][i].exist = 0;
                    point_ctrl[j][i].move = 0;
                }
            }
        }
    }
    else if(key_sel == Qt::Key_Down)
    {
        for( int i = 12; i >= 0; i-- )
        {
            for( int j = 0; j < 10; j++ )
            {
                if( point_ctrl[i][j].move == 1)
                {
                    //                Point_c point_temp;
                    int _x = point_ctrl[i][j].y/80;
                    int _y = point_ctrl[i][j].x/80;

                    point_ctrl[_x + 1][_y].exist = 1;
                    point_ctrl[_x + 1][_y].move = 1;

                    point_ctrl[i][j].exist = 0;
                    point_ctrl[i][j].move = 0;
                }
            }
        }
    }
    else if( key_sel == Qt::Key_Up)
    {
        if( picture_select == 0 )
        {

        }
        else if( picture_select == 1 )
        {

        }
        else if( picture_select == 2 )
        {

        }
        else if( picture_select == 3 )
        {

        }
        else if( picture_select == 4 )
        {

        }
        else if( picture_select == 5 )
        {

        }
    }
    else{ }
}

void Tetris::finally_move_pic( int key_sel )
{
    if( finally_move_flag == 1 )
    {
        //check
        check_if_touch_side();

        if(key_sel == Qt::Key_Left && move_left == 1)
        {
            for( int i = 0; i < 10; i++ )
            {
                for( int j = 0; j < 13; j++ )
                {
                    if( point_ctrl[j][i].exist == 0 && point_ctrl[j][i].move == 1)  //check the special status
                    {
                        int _x = point_ctrl[j][i].y/80;
                        int _y = point_ctrl[j][i].x/80;

                        point_ctrl[_x][_y - 1].exist = 1;
                        point_ctrl[_x][_y - 1].move = 1;

                        point_ctrl[j][i].exist = 0;
                        point_ctrl[j][i].move = 0;
                    }
                }
            }
        }
        else if( key_sel == Qt::Key_Right && move_right == 1 )
        {
            for( int i = 9; i >= 0; i-- )
            {
                for( int j = 0; j < 13; j++ )
                {
                    if( point_ctrl[j][i].exist == 0 && point_ctrl[j][i].move == 1)  //check the special status
                    {
                        int _x = point_ctrl[j][i].y/80;
                        int _y = point_ctrl[j][i].x/80;

                        point_ctrl[_x][_y + 1].exist = 1;
                        point_ctrl[_x][_y + 1].move = 1;

                        point_ctrl[j][i].exist = 0;
                        point_ctrl[j][i].move = 0;
                    }
                }
            }
        }
        finally_move_flag = 0;
    }
}

void Tetris::check_if_touch_bottom()
{
    int count{0};
    int push_flag = 0;
    QVector<Point_c> point_vec_tem;
    Point_c point_tem;
    for(int i = 0; i  < 10; i++ )   //column
    {
        count = 0;
        for( int j = 0; j < 13; j++ )  //row
        {
            if( point_ctrl[j][i].move == 1 )
            {
                push_flag = 1;
                if(count == 0 )
                {
                    point_tem.x = point_ctrl[j][i].x;
                    point_tem.y = point_ctrl[j][i].y;
                    point_tem.move = point_ctrl[j][i].move;
                    point_tem.exist = point_ctrl[j][i].exist;
                    count++;
                    continue;
                }
                if(point_ctrl[j][i].y > point_tem.y)
                {
                    point_tem.x = point_ctrl[j][i].x;
                    point_tem.y = point_ctrl[j][i].y;
                    point_tem.move = point_ctrl[j][i].move;
                    point_tem.exist = point_ctrl[j][i].exist;

                }

            }
        }
        if(push_flag == 1)
        {
            point_vec_tem.push_back(point_tem);
            push_flag = 0;
        }
    }

    //qDebug() << "sizeof this vector is : " << point_vec_tem.size();
    for(int i = 0; i < point_vec_tem.size(); i++)   //loop all the bottom point in vec
    {
        int _x = point_vec_tem[i].y/80;
        int _y = point_vec_tem[i].x/80;
        qDebug() << "This _x : "<< _x <<" this _y : "<<_y <<"  "<<point_vec_tem[i].y;
        qDebug() << "point_ctrl[_x+1][_y].y = " << point_ctrl[_x+1][_y].y;
        //system("pause");
        if( point_ctrl[_x+1][_y].exist == 1 || point_ctrl[_x][_y].y == 960 )
        {
            for( int j = 0; j < 13; j++ )  //if one point is seted, all move point should be seted
            {
                for( int k = 0; k < 10; k++)
                {
                    if(point_ctrl[j][k].move == 1)
                    {
                        // set the special status
                        point_ctrl[j][k].move = 1;
                        point_ctrl[j][k].exist = 0;
                        //make the finally move_pic
                        finally_move_flag = 1;
                        //return special status to common
                        point_ctrl[j][k].move = 0;
                        point_ctrl[j][k].exist = 1;

                        qDebug() << "The point of ( " << _x << ", " << _y <<" ) has been existed";
                    }
                }

            }
            set_flag = 1;
            //system("pause");
        }
    }
    point_vec_tem.clear();
    //the old move_pic has been set, then you should change create_flag in order to create a new move_pic
    if( set_flag == 1 )
    {
        create_flag = 1;
        set_flag = 0;
        qDebug() << "create a new pic ";
//        Sleep(1000);
        //system("pause");
    }
    update();
    //Sleep(1000);

}

void Tetris::check_if_line_full()
{
    int set_num;
    clear_count = 0;
    for( int i = 12; i >= 0; i-- )
    {
        set_num = 0;
        for( int j = 0; j < 10; j++ )
        {
            if( ( point_ctrl[i][j].exist == 1 ) && ( point_ctrl[i][j].move == 0 ) )
            {
                set_num++;
            }
        }
        if( set_num == 10 )
        {
            for( int k = 0; k < 10; k++ )
            {
                point_ctrl[i][k].exist = 0;
                point_ctrl[i][k].move = 0;

            }
            clear_count++;
            clear_flag = 1;
            clear_line_count = i;
//            qDebug() << "The check_if_line_full func run ";
            clear_full_line();
        }
    }

    update();

}

void Tetris::check_if_touch_side()
{
    move_right = 1;
    move_left = 1;
    //pack as a package     check move_left
    {
        move_to_side = 1;
        int count{0};
        int push_flag = 0;
        QVector<Point_c> point_vec_tem;
        Point_c point_tem;
        for(int i = 0; i  < 13; i++ )   //row
        {
            count = 0;
            for( int j = 0; j < 10; j++ )  //column
            {
                if( point_ctrl[i][j].move == 1 )
                {
                    push_flag = 1;
                    if(count == 0 )
                    {
                        point_tem.x = point_ctrl[i][j].x;
                        point_tem.y = point_ctrl[i][j].y;
                        point_tem.move = point_ctrl[i][j].move;
                        point_tem.exist = point_ctrl[i][j].exist;
                        count++;
                        continue;
                    }
                    if(point_ctrl[i][j].x < point_tem.x)
                    {
                        point_tem.x = point_ctrl[i][j].x;
                        point_tem.y = point_ctrl[i][j].y;
                        point_tem.move = point_ctrl[i][j].move;
                        point_tem.exist = point_ctrl[i][j].exist;

                    }

                }
            }
            if(push_flag == 1)
            {
                point_vec_tem.push_back(point_tem);
                push_flag = 0;
            }
        }

        //qDebug() << "sizeof this vector is : " << point_vec_tem.size();
        for(int i = 0; i < point_vec_tem.size(); i++)   //loop all the bottom point in vec
        {
            int _x = point_vec_tem[i].y/80;
            int _y = point_vec_tem[i].x/80;
            //        qDebug() << "This _x : "<< _x <<" this _y : "<<_y <<"  "<<point_vec_tem[i].y;
            //        qDebug() << "point_ctrl[_x+1][_y].y = " << point_ctrl[_x+1][_y].y;
            //        system("pause");
            if( point_ctrl[_x][_y - 1].exist == 1 || point_ctrl[_x][_y].x == 0 )
            {
                move_left = 0;
            }
        }
    }

    //pack as a package  check move_right
    {
        move_to_side = 1;
        int count{0};
        int push_flag = 0;
        QVector<Point_c> point_vec_tem;
        Point_c point_tem;
        for(int i = 12; i >= 0; i-- )   //row
        {
            count = 0;
            for( int j = 0; j < 10; j++ )  //column
            {
                if( point_ctrl[i][j].move == 1 )
                {
                    push_flag = 1;
                    if(count == 0 )
                    {
                        point_tem.x = point_ctrl[i][j].x;
                        point_tem.y = point_ctrl[i][j].y;
                        point_tem.move = point_ctrl[i][j].move;
                        point_tem.exist = point_ctrl[i][j].exist;
                        count++;
                        continue;
                    }
                    if(point_ctrl[i][j].x > point_tem.x)
                    {
                        point_tem.x = point_ctrl[i][j].x;
                        point_tem.y = point_ctrl[i][j].y;
                        point_tem.move = point_ctrl[i][j].move;
                        point_tem.exist = point_ctrl[i][j].exist;
                    }
                }
            }
            if(push_flag == 1)
            {
                point_vec_tem.push_back(point_tem);
                push_flag = 0;
            }
        }

        //qDebug() << "sizeof this vector is : " << point_vec_tem.size();
        for(int i = 0; i < point_vec_tem.size(); i++)   //loop all the bottom point in vec
        {
            int _x = point_vec_tem[i].y/80;
            int _y = point_vec_tem[i].x/80;
            //        qDebug() << "This _x : "<< _x <<" this _y : "<<_y <<"  "<<point_vec_tem[i].y;
            //        qDebug() << "point_ctrl[_x+1][_y].y = " << point_ctrl[_x+1][_y].y;
            //        system("pause");
            if( point_ctrl[_x][_y + 1].exist == 1 || point_ctrl[_x][_y].x == 720 )
            {
                move_right = 0;
            }
        }
    }





    update();
}
