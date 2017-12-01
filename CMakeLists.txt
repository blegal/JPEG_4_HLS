cmake_minimum_required(VERSION 3.7)
project(JPEG_4_HLS)

SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_FLAGS "")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -I/usr/local/systemc-2.3.2/include")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native -mtune=native")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SIMULATION_ -Wno-unknown-pragmas -Wno-unused-parameter")
SET (CMAKE_EXE_LINKER_FLAGS "")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/systemc-2.3.2/lib-linux64 -lsystemc")

SET (SOURCE_FILES \\
        ./src/DataSource/DataSource.cpp \\
        ./src/DataSource/CBitmap.cpp \\
        ./src/DataSource/CImage.cpp \\
        ./src/DataSource/CLigne.cpp \\
        ./src/DataSource/CPixel.cpp \\
        ./src/DataSink/DataSink.cpp \\
        ./src/RGB2YUV/RGB2YUV.cpp \\
        ./src/DCT2d/DCT2d.cpp \\
        ./src/Serializer/Serializer.cpp \\
        ./src/ZigZag/ZigZag.cpp \\
        ./src/Quantizer/Quantizer.cpp \\
        ./src/Encoder/Encoder.cpp \\
        ./src/Encoder/HardEncoder.cpp \\
        ./src/main.cpp)

add_executable(JPEG_processing ${SOURCE_FILES})
