# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget SphericalProjection::SphericalProjection SphericalProjection::CSVReader SphericalProjection::main)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target SphericalProjection::SphericalProjection
add_library(SphericalProjection::SphericalProjection STATIC IMPORTED)

set_target_properties(SphericalProjection::SphericalProjection PROPERTIES
  INTERFACE_LINK_LIBRARIES "opencv_calib3d;opencv_core;opencv_dnn;opencv_features2d;opencv_flann;opencv_gapi;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_stitching;opencv_video;opencv_videoio;opencv_alphamat;opencv_aruco;opencv_bgsegm;opencv_bioinspired;opencv_ccalib;opencv_datasets;opencv_dnn_objdetect;opencv_dnn_superres;opencv_dpm;opencv_face;opencv_freetype;opencv_fuzzy;opencv_hdf;opencv_hfs;opencv_img_hash;opencv_intensity_transform;opencv_line_descriptor;opencv_mcc;opencv_optflow;opencv_phase_unwrapping;opencv_plot;opencv_quality;opencv_rapid;opencv_reg;opencv_rgbd;opencv_saliency;opencv_shape;opencv_stereo;opencv_structured_light;opencv_superres;opencv_surface_matching;opencv_text;opencv_tracking;opencv_videostab;opencv_wechat_qrcode;opencv_xfeatures2d;opencv_ximgproc;opencv_xobjdetect;opencv_xphoto"
)

# Create imported target SphericalProjection::CSVReader
add_library(SphericalProjection::CSVReader STATIC IMPORTED)

# Create imported target SphericalProjection::main
add_executable(SphericalProjection::main IMPORTED)

# Import target "SphericalProjection::SphericalProjection" for configuration "Debug"
set_property(TARGET SphericalProjection::SphericalProjection APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SphericalProjection::SphericalProjection PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/home/hvh/MyGit/SphericalProjection/build/libSphericalProjection.a"
  )

# Import target "SphericalProjection::CSVReader" for configuration "Debug"
set_property(TARGET SphericalProjection::CSVReader APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SphericalProjection::CSVReader PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/home/hvh/MyGit/SphericalProjection/build/libCSVReader.a"
  )

# Import target "SphericalProjection::main" for configuration "Debug"
set_property(TARGET SphericalProjection::main APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SphericalProjection::main PROPERTIES
  IMPORTED_LOCATION_DEBUG "/home/hvh/MyGit/SphericalProjection/build/main"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
