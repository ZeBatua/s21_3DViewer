#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QSettings>
#include <QTimer>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include "glwidget.h"

extern "C" {
#include "c_part/matrix.h"
#include "c_part/parser.h"
#include "c_part/render.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  float scale_reduction = 0;
  float scale_increase = 0;
  float move_x_sum = 0;
  float move_y_sum = 0;
  float move_z_sum = 0;
  float move_x_sub = 0;
  float move_y_sub = 0;
  float move_z_sub = 0;
  float count = 0;
  QString file_name = "";
  QTimer *timer;
  QVector<QImage> gif;
  void set_info(QString path);

 public slots:
  void openFile();
  void zoomIn();
  void zoomOut();
  void moveX();
  void moveY();
  void moveZ();
  void moveX_sub();
  void moveY_sub();
  void moveZ_sub();

  void setDashLine();
  void setSolidLine();
  void setEmptyLine();
  void setThickLine();

  void setOrbPoint();
  void setEmptyPoint();
  void setSquarePoint();
  void setThickPoint();
  void setProjection();

  void setLineColor();
  void setPointcolor();
  void setBackColor();

  void createScreen();
  void createGIF();
  void timerRun();
  void makeGIF();

  void saveSetting();
  void loadSetting();
};

#endif  // MAINWINDOW_H
