#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>
#include "config.h"
#include "point_c.h"
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMap>
#include <iostream>
#include <windows.h>
#include <QTime>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <ctime>

namespace Ui {
class Tetris;
}

class Tetris : public QWidget
{
    Q_OBJECT

public:
    explicit Tetris(QWidget *parent = nullptr );
    ~Tetris();

    //function function
    void initial_widget();
    void initial_point( int col_sel = 0, int pic_sel = 0);
    void initial_point_apex();
    void initial_point_ctrl();

    //draw function
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paint_board();
    void paint_move_pic(int pic_sel_ = 0, int col_sel_ = 0);
    void interpreter_point();

    void clear_full_line();

    //move function
    void drop_pic();
    void move_change_pic(int);

    void finally_move_pic(int key_sel);

    //check function
    void check_if_touch_bottom();
    void check_if_line_full();
    void check_if_touch_side();

private:
    Ui::Tetris *ui;
    //widget  ptr
    QLineEdit * Line_edit_1 = new QLineEdit("Score : 0", this);
    QLineEdit * Line_edit_2 = new QLineEdit("*********", this);
    QLineEdit * Line_edit_3 = new QLineEdit("Speed : 2", this);

    QPushButton *push_button_1 = new QPushButton("Start", this);
    QPushButton *push_button_2 = new QPushButton("Pause", this);
    QPushButton *push_button_3 = new QPushButton("ReStart", this);
    QPushButton *push_button_4 = new QPushButton("Setting", this);

    //data
    int count{0};
    QMap<int, int> point_apex;
    QPoint point_array[16];

    int score{0};
    int speed{1000};
    int color_select{0};
    int picture_select{0};

    int clear_line_count;


    //point_ctrl
    Point_c point_ctrl[13][10];
    //flag

    int create_flag{1};  //1 -> can, 0 -> can not
    int set_flag{0};   //1 -> set, 0 -> set not
    int clear_count{0};
    int clear_flag{0};  //1 -> clear, 0 -> can not
    int move_to_side{1}; //1 -> can, 0 -> can not
    int move_left{1};
    int move_right{1};
    int finally_move_flag{0};

};

#endif // TETRIS_H
