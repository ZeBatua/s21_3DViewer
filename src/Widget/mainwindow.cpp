#include "mainwindow.h"

#include "ui_mainwindow.h"

int file_status_main = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D_Viewer");
  timer = new QTimer(0);

  connect(ui->newFile, SIGNAL(clicked()), this, SLOT(openFile()));
  connect(ui->scale_mul, SIGNAL(valueChanged(double)), this, SLOT(zoomIn()));
  connect(ui->scale_del, SIGNAL(valueChanged(double)), this, SLOT(zoomOut()));
  connect(ui->moveX_sum, SIGNAL(valueChanged(double)), this, SLOT(moveX()));
  connect(ui->moveY_sum, SIGNAL(valueChanged(double)), this, SLOT(moveY()));
  connect(ui->moveZ_sum, SIGNAL(valueChanged(double)), this, SLOT(moveZ()));
  connect(ui->moveX_sub, SIGNAL(valueChanged(double)), this, SLOT(moveX_sub()));
  connect(ui->moveY_sub, SIGNAL(valueChanged(double)), this, SLOT(moveY_sub()));
  connect(ui->moveZ_sub, SIGNAL(valueChanged(double)), this, SLOT(moveZ_sub()));

  connect(ui->empty_line, SIGNAL(clicked()), this, SLOT(setEmptyLine()));
  connect(ui->dash_line, SIGNAL(clicked()), this, SLOT(setDashLine()));
  connect(ui->solid_line, SIGNAL(clicked()), this, SLOT(setSolidLine()));
  connect(ui->thick_line, SIGNAL(valueChanged(int)), this,
          SLOT(setThickLine()));

  connect(ui->orb_point, SIGNAL(clicked()), this, SLOT(setOrbPoint()));
  connect(ui->empty_point, SIGNAL(clicked()), this, SLOT(setEmptyPoint()));
  connect(ui->square_point, SIGNAL(clicked()), this, SLOT(setSquarePoint()));
  connect(ui->thick_point, SIGNAL(valueChanged(int)), this,
          SLOT(setThickPoint()));

  connect(ui->ChangeLineColor, SIGNAL(clicked()), this, SLOT(setLineColor()));
  connect(ui->ChangePointColor, SIGNAL(clicked()), this, SLOT(setPointcolor()));
  connect(ui->ChangeBackgroundColor, SIGNAL(clicked()), this,
          SLOT(setBackColor()));

  connect(ui->central, SIGNAL(clicked()), this, SLOT(setProjection()));
  connect(ui->parallel, SIGNAL(clicked()), this, SLOT(setProjection()));

  connect(ui->make_screen, SIGNAL(textActivated(QString)), this,
          SLOT(createScreen()));
  connect(ui->gif, SIGNAL(clicked()), this, SLOT(createGIF()));
  connect(timer, SIGNAL(timeout()), this, SLOT(timerRun()));

  connect(ui->save_setting, SIGNAL(clicked()), this, SLOT(saveSetting()));
  connect(ui->load_setting, SIGNAL(clicked()), this, SLOT(loadSetting()));
}

MainWindow::~MainWindow() {
  delete timer;
  delete ui;
}

void MainWindow::openFile() {
  if (file_status_main == 1) freeMem(&ui->widget->data);
  initFileData(&ui->widget->data);
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr("(*.obj)"));
  if (file != "") {
    int error = 0;
    QByteArray q_path = file.toLocal8Bit();
    char *result_path = q_path.data();
    error = readFile(result_path, &ui->widget->data);
    if (!error) {
      file_status_main = 1;
      ui->widget->openFile();
      set_info(file);
    } else {
      ui->file_name->setText("File not valid");
    }
  }
}

void MainWindow::set_info(QString path) {
  QString count_of_vertexes =
      QString::number(ui->widget->data.count_of_vertexes);
  QString count_of_facets = QString::number(ui->widget->data.count_of_facets);
  int index = path.lastIndexOf("/");
  int size = path.length();
  file_name = path.right(size - index - 1);
  ui->vertexes->setText(count_of_vertexes);
  ui->polygons->setText(count_of_facets);
  ui->file_name->setText(file_name);
}

void MainWindow::zoomIn() {
  float scale = ui->scale_mul->value();
  if (scale_increase != 0 && scale < scale_increase) {
    float difference = scale_increase - scale;
    ui->widget->delScaleChange(difference + scale_increase);
  } else {
    ui->widget->mulScaleChange(scale);
  }
  scale_increase = scale;
}

void MainWindow::zoomOut() {
  float scale = ui->scale_del->value();
  if (scale_reduction != 0 && scale < scale_reduction) {
    float difference = scale_reduction - scale;
    ui->widget->mulScaleChange(difference + scale_reduction);
  } else {
    ui->widget->delScaleChange(scale);
  }
  scale_reduction = scale;
}

void MainWindow::moveX() {
  float sumX = ui->moveX_sum->value();
  if (move_x_sum != 0 && sumX < move_x_sum) {
    ui->widget->addMoveChangeX(move_x_sum * (-1));
  } else {
    ui->widget->addMoveChangeX(sumX);
  }
  move_x_sum = sumX;
}

void MainWindow::moveY() {
  float sumY = ui->moveY_sum->value();
  if (move_y_sum != 0 && sumY < move_y_sum) {
    ui->widget->addMoveChangeY(move_y_sum * (-1));
  } else {
    ui->widget->addMoveChangeY(sumY);
  }
  move_y_sum = sumY;
}

void MainWindow::moveZ() {
  float sumZ = ui->moveZ_sum->value();
  if (move_z_sum != 0 && sumZ < move_z_sum) {
    ui->widget->addMoveChangeZ(move_z_sum * (-1));
  } else {
    ui->widget->addMoveChangeZ(sumZ);
  }
  move_z_sum = sumZ;
}

void MainWindow::moveX_sub() {
  float subX = ui->moveX_sub->value();
  if (move_x_sub != 0 && subX < move_x_sub) {
    ui->widget->addMoveChangeX(move_x_sub);
  } else {
    ui->widget->addMoveChangeX(subX * (-1));
  }
  move_x_sub = subX;
}

void MainWindow::moveY_sub() {
  float subY = ui->moveY_sub->value();
  if (move_y_sub != 0 && subY < move_y_sub) {
    ui->widget->addMoveChangeY(move_y_sub);
  } else {
    ui->widget->addMoveChangeY(subY * (-1));
  }
  move_y_sub = subY;
}

void MainWindow::moveZ_sub() {
  float subZ = ui->moveZ_sub->value();
  if (move_z_sub != 0 && subZ < move_z_sub) {
    ui->widget->addMoveChangeZ(move_z_sub * (-1));
  } else {
    ui->widget->addMoveChangeZ(subZ);
  }
  move_z_sub = subZ;
}

void MainWindow::setDashLine() {
  ui->widget->lineType = ui->widget->LINE_DASHED;
  ui->widget->update();
}

void MainWindow::setSolidLine() {
  ui->widget->lineType = ui->widget->LINE_SOLID;
  ui->widget->update();
}

void MainWindow::setEmptyLine() {
  ui->widget->lineType = ui->widget->EMPTY;
  ui->widget->update();
}

void MainWindow::setThickLine() {
  ui->widget->lineWidth = ui->thick_line->value();
  ui->widget->update();
}

void MainWindow::setOrbPoint() {
  ui->widget->pointType = ui->widget->POINT_ROUND;
  ui->widget->update();
}
void MainWindow::setEmptyPoint() {
  ui->widget->pointType = ui->widget->EMPTY;
  ui->widget->update();
}

void MainWindow::setSquarePoint() {
  ui->widget->pointType = ui->widget->POINT_QUADRO;
  ui->widget->update();
}

void MainWindow::setThickPoint() {
  ui->widget->pointWidth = ui->thick_point->value();
  ui->widget->update();
}

void MainWindow::setLineColor() {
  ui->widget->colorLine = QColorDialog::getColor(Qt::gray);
  ui->widget->update();
}
void MainWindow::setPointcolor() {
  ui->widget->colorPoint = QColorDialog::getColor(Qt::gray);
  ui->widget->update();
}
void MainWindow::setBackColor() {
  ui->widget->colorBack = QColorDialog::getColor(Qt::gray);
  ui->widget->update();
}

void MainWindow::createScreen() {
  QString current_type = ui->make_screen->currentText();

  QString screen =
      QFileDialog::getSaveFileName(this, "Save screen as:", "", current_type);
  if (screen != nullptr) {
    QFile file(screen);
    file.open(QIODevice::WriteOnly);
    QRect rect(0, 0, ui->widget->width() * 2, ui->widget->height() * 2);
    QPixmap map = ui->widget->grab(rect);
    map.copy(rect).toImage().save(&file, current_type.toStdString().c_str());
  }
}

void MainWindow::createGIF() {
  timer->start(100);
  timerRun();
  count = 0.0;
}

void MainWindow::timerRun() {
  if (count <= 5.0) {
    gif.push_back(ui->widget->grab().toImage());
    count += 0.1;
  } else {
    makeGIF();
    timer->stop();
  }
}

void MainWindow::makeGIF() {
  QString gif_name =
      QFileDialog::getSaveFileName(this, "Save gif", "", "*.gif");
  QGifImage gif_image(QSize(640, 480));
  gif_image.setDefaultDelay(100);

  for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
       ++screen) {
    gif_image.addFrame(*screen);
  }
  gif_image.save(gif_name);
  gif.clear();
  count = 0.0;
}

void MainWindow::setProjection() {
  if (ui->central->isChecked()) {
    ui->widget->projection_type = 1;
  } else if (ui->parallel->isChecked()) {
    ui->widget->projection_type = 0;
  }
  ui->widget->update();
}

void MainWindow::saveSetting() {
  QSettings settings(QApplication::applicationDirPath() + "/user_settings",
                     QSettings::NativeFormat);
  settings.setValue("lineType", ui->widget->lineType);
  settings.setValue("lineWidth", ui->widget->lineWidth);

  settings.setValue("pointType", ui->widget->pointType);
  settings.setValue("pointWidth", ui->widget->pointWidth);

  settings.setValue("colorPoint", ui->widget->colorPoint);
  settings.setValue("colorBack", ui->widget->colorBack);
  settings.setValue("colorLine", ui->widget->colorLine);

  settings.setValue("projection_type", ui->widget->projection_type);
}

void MainWindow::loadSetting() {
  QSettings settings(QApplication::applicationDirPath() + "/user_settings",
                     QSettings::NativeFormat);

  ui->widget->lineType = settings.value("lineType").toInt();
  if (ui->widget->lineType == ui->widget->EMPTY)
    ui->empty_line->setChecked(true);
  else if (ui->widget->lineType == ui->widget->LINE_SOLID)
    ui->solid_line->setChecked(true);
  else
    ui->dash_line->setChecked(true);

  ui->widget->lineWidth = settings.value("lineWidth").toFloat();
  ui->thick_line->setValue(ui->widget->lineWidth);

  ui->widget->pointType = settings.value("pointType").toInt();
  if (ui->widget->pointType == ui->widget->EMPTY)
    ui->empty_point->setChecked(true);
  else if (ui->widget->pointType == ui->widget->POINT_ROUND)
    ui->orb_point->setChecked(true);
  else
    ui->square_point->setChecked(true);

  ui->widget->pointWidth = settings.value("pointWidth").toFloat();
  ui->thick_point->setValue(ui->widget->pointWidth);

  ui->widget->colorBack = settings.value("colorBack").value<QColor>();
  ui->widget->colorLine = settings.value("colorLine").value<QColor>();
  ui->widget->colorPoint = settings.value("colorPoint").value<QColor>();

  ui->widget->projection_type = settings.value("projection_type").toInt();
  if (ui->widget->projection_type == 1)
    ui->central->setChecked(true);
  else
    ui->parallel->setChecked(true);

  ui->widget->update();
}
