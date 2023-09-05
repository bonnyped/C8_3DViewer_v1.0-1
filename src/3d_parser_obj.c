#include <assert.h>
#include <float.h>
#include <string.h>

#include "three_d_viewer.h"
#if defined(__linux__)
#define strtok_r(a, b, c) __strtok_r(a, b, c)
#endif

// 1.0
int parse_the_model_file_obj_head(model_v *model, const char *obj_file_name) {
  setlocale(LC_NUMERIC, "C");
  int status = ALL_RIGHT;
  if (obj_file_name == NULL) {
    status = ERROR;
  }
  if (status == ALL_RIGHT) {
    FILE *file_obj = fopen(obj_file_name, "r");
    if (file_obj) {
      status = parse_the_model_file_obj(model, file_obj);
      if (model->buffer) {
        free(model->buffer);
        model->buffer = NULL;
      }
      fclose(file_obj);
      optimize_vector_value_head(model, status);
    } else {
      status = THE_FILE_CANNOT_BE_OPENED;
      fprintf(stderr, "Hamlet3DViewer: Error file NOT\n");
    }
  }
  return status;
}

// 1.1
int parse_the_model_file_obj(model_v *model, FILE *file_obj) {
  int status = ALL_RIGHT;
  long int size_file = determine_the_file_size_in_bytes(file_obj);
  model->buffer = (char *)calloc((size_file + 1), sizeof(char));
  size_t result = fread(model->buffer, 1, size_file, file_obj);
  if (result != (size_t)size_file) {
    status = ERROR_READ_FILE;
  }
  status = (status == ALL_RIGHT)
               ? counting_vertices_and_polygons_head(model, model->buffer)
               : status;
  if (status == ALL_RIGHT) {
    status = allocate_memory_for_vertices_and_polygons(model);
    status = (status == ALL_RIGHT)
                 ? write_vertices_and_polygons_head(model, model->buffer)
                 : status;
  }
  return status;
}

// 2
long int determine_the_file_size_in_bytes(FILE *file_obj) {
  fseek(file_obj, 0L, SEEK_END);
  long int size_file = ftell(file_obj);
  rewind(file_obj);
  return size_file;
}

// 3.0
int counting_vertices_and_polygons_head(model_v *model, char *buffer) {
  int status = ALL_RIGHT;
  char *saveptr_line = NULL;
  char *original = my_strdup(buffer);
  saveptr_line = original;
  char *line = NULL;
  status =
      original == NULL ? ERROR_ALLOCATION : status;  // return ERROR_ALLOCATION;
  model->number_struct.number_of_indexes = 0;
  model->number_struct.number_of_vertices = 0;
  while ((line = strtok_r(saveptr_line, "\n", &saveptr_line)) && !status) {
    if ((strncmp(line, "v ", 2) == 0)) {
      model->number_struct.number_of_vertices++;
    } else if (strncmp(line, "f ", 2) == 0) {
      counting_poligons_in_one_str(model, line);
    }
  }

  if (original) {
    free(original);
  }

  if (!model->number_struct.number_of_vertices ||
      !model->number_struct.number_of_indexes) {
    status = ZERO_VALUE_WHEN_COUNTING;
    fprintf(stderr, "Hamlet3DViewer:  value: v = %u | f = %u\n",
            model->number_struct.number_of_vertices,
            model->number_struct.number_of_indexes);
  }
  return status;
}

// 3.1
int counting_poligons_in_one_str(model_v *model, char *line) {
  int status = ALL_RIGHT;
  char *saveptr = NULL;
  char *token = NULL;
  for (token = strtok_r(line, " ", &saveptr); token && line;
       token = strtok_r(NULL, " ", &saveptr)) {
    if (atoi(token)) {
      model->number_struct.number_of_indexes++;
    }
  }
  return status;
}

// 4
int allocate_memory_for_vertices_and_polygons(model_v *model) {
  int status_allocate_memory = ALL_RIGHT;
  if (!model->vertex_obj) {
    model->vertex_obj = (double *)malloc(
        ((model->number_struct.number_of_vertices * 3)) * sizeof(double));
    status_allocate_memory =
        (model->vertex_obj == NULL) ? ERROR_ALLOCATION : ALL_RIGHT;
  } else {
    free(model->vertex_obj);
    model->vertex_obj = (double *)malloc(
        ((model->number_struct.number_of_vertices * 3)) * sizeof(double));
    status_allocate_memory =
        (model->vertex_obj == NULL) ? ERROR_ALLOCATION : ALL_RIGHT;
  }

  if (!model->polygons_obj && status_allocate_memory == ALL_RIGHT) {
    model->polygons_obj = (int *)malloc(
        (model->number_struct.number_of_indexes * 2) * sizeof(int));
    status_allocate_memory =
        (model->polygons_obj == NULL) ? ERROR_ALLOCATION : ALL_RIGHT;
  } else if (model->polygons_obj && status_allocate_memory == ALL_RIGHT) {
    free(model->polygons_obj);
    model->polygons_obj = (int *)malloc(
        (model->number_struct.number_of_indexes * 2) * sizeof(int));
    status_allocate_memory =
        (model->polygons_obj == NULL) ? ERROR_ALLOCATION : ALL_RIGHT;
  }
  return status_allocate_memory;
}

// 5.0
int write_vertices_and_polygons_head(model_v *model, char *buffer) {
  int status = ALL_RIGHT;
  char *original = NULL;
  original = my_strdup(buffer);
  char *saveptr_line = original;
  char *line_token = NULL;
  status = !original ? ERROR : status;
  while ((line_token = strtok_r(saveptr_line, "\n", &saveptr_line)) &&
         !status) {
    if ((strncmp(line_token, "v ", 2) == 0)) {
      status = write_vertices(model, line_token);
    } else if (strncmp(line_token, "f ", 2) == 0) {
      status = write_polygons(model, line_token + 2);
    }
  }
  if (original) {
    free(original);
  }
  return status;
}

// 5.1.0
int write_vertices(model_v *model, char *line) {
  int status = ALL_RIGHT;
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  sscanf(line, "v %lf %lf %lf", &x, &y, &z);
  min_max_x_y_z(model, x, y, z);
  model->vertex_obj[model->count_v] = x;
  model->vertex_obj[model->count_v + 1] = y;
  model->vertex_obj[model->count_v + 2] = z;
  model->count_v += 3;

  return status;
}

// 5.1.1
void min_max_x_y_z(model_v *model, double x, double y, double z) {
  if (x > model->extreme_values.max_x) {
    model->extreme_values.max_x = x;
  }
  if (y > model->extreme_values.max_y) {
    model->extreme_values.max_y = y;
  }
  if (z > model->extreme_values.max_z) {
    model->extreme_values.max_z = z;
  }
  if (model->extreme_values.min_x > x) {
    model->extreme_values.min_x = x;
  }
  if (model->extreme_values.min_y > y) {
    model->extreme_values.min_y = y;
  }
  if (model->extreme_values.min_z > z) {
    model->extreme_values.min_z = z;
  }
}

// 5.2
int write_polygons(model_v *model, char *line) {
  int status = ALL_RIGHT;
  char *saveptr = NULL;
  char *token = NULL;
  int last = -1000000;
  int first = 0;
  for (token = strtok_r(line, " ", &saveptr); token;
       token = strtok_r(NULL, " ", &saveptr)) {
    int tok = atoi(token);
    if (tok) {
      if (tok < 0) {
        tok += model->count_v / 3 + 1;
      }
      model->polygons_obj[model->count_p++] = tok - 1;
      if (last > -1) {
        model->polygons_obj[model->count_p++] = tok - 1;
      } else if (last == -1000000) {
        first = tok - 1;
        last = tok - 1;
      }
      if (tok > (int)model->number_struct.number_of_vertices || tok < 0) {
        status = ERROR_INDEX_F;
        fprintf(stderr,
                "Hamlet3DViewer:  v = %u | f = %d token = %s line = %s\n",
                model->number_struct.number_of_vertices, tok, token, line);
      }
    }
  }

  model->polygons_obj[model->count_p++] = first;
  return status;
}

// 0.0 зануление и запись значений в структуру вызывается после определения
// структуры в main(Qt c++)
void zero_out_the_structure(model_v *model) {
  assert(model);
  model->buffer = NULL;
  model->count_p = 0;
  model->count_v = 0;
  model->vertex_obj = NULL;
  model->vertex_obj = NULL;
  model->extreme_values.max_x = -10000;
  model->extreme_values.max_y = -10000;
  model->extreme_values.max_z = -10000;
  model->extreme_values.min_x = DBL_MAX;
  model->extreme_values.min_y = DBL_MAX;
  model->extreme_values.min_z = DBL_MAX;
  model->extreme_values.max_all = DBL_MIN;
  model->number_struct.number_of_indexes = 0;
  model->number_struct.number_of_vertices = 0;
}

// достаем x y z по индексу
int index_vertex(double *x, double *y, double *z, int index, model_v *model) {
  int status = ALL_RIGHT;
  int i = index * 3 - 3;
  if (i >= 0 && i < model->count_v) {
    *x = model->vertex_obj[i];
    *y = model->vertex_obj[i + 1];
    *z = model->vertex_obj[i + 2];
  } else {
    status = ERROR;
  }
  return status;
}

// очищаем выделенную память под индексы вершины и файл
void free_model(model_v *model) {
  if (model) {
    if (model->polygons_obj) {
      free(model->polygons_obj);
      model->polygons_obj = NULL;
    }
    if (model->vertex_obj) {
      free(model->vertex_obj);
      model->vertex_obj = NULL;
    }
    if (model->buffer) {
      free(model->buffer);
      model->buffer = NULL;
    }
  }
}

// вмещаем модель в экран openGl от -1 до 1
void optimize_for_the_size_of_the_opengl_window(model_v *model) {
  double coof_scale = 0.5;
  double cooef_x =
      (model->extreme_values.max_x - model->extreme_values.min_x) / 2 +
      model->extreme_values.min_x;
  double cooef_y =
      (model->extreme_values.max_y - model->extreme_values.min_y) / 2 +
      model->extreme_values.min_y;
  double cooef_z =
      (model->extreme_values.max_z - model->extreme_values.min_z) / 2 +
      model->extreme_values.min_z;
  double x_x = model->extreme_values.max_x - model->extreme_values.min_x;
  double y_y = model->extreme_values.max_y - model->extreme_values.min_y;
  double z_z = model->extreme_values.max_z - model->extreme_values.min_z;
  double max_point_m = max_value(x_x, y_y, z_z);
  double scale_model = (coof_scale - (coof_scale * -1)) / max_point_m;
  for (size_t i = 0; i < model->number_struct.number_of_vertices * 3; i += 3) {
    model->vertex_obj[i] -= cooef_x;
    model->vertex_obj[i + 1] -= cooef_y;
    model->vertex_obj[i + 2] -= cooef_z;
    model->vertex_obj[i] *= scale_model;
    model->vertex_obj[i + 1] *= scale_model;
    model->vertex_obj[i + 2] *= scale_model;
  }
}

double max_value(double x_x, double y_y, double z_z) {
  double result = x_x;
  if (y_y > x_x && y_y > z_z) {
    result = y_y;
  } else if (z_z > x_x && z_z > y_y) {
    result = z_z;
  }
  return result;
}

// находим максимальное число для проэкции
void optimize_vector_value_head(model_v *model, int status) {
  if (status == ALL_RIGHT) {
    optimize_for_the_size_of_the_opengl_window(model);
    for (size_t i = 0; i < model->number_struct.number_of_vertices * 3; i++) {
      if (fabs(model->vertex_obj[i]) > fabs(model->extreme_values.max_all)) {
        model->extreme_values.max_all = fabs(model->vertex_obj[i]);
      }
    }
  }
}

char *my_strdup(char *string) {
  int status = ALL_RIGHT;
  char *new_string = NULL;
  size_t size_original_str = 0;
  if (string != NULL) {
    size_original_str = strlen(string);
  } else {
    status = ERROR;
  }
  if (status == ALL_RIGHT) {
    new_string = (char *)calloc(size_original_str + 1, sizeof(char));
  }
  if (new_string != NULL) {
    strncpy(new_string, string, size_original_str + 1);
  }
  return new_string;
}
