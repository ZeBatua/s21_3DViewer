#include "render.h"

void moveX(file_data* data, double value) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] += value;
  }
}

void moveY(file_data* data, double value) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][1] += value;
  }
}

void moveZ(file_data* data, double value) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][2] += value;
  }
}

void rotationOX(file_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double tmp_y = data->matrix_3d.matrix[i][1];
    double tmp_z = data->matrix_3d.matrix[i][2];
    data->matrix_3d.matrix[i][1] = cos(angle) * tmp_y + sin(angle) * tmp_z;
    data->matrix_3d.matrix[i][2] = -sin(angle) * tmp_y + cos(angle) * tmp_z;
  }
}

void rotationOY(file_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double tmp_x = data->matrix_3d.matrix[i][0];
    double tmp_z = data->matrix_3d.matrix[i][2];
    data->matrix_3d.matrix[i][0] = cos(angle) * tmp_x + sin(angle) * tmp_z;
    data->matrix_3d.matrix[i][2] = -sin(angle) * tmp_x + cos(angle) * tmp_z;
  }
}

void rotationOZ(file_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double tmp_x = data->matrix_3d.matrix[i][0];
    double tmp_y = data->matrix_3d.matrix[i][1];
    data->matrix_3d.matrix[i][0] = cos(angle) * tmp_x - sin(angle) * tmp_y;
    data->matrix_3d.matrix[i][1] = sin(angle) * tmp_x + cos(angle) * tmp_y;
  }
}

void zoomIn(file_data* data, double value) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] *= value;
    data->matrix_3d.matrix[i][1] *= value;
    data->matrix_3d.matrix[i][2] *= value;
  }
}

void zoomOut(file_data* data, double value) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] /= value;
    data->matrix_3d.matrix[i][1] /= value;
    data->matrix_3d.matrix[i][2] /= value;
  }
}
