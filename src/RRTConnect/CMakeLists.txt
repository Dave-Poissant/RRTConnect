# Find source files
FILE(GLOB_RECURSE RRTCONNECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build library
add_library(RRTConnectLib STATIC
    ${RRTCONNECT_SOURCES}
)

target_link_libraries(RRTConnectLib
    ${RRTCONNECT_PACKAGES_LIBRARIES}
    ${RRTCONNECT_DEPENDENCIES}
)