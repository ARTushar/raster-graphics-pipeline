cmake_minimum_required(VERSION 3.14)
project(RasterPipeline)

set(CMAKE_CXX_STANDARD 17)

add_executable(RasterPipeline main.cpp utils/point/Point.h utils/transformation/Transformation.cpp utils/transformation/Transformation.h pipeline/projection/Projection.cpp pipeline/projection/Projection.h pipeline/model/Model.cpp pipeline/model/Model.h pipeline/view/View.cpp pipeline/view/View.h pipeline/Pipeline.cpp pipeline/Pipeline.h utils/matrix/Matrix.cpp utils/matrix/Matrix.h utils/command/Command.cpp utils/command/Command.h utils/triangle/Triangle.cpp utils/triangle/Triangle.h pipeline/clipping/Clipping.cpp pipeline/clipping/Clipping.h utils/image/bitmap_image.hpp)