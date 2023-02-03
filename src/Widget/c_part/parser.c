#include "parser.h"

int readFile(const char *filename, file_data *data) {
  int errorValue = getVertexesFacets(filename, data);
  if (!errorValue) createMatrixData(filename, data);
  return errorValue;
}

int getVertexesFacets(const char *file_obj, file_data *data) {
  int errorStatus = 0;
  FILE *file = NULL;
  file = fopen(file_obj, "r");
  if (file != NULL) {
    initFileData(data);
    char *str_pos = NULL;
    size_t len = 0;
    while (getline(&str_pos, &len, file) != -1) {
      if (*str_pos == 'v' && *(str_pos + 1) == ' ') {
        data->count_of_vertexes++;
      }
      if (*str_pos == 'f' && *(str_pos + 1) == ' ') {
        data->count_of_facets++;
      }
    }
    fclose(file);
  } else {
    errorStatus = 1;
  }
  return errorStatus;
}

void createMatrixData(const char *filename, file_data *data) {
  unsigned int vertex_counter = 1, facets_counter = 0;
  FILE *file = fopen(filename, "r");
  char *str_pos = NULL;
  s21_create_matrix(data->count_of_vertexes + 1, 3, &data->matrix_3d);
  data->polygons = calloc(data->count_of_facets, sizeof(polygon_t));
  size_t len = 0;
  while (getline(&str_pos, &len, file) != -1) {
    if (*str_pos == 'v' && *(str_pos + 1) == ' ') {
      fillVertexMatrix(str_pos + 1, data, &vertex_counter);
      vertex_counter++;
    } else if (*str_pos == 'f' && *(str_pos + 1) == ' ') {
      getVertexesInFacet(str_pos + 1, data, &facets_counter);
      data->polygons[facets_counter].vertexes =
          calloc(data->polygons[facets_counter].numbers_of_vertexes_in_facets,
                 sizeof(unsigned int));
      fillFacetMatrix(str_pos + 1, data, &facets_counter);
      facets_counter++;
    }
  }
  fclose(file);
}

void fillVertexMatrix(char *str_pos, file_data *data,
                      unsigned int *vertex_counter) {
  char *token;
  int i = 0;
  while ((token = strtok_r(str_pos, " ", &str_pos))) {
    data->matrix_3d.matrix[*vertex_counter][i] = atof(token);
    if (data->matrix_3d.max_value <
        fabs(data->matrix_3d.matrix[*vertex_counter][i])) {
      data->matrix_3d.max_value =
          fabs(data->matrix_3d.matrix[*vertex_counter][i]);
    }
    i++;
  }
}

void getVertexesInFacet(char *str_pos, file_data *data,
                        unsigned int *facets_counter) {
  char *temp = strdup(str_pos);
  char *for_free = temp;
  char *token;

  while ((token = strtok_r(temp, " ", &temp))) {
    if (*token != '0' && *token != '\n' && *token != '\r') {
      data->polygons[*facets_counter].numbers_of_vertexes_in_facets++;
      data->full_amount_of_vertexes_in_facets++;
    }
  }
  free(for_free);
}
void fillFacetMatrix(char *str_pos, file_data *data,
                     unsigned int *facets_counter) {
  int i = 0;
  char *token;

  while ((token = strtok_r(str_pos, " ", &str_pos))) {
    if (*token == '\n' || *token == ' ' || *token == '\r') break;
    if (*token != '0') {
      data->polygons[*facets_counter].vertexes[i] = atoi(token) - 1;
      i++;
    }
  }
}

void initFileData(file_data *data) {
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->full_amount_of_vertexes_in_facets = 0;
  data->matrix_3d.matrix = NULL;
  data->matrix_3d.columns = 0;
  data->matrix_3d.rows = 0;
  data->matrix_3d.max_value = 0;
  data->polygons = NULL;
}

void freeMem(file_data *data) {
  if (data != NULL) {
    s21_remove_matrix(&data->matrix_3d);
    if (data->polygons != NULL) {
      for (unsigned int i = 0; i < data->count_of_facets; i++) {
        free(data->polygons[i].vertexes);
      }
      free(data->polygons);
    }
  }
}

float *rewrite_matrix(file_data *data) {
  // if (data != NULL) {
  float *new_matrix = calloc(data->count_of_vertexes * 3, sizeof(float));
  unsigned int k = 0;
  if (data->matrix_3d.matrix != NULL) {
    if (data->count_of_facets != 0) {
      for (int i = 1; i < data->matrix_3d.rows; i++) {
        for (int j = 0; j < data->matrix_3d.columns; j++) {
          new_matrix[k] =
              data->matrix_3d.matrix[i][j] / data->matrix_3d.max_value;
          k++;
        }
      }
    }
  }
  return new_matrix;
  // }
}

unsigned int *write_facets(file_data *data) {
  unsigned int *new_matrix =
      calloc(data->full_amount_of_vertexes_in_facets * 2, sizeof(unsigned int));
  if (data->count_of_facets != 0) {
    unsigned int p_counter = 0, v_index = 0, mass_counter = 0;
    while (p_counter < data->count_of_facets) {
      while (data->polygons[p_counter].vertexes != NULL) {
        new_matrix[mass_counter] = data->polygons[p_counter].vertexes[v_index];
        mass_counter++;
        if (v_index + 1 <
            data->polygons[p_counter].numbers_of_vertexes_in_facets) {
          new_matrix[mass_counter] =
              data->polygons[p_counter].vertexes[v_index + 1];
          mass_counter++;
        } else {
          new_matrix[mass_counter] = data->polygons[p_counter].vertexes[0];
          mass_counter++;
          break;
        }
        v_index++;
      }
      v_index = 0;
      p_counter++;
    }
  }
  return new_matrix;
}
