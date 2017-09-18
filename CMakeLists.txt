cmake_minimum_required(VERSION 3.7)
project(JPEG_4_HLS)

SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_FLAGS "")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wno-overloaded-virtual -I/usr/local/systemc-2.3.1/include")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -std=c++14 -march=native -mtune=native")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SIMULATION_ -Wno-unknown-pragmas -Wno-unused-parameter")
SET (CMAKE_EXE_LINKER_FLAGS "")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/systemc-2.3.1/lib-macosx64 -lsystemc")
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dpm -lopencv_fuzzy -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_plot -lopencv_dnn -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core")
# pkg-config --cflags --libs opencv
SET (SOURCE_FILES \\
        ./src/DataSource/DataSource.cpp \\
        ./src/DataSink/DataSink.cpp \\
        ./src/RGB2YUV/RGB2YUV.cpp \\
        ./src/DCT2d/DCT2d.cpp \\
        ./src/Serializer/Serializer.cpp \\
        ./src/ZigZag/ZigZag.cpp \\
        ./src/Quantizer/Quantizer.cpp \\
        ./src/main.cpp)

add_executable(JPEG_processing ${SOURCE_FILES})
