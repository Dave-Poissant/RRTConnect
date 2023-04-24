add_executable(RRTConnect main.cpp)
target_link_libraries(RRTConnect 
    PUBLIC RRTConnectLib
    ${RRTCONNECT_DEPENDENCIES}
)