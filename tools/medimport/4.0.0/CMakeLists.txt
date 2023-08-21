SET(medimport400_SOURCES
  MAJ_400_410_champs.c
)

FILE(COPY "${PROJECT_SOURCE_DIR}/src/ci/_MEDfieldValueUpdateEntityList41.c" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

# On Win platform, we need to make sure symbols are properly exported in
# the intermediary OBJECT targets
# The definition "-D<target>_EXPORTS" is normally added automatically by CMake
# when building Win DLL,
# but this doesn't work when using intermediary targets (ADD_LIBRARY(... OBJECT ...)
IF(WIN32)
  ADD_DEFINITIONS(-Dmedimport_EXPORTS)
ENDIF()

ADD_LIBRARY(_medimport400 OBJECT ${medimport400_SOURCES})

ADD_LIBRARY(_medimport400_static OBJECT ${medimport400_SOURCES})
MED_SET_DEFINITIONS(_medimport400_static MED3_USESTATIC)
