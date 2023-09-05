#include "three_d_viewer.h"

void x_axis_rotation(model_v *model, double angle_of_inclination) {
  double angle = angle_of_inclination * V_PI / 180.0;  // translate
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  for (size_t i = 1; i <= model->number_struct.number_of_vertices; ++i) {
    index_vertex(&x, &y, &z, i, model);
    model->vertex_obj[i * 3 - 2] = y * cos(angle) + z * sin(angle);
    model->vertex_obj[i * 3 - 1] = -y * sin(angle) + z * cos(angle);
  }
}

void y_axis_rotation(model_v *model, double angle_of_inclination) {
  double angle = angle_of_inclination * V_PI / 180.0;  // translate
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  for (size_t i = 1; i <= model->number_struct.number_of_vertices; ++i) {
    index_vertex(&x, &y, &z, i, model);
    model->vertex_obj[i * 3 - 3] = x * cos(angle) + z * sin(angle);
    model->vertex_obj[i * 3 - 1] = -x * sin(angle) + z * cos(angle);
  }
}

void z_axis_rotation(model_v *model, double angle_of_inclination) {
  double angle = angle_of_inclination * V_PI / 180.0;  // translate
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  for (size_t i = 1; i <= model->number_struct.number_of_vertices; ++i) {
    index_vertex(&x, &y, &z, i, model);
    model->vertex_obj[i * 3 - 3] = x * cos(angle) + y * sin(angle);
    model->vertex_obj[i * 3 - 2] = -x * sin(angle) + y * cos(angle);
  }
}

void model_scale(model_v *model, double coefficient) {
  if (coefficient != 0.0) {
    for (unsigned i = 0; i < model->number_struct.number_of_vertices * 3; ++i) {
      model->vertex_obj[i] *= coefficient;
    }
  }
}

void move_the_model_along_the_x_axis(model_v *model, double coefficient) {
  for (unsigned i = 0; i < model->number_struct.number_of_vertices * 3;
       i += 3) {
    model->vertex_obj[i] += coefficient;
  }
}

void move_the_model_along_the_y_axis(model_v *model, double coefficient) {
  for (unsigned i = 1; i < model->number_struct.number_of_vertices * 3;
       i += 3) {
    model->vertex_obj[i] += coefficient;
  }
}

void move_the_model_along_the_z_axis(model_v *model, double coefficient) {
  for (unsigned i = 2; i < model->number_struct.number_of_vertices * 3;
       i += 3) {
    model->vertex_obj[i] += coefficient;
  }
}
