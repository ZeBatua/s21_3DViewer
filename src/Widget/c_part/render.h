#ifndef SRC_RENDER_H_
#define SRC_RENDER_H_

#include "parser.h"

void moveX(file_data* data, double value);
void moveY(file_data* data, double value);
void moveZ(file_data* data, double value);
void rotationOX(file_data* data, double angle);
void rotationOY(file_data* data, double angle);
void rotationOZ(file_data* data, double angle);
void zoomIn(file_data* data, double value);
void zoomOut(file_data* data, double value);

#endif  // SRC_RENDER_H_
