set(HEADER_FILES
        ../include/rkb/common.h
        ../include/rkb/Client.h
        ../include/rkb/Keyboard.h)

set(SOURCE_FILES
        main.cpp
        Client.cpp
        Keyboard.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include ../vendors/src)
target_link_libraries(${PROJECT_NAME} PUBLIC
        sioclient)

#target_link_libraries(rkb PUBLIC
#        sioclient sioclient_tls)
