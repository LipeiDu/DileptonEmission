set (SOURCES
     Hydroinfo_h5.cpp
     Arsenal.cpp
     ThermalPhoton.cpp
     Table2D.cpp
     PhotonEmission.cpp
     ParameterReader.cpp
     tensor_trans.cpp
     gauss_quadrature.cpp
     Hydroinfo_MUSIC.cpp
     QGP_LO_analytic.cpp
     QGP_NLO.cpp
     QGP_LO.cpp
    )

add_library(${libname} SHARED ${SOURCES})
target_link_libraries(${libname} ${HDF5_LIBRARIES} gsl gslcblas)

if (link_with_lib)
    add_executable(${exename} main.cpp)
    target_link_libraries(${exename} ${libname} ${HDF5_LIBRARIES} gsl)
else (link_with_lib)
    add_executable(${exename} main.cpp ${SOURCES})
    target_link_libraries(${exename} ${libname} ${HDF5_LIBRARIES} gsl)
endif (link_with_lib)

install(TARGETS ${exename} ${libname}
        RUNTIME DESTINATION ${CMAKE_HOME_DIRECTORY}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)