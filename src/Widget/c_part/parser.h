#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include "matrix.h"

typedef struct facets {
  unsigned int *vertexes;
  unsigned int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct s_data {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  unsigned int full_amount_of_vertexes_in_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} file_data;

int readFile(const char *filename, file_data *data);
void initFileData(file_data *data);
int getVertexesFacets(const char *file_obj, file_data *data);
void createMatrixData(const char *filename, file_data *data);
void fillVertexMatrix(char *string_pos, file_data *data,
                      unsigned int *vertex_counter);
void getVertexesInFacet(char *string_pos, file_data *data,
                        unsigned int *facets_counter);
void fillFacetMatrix(char *string_pos, file_data *data,
                     unsigned int *facets_counter);
void freeMem(file_data *data);
float *rewrite_matrix(file_data *data);
unsigned int *write_facets(file_data *data);

#endif  // SRC_PARSER_PARSER_H
