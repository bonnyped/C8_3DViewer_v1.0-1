#ifndef THREE_D_VIEWER_H
#define THREE_D_VIEWER_H

#define V_PI 3.14159265358979323846
#define EPSILON 0.000000001

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief Statuses of the executed program
enum status {
  ALL_RIGHT,
  ERROR,
  THE_FILE_CANNOT_BE_OPENED,
  ZERO_VALUE_WHEN_COUNTING,
  ERROR_INDEX_F,
  ERROR_READ_FILE,
  ERROR_ALLOCATION,
};

/// @brief Structure for storing the number of vertices and edges of a 3d model
///\struct
struct size_vert {
  unsigned int number_of_vertices;
  unsigned int number_of_indexes;
};

/// @brief The structure for storing the minimum and maximum values of vertex
/// coordinates.(x,y,z)
struct min_max_xyz {
  double min_x;
  double min_y;
  double min_z;
  double max_x;
  double max_y;
  double max_z;
  double max_all;
};

/// @brief Information about the 3d model is stored here.(association)
typedef struct data {
  char *buffer;
  long int count_v;
  long int count_p;
  double *vertex_obj;
  int *polygons_obj;
  struct size_vert number_struct;
  struct min_max_xyz extreme_values;
} model_v;

/// @brief The function of reading and parsing the file.  Parent  function .
/// @param model  To write values from a file.obj for further rendering.
/// @param obj_file_name Type: char* a pointer to a string containing the path
/// to the file and the file name.
/// @return File parsing status type: int
int parse_the_model_file_obj_head(model_v *model, const char *obj_file_name);

/// @brief In this function, information from the file is written to a string
/// (MEMORY is ALLOCATED!!), the functions of parsing this string (buffer) are
/// called, counting vertices and indexes and allocating memory for their
/// storage.
/// @param model To write values from a file.obj for further rendering.
/// @param file_obj this is a reference to the memory in which the absolute path
/// to the file and the file name are stored.
/// @return The execution status is returned: success or error code.  Type: int
int parse_the_model_file_obj(model_v *model, FILE *file_obj);

/// @brief The function distributes the processing of rows with vertices and the
/// processing of rows with indexes into two independent functions.
/// @param model  To write values from a file.obj for further rendering.
/// @param buffer This is a pointer to the allocated memory for the .obj file |
/// type: char*
/// @return The execution status is returned: success or error code.  Type: int
int write_vertices_and_polygons_head(model_v *model, char *buffer);

/// @brief Index counting function (for further allocation of memory for an
/// array of int)
/// @param model To write values from a file.obj for further rendering.
/// @param line This is a pointer to the allocated memory for a row with
/// indexes. ("f 1 2 3")
/// @return The execution status is returned: success or error code.  Type: int
int counting_poligons_in_one_str(model_v *model, char *line);

/// @brief This is a function in which memory is allocated for an array of
/// vertices(double) and an array of indexes(int).
/// @param model  To write values from a file.obj for further rendering.
/// @return The execution status is returned: success or error code.  Type: int
int allocate_memory_for_vertices_and_polygons(model_v *model);

/// @brief This is a function that writes the coordinates x,y,z, from a string
/// to an array of vertices (double).
/// @param model To write values from a file.obj for further rendering.
/// @param line This is a string with the coordinates of the vertex
/// @return The execution status is returned: success or error code.  Type: int
int write_vertices(model_v *model, char *line);

/// @brief This is a function that writes indexes from a string to an array of
/// indexes (int).
/// @param model To write values from a file.obj for further rendering.
/// @param line This is a string with indexes. (f 1 2 3 ...) | f(1/3/4 2/3/5
/// 4/5/6 ...) | ...
/// @return The execution status is returned: success or error code.  Type: int
int write_polygons(model_v *model, char *line);

/// @brief This procedure nulls the elements of the structure and fills in the
/// necessary values for the correct operation of the program
/// @param model  To write values from a file.obj for further rendering.
void zero_out_the_structure(model_v *model);

/// @brief This procedure checks and records the minimum and maximum values of
/// the x,y and z coordinates.
/// @param model To write values from a file.obj for further rendering.
/// @param x This is the coordinate of the vertex on the x axis
/// @param y This is the coordinate of the vertex on the y axis
/// @param z This is the coordinate of the vertex on the z axis
void min_max_x_y_z(model_v *model, double x, double y, double z);

/// @brief This function retrieves the values x,y,i from the array of vertices
/// by index.
/// @param x This is the coordinate of the vertex on the x axis
/// @param y This is the coordinate of the vertex on the y axis
/// @param z This is the coordinate of the vertex on the z axis
/// @param index Index from an array of indexes
/// @param model To write values from a file.obj for further rendering.
/// @return The execution status is returned: success or error code.  Type: int
int index_vertex(double *x, double *y, double *z, int index, model_v *model);

/// @brief This function optimizes the vertex coordinates to fit the opengl
/// window size(-1 to 1)
/// @param model To write values from a file.obj for further rendering.
void optimize_for_the_size_of_the_opengl_window(model_v *model);

/// @brief This function finds the maximum value of the x y z coordinates, which
/// is the coefficient when working with the opengl projection type
/// @param model To write values from a file.obj for further rendering.
/// @param status The status: success or error code.  Type: int
void optimize_vector_value_head(model_v *model, int status);

/// @brief This function finds the maximum value by choosing from x, y and z
/// @param x_x value x
/// @param y_y value y
/// @param z_z value z
/// @return max value. type: double
double max_value(double x_x, double y_y, double z_z);

/// @brief The function of writing vertices to a vector
/// @param i index buffer
/// @param buffer string with file.obj
/// @param model To write values from a file.obj for further rendering.
/// @param count_v index-count vertex for vector - double *vertex_obj
/// @return status write
int write_vertex(int *i, char *buffer, model_v *model, unsigned *count_v);

////////////////////////////////////////////////////
/// @brief function in parser
/// @param file_obj (FILE)
/// @return file size in bytes (long int)
////////////////////////////////////////////////////
long int determine_the_file_size_in_bytes(FILE *file_obj);

/// @brief This function counts the number of vertices and the number of indexes
/// to allocate memory for arrays. (MEMORY ALLOCATION and deallocation!!!)
/// @param model To write values from a file.obj for further rendering.
/// @param buffer this is a string with data from a file. Type: char *
/// @return The status: success or error code.  Type: int
int counting_vertices_and_polygons_head(model_v *model, char *buffer);

/// @brief This is a string copy function(MEMORY ALLOCATION no memory release!)
/// @param string The string that is being copied. The original
/// @return Pointer to the copied string or null if memory is not allocated
char *my_strdup(char *string);

/// @brief This is a procedure of the rotation of the model along the x axis.
/// @param model To write values from a file.obj for further rendering.
/// @param angle_of_inclination value for rotation
void x_axis_rotation(model_v *model, double angle_of_inclination);

/// @brief This is a procedure of the rotation of the model along the y axis.
/// @param model To write values from a file.obj for further rendering.
/// @param angle_of_inclination value for rotation
void y_axis_rotation(model_v *model, double angle_of_inclination);

/// @brief This is a procedure of the rotation of the model along the z axis.
/// @param model To write values from a file.obj for further rendering.
/// @param angle_of_inclination value for rotation
void z_axis_rotation(model_v *model, double angle_of_inclination);

/// @brief This is a procedure of the displacement of the model along the
/// x-axis.
/// @param model To write values from a file.obj for further rendering.
/// @param coefficient Values for model offset
void move_the_model_along_the_x_axis(model_v *model, double coefficient);

/// @brief This is a procedure of the displacement of the model along the
/// y-axis.
/// @param model To write values from a file.obj for further rendering.
/// @param coefficient Values for model offset
void move_the_model_along_the_y_axis(model_v *model, double coefficient);

/// @brief This is a procedure of the displacement of the model along the
/// z-axis.
/// @param model To write values from a file.obj for further rendering.
/// @param coefficient Values for model offset
void move_the_model_along_the_z_axis(model_v *model, double coefficient);

/// @brief This is the procedure for scaling the model
/// @param model To write values from a file.obj for further rendering.
/// @param coefficient Values for scaling the model
void model_scale(model_v *model, double coefficient);

/// @brief Procedure for freeing the memory allocated during the reading of the
/// obj file. (for a file, for storing vertex coordinates, for storing indexes)
/// @param model Type: model_v* To write values from a file.obj for further
/// rendering.
void free_model(model_v *model);
#endif  // THREE_D_VIEWER_H
