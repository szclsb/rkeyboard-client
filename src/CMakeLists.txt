set(HEADER_FILES
        #../include/rkb/Client.h
        ../include/rkb/Keyboard.h)

set(SOURCE_FILES
        main.cpp
        #Client.cpp
        Keyboard.cpp)

link_directories(../lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_link_libraries(${PROJECT_NAME} PUBLIC
        sioclient)

#target_link_libraries(rkb PUBLIC
#        sioclient sioclient_tls)
