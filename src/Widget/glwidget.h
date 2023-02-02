#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

extern "C" {
#include "c_part/matrix.h"
#include "c_part/parser.h"
#include "c_part/render.h"
}

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 public:
  GLWidget(QWidget *parent = nullptr);

  void openFile();
  void getVertexArray();
  void getColorArray();

  void set_Line();
  void set_Point();

  QColor colorBack;
  QColor colorLine;
  QColor colorPoint;

  int lineType = 2;
  float lineWidth = 1;

  int pointType = 1;
  float pointWidth = 5;

  float *V_arr = NULL;
  unsigned int *F_arr = NULL;

  int projection_type = 0;

  void mulScaleChange(float value);
  void delScaleChange(float value);
  void addMoveChangeX(float value);
  void addMoveChangeY(float value);
  void addMoveChangeZ(float value);
  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;
  void change_projection();

  float xRot = 0;
  float yRot = 0;
  float zRot = 0;
  GLfloat rotationX;
  GLfloat rotationY;
  GLfloat rotationZ;
  QColor faceColors[6];
  QPoint lastPos;
  file_data data;
  QPoint mPos;

  enum {
    EMPTY = 0,
    POINT_ROUND = 1,
    POINT_QUADRO = 2,
    LINE_SOLID = 2,
    LINE_DASHED = 1,
    IS_CHECKED = 1
  };
};
#endif  // GLWIDGET_H
