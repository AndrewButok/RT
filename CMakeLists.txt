 cmake_minimum_required(VERSION 3.9)
project(RT C)

set(CMAKE_C_STANDARD 99)

find_library(SDL SDL2)
find_library(OPENCL OpenCL)

AUX_SOURCE_DIRECTORY(libft LIBFT_SRC)
set(PARSON_SRC parson/parson.c )
set(SOURCE_FILES
        includes/rt.h
        src/parse/ft_hexatoi.c
        src/main.c
        src/parse/get_space.c
        src/parse/get_sphere.c
        src/parse/get_vector.c
        src/parse/get_figure_params.c
        src/parse/get_infinite_plane.c
        src/parse/get_infinite_cone.c
        src/vector/vector.c
        src/scene_objects/infinite_cylinder.c
        src/parse/get_infinite_cylinder.c
        src/parse/get_light.c
        src/scene_objects/sphere.c
        src/scene_objects/infinite_plane.c
        src/scene_objects/infinite_cone.c
        src/scene_objects/infinite_cylinder.c
        src/scene_objects/light_init.c
        src/cl.c
        src/cl2.c
        src/parse/get_cam.c
        src/parse/get_params.c
        src/scene_objects/cylinder.c
        src/parse/get_cylinder.c src/parse/get_cone.c src/scene_objects/cone.c src/parse/get_triangle.c src/scene_objects/triangle.c src/parse/get_ellipsoid.c src/scene_objects/ellipsoid.c src/parse/get_figure_texture.c)

add_library(ft ${LIBFT_SRC})
add_library(parson ${PARSON_SRC})
add_executable(RT ${SOURCE_FILES})
target_link_libraries(RT ft parson ${SDL} ${OPENCL})
include_directories(includes parson libft/includes /Library/Frameworks/SDL2.framework/Headers)