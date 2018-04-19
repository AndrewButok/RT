cmake_minimum_required(VERSION 3.9)
project(RT C)

set(CMAKE_C_STANDARD 99)

find_library(MLX mlx)
find_library(OPENGL OpenGL)
find_library(APPKIT AppKit)

AUX_SOURCE_DIRECTORY(libft LIBFT_SRC)
set(PARSON_SRC parson/parson.c)
set(SOURCE_FILES
        includes/rt.h
        src/main.c
        includes/rt.h
        src/vector/vector.c
        src/figure/fsphere.c
        src/figure/figure.c
        src/figure/fcylinder.c
        src/vector/vector2.c
        src/light/light.c
        src/do_rt.c
        src/color/color.c
        src/space.c
        src/vector/rotate.c
        src/figure/fplane.c
        src/figure/fcone.c
        src/parse/parse.c
        src/parse/ft_hexatoi.c
        src/parse/perror.c
        src/parse/psphere.c
        src/parse/pplane.c
        src/parse/pcylinder.c
        src/parse/pcone.c src/parse/plight.c src/parse/pcam.c
        src/parse/ptriangle.c
        src/figure/ftriangle.c)

add_library(ft ${LIBFT_SRC})
add_library(parson ${PARSON_SRC})
add_executable(RT ${SOURCE_FILES})
target_link_libraries(RT ft parson ${OPENGL} ${APPKIT} ${MLX} ${OPENCL})
include_directories(includes parson libft/includes /usr/local/include)