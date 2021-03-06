# Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Alberto Cardellino
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

yarp_prepare_plugin(faceDisplayServer
                    CATEGORY device
                    TYPE cer::dev::FaceDisplayServer
                    INCLUDE faceDisplayServer.h)

project(FaceDisplayServer)

IF (ENABLE_faceDisplayServer)

  ## Use opencv
  find_package(OpenCV)
  if(NOT OpenCV_FOUND)
      message(WARNING "OpenCV was not found therefore FaceDisplayServer cannot be compiled. Please disable it or install OpenCV.")
      return()
  endif(NOT OpenCV_FOUND)


  include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${OPENCV_INCLUDE_DIR})

  yarp_add_plugin(faceDisplayServer faceDisplayServer.cpp faceDisplayServer.h)
  TARGET_LINK_LIBRARIES(faceDisplayServer ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})
  link_directories(${OpenCV_LIB_DIR})

  yarp_install( TARGETS faceDisplayServer
                COMPONENT Runtime
                 EXPORT YARP_${YARP_PLUGIN_MASTER}
                LIBRARY DESTINATION ${CER_DYNAMIC_PLUGINS_INSTALL_DIR}
                YARP_INI DESTINATION ${CER_PLUGIN_MANIFESTS_INSTALL_DIR})

       
ENDIF (ENABLE_faceDisplayServer)

