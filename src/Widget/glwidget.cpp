#include "glwidget.h"

#include "ui_glwidget.h"

int file_status = 0;

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget{parent} {}

void GLWidget::initializeGL() {
  glLoadIdentity();
  initializeOpenGLFunctions();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glTranslatef(0, 0, -3);

  colorBack = QColor(Qt::black);
  colorLine = QColor(Qt::green);
  colorPoint = QColor(Qt::darkGreen);
}

void GLWidget::openFile() {
  file_status = 1;
  update();
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(), 0);

  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, colorBack);
  setAutoFillBackground(true);
  setPalette(pal);

  if (file_status) V_arr = rewrite_matrix(&data);
  if (file_status) F_arr = write_facets(&data);

  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_MODELVIEW);
  glLineWidth(1);

  glLineWidth(lineWidth);
  glDisable(GL_LINE_STIPPLE);
  set_Line();
  update();
  glLineWidth(lineWidth);

  change_projection();

  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glVertexPointer(3, GL_FLOAT, 0, V_arr);
  if (file_status)
    glDrawElements(GL_LINES, data.full_amount_of_vertexes_in_facets * 2,
                   GL_UNSIGNED_INT, F_arr);

  if (pointType == 0) {
    glPointSize(0);
    glDisable(GL_POINT_SMOOTH);
  } else if (pointType == 1) {
    glDisable(GL_POINT_SMOOTH);
    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());
    glEnable(GL_POINT_SMOOTH);
    glPointSize(pointWidth);

    if (file_status)
      glDrawElements(GL_POINTS, data.full_amount_of_vertexes_in_facets * 2,
                     GL_UNSIGNED_INT, F_arr);
  } else if (pointType == 2) {
    glDisable(GL_POINT_SMOOTH);
    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());
    glPointSize(pointWidth);
    if (file_status)
      glDrawElements(GL_POINTS, data.full_amount_of_vertexes_in_facets * 2,
                     GL_UNSIGNED_INT, F_arr);
  }

  update();

  if (V_arr != NULL) {
    free(V_arr);
  }
  if (F_arr != NULL) {
    free(F_arr);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}
void GLWidget::resizeGL(int w, int h) {}

void GLWidget::mulScaleChange(float value) {
  zoomIn(&data, value);
  update();
}

void GLWidget::delScaleChange(float value) {
  zoomOut(&data, value);
  update();
}

void GLWidget::addMoveChangeX(float value) {
  moveX(&data, value);
  update();
}

void GLWidget::addMoveChangeY(float value) {
  moveY(&data, value);
  update();
}

void GLWidget::addMoveChangeZ(float value) {
  moveZ(&data, value);
  update();
}

void GLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  xRot += 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot += 1 / M_PI * (mo->pos().x() - mPos.x());
  mPos = mo->pos();
  update();
}

void GLWidget::change_projection() {
  if (projection_type == 0) {
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }
}

void GLWidget::set_Point() {
  if (pointType == POINT_ROUND) {
    glEnable(GL_POINT_SMOOTH);
  } else if (pointType == POINT_QUADRO) {
    glDisable(GL_POINT_SMOOTH);
  }
  if (pointType != EMPTY) {
    glPointSize(pointWidth);
    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());
    glDrawArrays(GL_POINTS, 0, data.count_of_vertexes);
  }
}

void GLWidget::set_Line() {
  if (lineType == EMPTY) {
    glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
    glLineWidth(lineWidth);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
    glLineWidth(lineWidth);
  } else if (lineType == LINE_DASHED) {
    glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
    glLineWidth(lineWidth);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
    glLineWidth(lineWidth);
  } else {
    glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
    glDisable(GL_LINE_STIPPLE);
  }
}
