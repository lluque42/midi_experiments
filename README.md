# MIDI & audio synthesis experiments - 2025

Luis Luque (luque.luis@gmail.com)

## Introduction

(check out development branch, since this will be at first mostly
experimenting and not so much anything worthy of production)

I don't know what this will end up being. Some things like MIDI messaging
interpreting and may be rendering (into a piano keyboard image); arbitrary
scales calculator; interval calculator; interactive circle of fifths;
interactive tonnetz; audio synthesis; Fourier transform and spectrum analysis
and manipulation; etc.

The thing is I'm a self-taught piano (and music theory) learner in the very
early stages and a passionate for coding, physics, math and communications,
so why not mixing it all together to harvest back the resulting procrastination
of being so multididisciplinary?

At the begining I suppose this program will at least be a beginner's piano
trainer (that's what inspire this in the first place).

The beginner's piano trainer, after detecting an input MIDI device, will
randomly ask for a particular note (or an interval, or a scale, or a scale
based on a particular note, etc.) and then will listen to the MIDI input
for the user attempt to comply with the request.

## Building and execution

Clone the repository using the url in the desired directory:
```
~$ git clone github_url project_directory
```

Initialize the library submodule by running this in the project directory:
```
~/project_directory$ git submodule update --init --recursive
```

For help on building options execute in the project directory:
```
~/project_directory$ make help
```

The output for 'make help' includes instruction for building with the
-g flag (neccesary for lldb, valgrind, etc.); MAKE_DEBUG_LVL for desired
extra debug output; and Doxygen documentation generation. An example of
the output for 'make help' is:
```
lluque@Z500-ubuntu:~/013_minishell/repo_github$ make help
----------------------------------------------------------------------

                          --- Ayuda ---

    usar 'make', 'make all' o 'make ./bin/mandatory/minishell' para compilar el proyecto base como: ./bin/mandatory/minishell
    usar 'make bonus' para compilar el proyecto en version bonus (en caso de estar disponible) como ./bin/mandatory/minishell
    usar 'make tester' para compilar el programa de pruebas (en caso de estar disponible) como ./bin/mandatory/tester
    usar 'make clean' para borrar los archivos .o y su directorio ./obj/
    usar 'make fclean' para hacer 'clean' y ademas borrar todos los binarios y su directorio ./bin/mandatory/
    usar 'make re' para hacer 'fclean' y luego 'all'
    usar 'make ... DEBUG=...' para hacer todas las compilaciones con estos flags adicionales:
        DEBUG=g      (e.g. para debugging con lldb)    ---> -g
        DEBUG=addsan (i.e. para reportar memory leaks) ---> -g -fsanitize=address
        (cualquier otro valor es ignorado)
    usar 'make ... MAKE_DEBUG_LVL=...' para compilar el código con un #define MAKE_DEBUG_LVL ...
        Se recomienda pasar un valor entero que sería usado en el código como MAKE_DEBUG_LVL
        para imprimir diferentes niveles de mensajes de debugging.
    usar 'make help' para mostrar esta ayuda

----------------------------------------------------------------------

```

For building the project without -g flag or debug outputs, run:
```
~/project_directory$ make
    or
~/project_directory$ make bonus
```

The binaries will be built at:
```
~/project_directory/bin/mandatory/
    or
~/project_directory/bin/bonus/
```

## Directory tree

    ./  
    ├── .gitignore				(to prevent undesired files to be stagged)
    ├── Doxyfile				(doxygen config file for doc generation)  
    ├── Makefile				(use 'make help' for instructions)  
    ├── README.md				(brief documentation)  
    ├── doc/					(documentation extracted from comments in .h)  
    │   ├── html/				(html documentation)  
    │   │   ├── ...  
    │   │   ├── index.html		(entry point for html documentation)  
    │   │   ├── ...  
    │   └── man/				(man pages documentation)  
    │       └── man3/  
    │           └── ...			(example of use: 'man -l ft_string.h.3')  
    ├── include/				(directory for public header files (.h))  
    │   ├── ...  
    │   └── ...  
    ├── src/					(dir for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  				
    │   │   └── ...  
    │   └── ...					(may be structured in several directories)  
    │       ├── ...  
    │       └── ...  
    ├── lib/					(external libraries)  
    │   ├── ...  
    │   └── libft				(each library in its own directory)  
    ├── bin/					(directory for project's binaries and tester)  
    │   ├── ...  
    │   └── ...					(may be structured in several directories)  
    ├── obj/					(dir for source code and private header files)  
    │   ├── ...  
    │   │   ├── ...  
    │   │   └── ...  
    │   └── ...					(structured as in ./src)  
    │       ├── ...  
    │       └── ...  
    ├── data/					(directory for non-source files)  
    └── test/					(test program src code, compiles to .bin/tester)
        ├── ...  
        ├── tester.c  
        └── ...  

## Program's data model
### Conventions adopted

        TODO
        TODO
        TODO
        (the following is a place-holder (and markdown formatting examples)
         from another project)
* When rendering, the right-handed convention for drawing XYZ axis will be
used, which implies:  
```
                +Z
                 |
                 |
                / \
               /   \
             +X     +Y
```
* The correspondence of the map matrix to the image spatial-wise is as
follows:
    * Moving through a ROW is analogous to move along the X coordinate.
        * The rightmost element in a row represents the altitude at X = 0.
        * The leftmost element in a row represents the altitude at the
        greatest positive value for axis X.
            * *The horizontal position corresponds to its axis (X).*
    * Moving through a COLUMN is analogous to move along the Y coordinate.
        * The top-most element in a column represents the altitude at Y = 0.
        * The bottom-most element in a column represents the altitude at the
        greatest positive value for axis Y.
            * *The vertical position corresponds to its ordinate (Y).*
    * Briefly stated:
        * The top-right element in the matrix corresponds to the altitude at
        XY origin (0,0).
        * The bottom-left element in the matrix corresponds to the altitude at
        (Xmax, Ymax).
```
                      <<< X  
        (Xmax,0) c0     cC (0,0)  
              r0  A .... B   Y  
                  .      .   v  
                  .      .   v  
              rR  C .... D   v  
      (Xmax,Ymax)          (0,Ymax)  

          B: (0,0)
          A: (Xmax,0)
          D: (0,Ymax)
          C: (Xmax, Ymax)

                +Z
                 |
                 | B (top-right matrix element)
                / \
               /   \
             +X     +Y
```
* Matrices nomenclature follows the mathematics standard:
```
    i: row index, starts at 0 (NOT 1)
    j: col index, starts at 0 (NOT 1)
    m: number of rows
    n: number of cols
    Aij: Element in row i col j. NOTICE that row index comes first...
            A00 A02 A03
            A10 A11 A12
            A20 A21 A22
```
* When representing matrix-like data, the native C matrix\[i\]\[j\] approach
(where matrix is of \*\*double type) is not used, because that implies an
array of array of pointers to memory in the HEAP which could "physically" be
anywhere (no contiguous blocks). A single array of \*double type was chosen
instead to represent the elements of a matrix in a sequential fashion assuring
all the data to be in the same memory block. This linear representation of a
matrix consists of store in a unidimensional array all the elements of a
matrix one after, that is, first all the elements of a row/col, followed by
all the elements of the next row/col, etc. Choosing between row-by-row or
col-by-col in this context is called row-major order (aka lexicographic order)
or column-major order (aka colexicographic order) respectively.

The convention used here is the row-major order (aka lexicographic order;
aka row-by-row).

The element addressing of an intuitive C-style matrix (array of arrays,
e.g. \*\*double or double[][]) translates to this addressing:
Given a m x n (rows x columns matrix, the element Aij is addressed in
this way...
```
     Intuitive C-style matrix    Linear storage (row-major order)

          double **data;                   double *data;

            data[i][j] >>>>>>>>>>>>>>>>>> data[i * n + j]
```
For example, a 2 x 5 matrix as it appears in the .fdf file:

As matrix format:
```
   10    11    12    13    14
   15    16    17    18    19
```
As it is actually storaged in memory as a unidimensional array using the
row-major order (aka lexicographic order; aka row-by-row):

**10 11 12 13 14** 15 16 17 18 19
* When representing a vertex matrix, that is, the result of interpreting the
map matrix as XYZW points (*the W component is a prevision for the future*),
each point data is storaged (**idiotically**) as a column vector (**a row
vector makes more sense when my whole freaking point is to optimize the
calculations this is a major TODO for the future**):

As matrix format:
```
    0     1     2     3     4     0     1     2     3     4
    0     0     0     0     0     1     1     1     1     1
   10    11    12    13    14    15    16    17    18    19
    1     1     1     1     1     1     1     1     1     1
```
As it is actually storaged in memory as a unidimensional array using the
row-major order (aka lexicographic order; aka row-by-row):

**0 1 2 3 4 0 1 2 3 4** 0 0 0 0 0 1 1 1 1 1 10 11 12 13 14 15 16 17 18 19 1...

* The MLX42 GUI image object has its own coordinate system where the XY origin
is at the top-left corner.
    * X values grow going to the left.
    * Y values grow going downward.
    * (The program deals with the coordinate system mismatch in some of the
    several transformations when rendering).

* Vertex color is supported for .fdf map files if an altitude value is
followed by ",0xhhhhhh" where h are hexadecimal digits representing RGB
values. This is transformed to the 8 bits per channel RGBA color model format
supported by MLX42 library as 0xhhhhhhFF (channel alpha value does not come
from the .fdf file and is always considered 0xFF).

### Data structures
    * Array of two matrices resulting from loading the .fdf map file. The
    first matrix contains altitude values (Z axis) while the second matrix
    contains color values (255 if map has no color info). The column and row
    in each matrix represents the X, Y coordinates.

## Program's internal working
### Core functions callings
* main() function does the following:
    * Checks validity of arguments.
    * Creates the fdf data structure which serves as an entry point to every
    other data.
    * Loads the .fdf file data into an array of two matrices (one for height
    or Z values and the other one for color values) by calling
    ft_mx_load_file().
    * Calls fdf_start_gui() which does the following:
        * fdf_start_gui() registers the hooks:
            * mlx_resize_hook() -> fdf_resizehook().
            * mlx_key_hook() -> fdf_keyhook().
            * mlx_close_hook() -> fdf_closehook().
            * mlx_loop_hook() -> fdf_generichook().
        * Creates the GUI: window, image, places the image on the window.
        * Then waits in the mlx_loop(). At this point (and until after the 
        window is closed or the ESCAPE key is pressed), only the hooks
        functions are called to act as a result of the GUI events.
            * When MLX loop breaks, fdf_start_gui() finishes the MLX clean up
            by calling mlx_terminate(). The MLX clean up process starts in the
            fdf_closehook() when it calls the fdf_exit_program() which calls
            the MLX functions mlx_delete_image() and mlx_close_window().  
      
  
*[...... while fdf_start_gui() is blocked in the MLX loop ......]*
* Asinchronously, fdf_generichook() is called on every MLX loop. This function
does the following:
    * Checks if the keys to translate/rotate/scale are pressed down. If any,
    this function updates the required transformation data through fdf
    structure object member and sets a t_render_request level at the fdf
    structure if a render is required as a result of the keys events.
        * *NOTE: Other hooks such as fdf_resizehook() and fdf_keyhook() also
        can independently change transformation data and set a render request
        level.*
    * Calls fdf_render() every loop. *NOTE: fdf_generichook() is the only
    caller of fdf_render().* This function is the last one that is called with
    fdf as an argument, from now on, every function is called passing the fdf
    member object. fdf_render() function does the following:
        * Checks the fdf t_render_request member fdf->render_request.
        * According to the render request level, fdf_render() successively
        calls the following function BUT starting with the one that correspond
        to the request level. In this way, only those stages of the rendering
        process that need to be recalculated as per the request level are
        performed. The functions that perform each stage of the rendering
        process are (in the logical order of precedence) the following:
            * fdf_tesselate_map() when render_request <= FROM_MODEL.
                * Read "Rendering process" section for details.
            * fdf_setup_world() when render_request <= FROM_WORLD.
                * Read "Rendering process" section for details.
            * fdf_setup_camera() when render_request <= FROM_CAMERA.
                * Read "Rendering process" section for details.
            * fdf_setup_screen() when render_request <= FROM_SCREEN.
                * Read "Rendering process" section for details.
            * fdf_setup_image() when render_request <= FROM_IMAGE.
                * Read "Rendering process" section for details.
        * Finally, fdf_render() resets the render request level to NO_RENDER
        and returns to fdf_generichook().  
  
The next section details what the rendering process functions
(fdf_tesselate_map(), fdf_setup_world(), fdf_setup_camera(),
fdf_setup_screen(), and fdf_setup_image()) do at each stage of the rendering
process.


### Rendering process
The rendering process entry point is the fdf_render() function, called from
the GUI loop hook fdf_generichook().

The rendering process has several stages, let's call them transformations,
which must be processed in this order, starting at the first stage that needs
to be re-calculated. The selection of the first stage is determined by the
render request level of fdf struct for each loop.

<table>
  <tr>
    <th>Transformation</th>
    <th>Details</th>
    <th>Render level request</th>
    <th>Associated function</th>
  </tr>
  <tr>
    <td>*file to array of altitude and color matrices that represents 
    the map info*</td>
    <td>*Not an actual part of the rendering process*</td>
    <td>*doesn't apply*</td>
    <td>ft_mx_load_file()</td>
  </tr>
  <tr>
    <td>Map to 3D model</td>
    <td>Either planar, spherical or cylindrical projection</td>
    <td><= FROM_MODEL</td>
    <td>fdf_tesselate_map()</td>
  </tr>
  <tr>
    <td>3D model to world</td>
    <td></td>
    <td><= FROM_WORLD</td>
    <td>fdf_setup_world()</td>
  </tr>
  <tr>
    <td>World to camera</td>
    <td></td>
    <td><= FROM_CAMERA</td>
    <td>fdf_setup_camera()</td>
  </tr>
  <tr>
    <td>Camera to screen</td>
    <td></td>
    <td><= FROM_SCREEN</td>
    <td>fdf_setup_screen()</td>
  </tr>
  <tr>
    <td>Screen to image</td>
    <td></td>
    <td><= FROM_IMAGE</td>
    <td>fdf_setup_image()</td>
  </tr>
  <tr>
    <td>Nothing to perform</td>
    <td></td>
    <td>== NO_RENDER</td>
    <td>return</td>
  </tr>
</table>
  
Not every rendering needs to go through all of these transformations,
but just need to start at one of them and perform the rest. The level from
which to start has to do with the requested actions:  
* *[Should the map change, it has to start with file-to-map level]*
* Should the projection type change, it has to start with map-to-model level.
* TODO

#### Loading the .fdf file

This is the process in which the .fdf file is parsed to create an array of two
matrices. Both matrices are of the same size, that is, rows and columns
positions representing the actual spatial 2D (XY plane) position of each
sample.

Each sample will be then transformed into a 3D vertex in the tesselation
stage.

There are two matrices because we need to storage two values for each point:
the altitude value (the Z component) and the color value.  
The function ft_mx_load_file() performs this stage, taking as argument the
filename for the .fdf map and the expected character separating the sample
information from the next sample information. The ft_mx_load_file() function
returns the array of the two matrices which will end up as the map_mx member
of the object struct that is the object member of the fdf struct.

A .fdf file may or may not have sample color information. The color
information is expected as a ',0xhhhhhh' string inmediately following each
altitude value. If no color information is found, ft_mx_load_file()
initializes the color matrix with FFFFFF for each sample.  

#### Tesselation: samples map to 3D model (where samples become vertices)
This is the stage where: (1) the samples obtained from loading the .fdf file
(2D position at XY plane + altitude) are used to create actual 3D XYZ points
in space, this is dependent upon the type of projection: planar, spherical,
or cylindrical; (2) for each of the samples (spatial-info-wise) a relationship
is stablished with its neighboring samples in the matrix, this relationship
is represented in an edge array and is the base for eventually drawing lines
that connect each vertex only to its orthogonal neighbor vertices (or, in
bonus version, also to its non-orthogonal neighbors that makes spatial sense;
or to every neighbor). Each edge also contains the numeric value for the color
of the start and end vertex.

In (1) one of this three functions: fdf_get_vertex_mx(),
fdf_get_vertex_mx_sph(), or fdf_get_vertex_mx_cyl() is used to create a matrix
in which each column ?????? is a XYZW 3D point in space (a vertex).
This matrix will become the model_mx member of the object, which is the object
member of fdf.

In (2) the fdf_get_edge() creates an array of edges, an edge is  a struct
type that has four key members: start and end, and start_color and end_color.
The start and end members represent the index in the vertex matrix of the
starting vertex of the edge and the end vertex of the edge.  
The start_color and end_color members contain the uint32_t value of the color
of the start and end vertex. Clearly, each edge (if not hidden) will become a
line on the image.
*The call to fdf_get_edge() is performed only once, when the model_mx member
of the object is NULL, since the edge information (what point connects to
another point and what colors should be used) will be the same for any
tesselation projection type.*
 
Both the vertex matrix column index (1) and the start/end members in the edges
array indices (3) refer to the information of the same 3D vertex.

The next stages of the rendering process after tesselating the map consists of
several succesive transformations from the vertex matrix for a stage to obtain
the vertex matrix of the next stage. This vertex matrices are called spaces.
These transformations to "get" the object to one space to the next, consist of
succesively multiplying the previous vertex matrix (that represents the same
points but in a particular space: the 3D object now placed in the world;
the 3D object in the world but now from the point of view from the camera;
or the 2D projection of the later to the screen) by different transformation
matrices (to rotate, translate, scale, project) to generate the new vertex
matrix for the next space.

#### 3D model space to world space transformation
TODO

#### World space transformation to camera space transformation
TODO

#### Camera space to screen space transformation
TODO

#### Screen space to image space transformation
In this stage, the vertex matrix representing the screen space is used to,
finally, draw all the lines (edges) on the image. This job is ultimately
perform by the fdf_drw_edges() function.

The fdf_drw_edges() function takes the object and the image element of the GUI
and uses its auxiliary functions to draw each edge as a line onto the image.

##### Inner working of fdf_drw_edges() function
This function loops through the edges array skipping the edges flagged as
hidden and for each non-skipped edge:
* A line struct is created using fdf_create_line() function with the
arguments:
X value of the edge starting vertex; Y value of the edge starting vertex;
X value of the edge end vertex; Y value of the edge end vertex.
* TODO fdf_set_line_color_info() TODO !!!!!!!!!!!!!!
* Finally, the fdf_drw_edges() calls the fdf_draw_line() which actually draws
the line.

The fdf_drw_edges() auxiliary functions inner workings are detailed in the
following sections.

*NOTE: Bonus version edge skipping process in fdf_drw_edges() is more or less
strict depending on the user's selection to draw or not valid non-orthogonal
edges or every non-orthogonal edges).*

###### Inner working of fdf_create_line() function
TODO

###### Inner working of fdf_set_line_color_info() function
TODO

###### Inner working of fdf_draw_line() function
TODO
