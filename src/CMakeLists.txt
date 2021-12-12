set(HEADER_FILES
        ../include/rkb/Client.h)

set(SOURCE_FILES
        main.cpp
        Client.cpp)

link_directories(../lib)

add_executable(rkb ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(rkb PUBLIC ../include)
target_link_libraries(rkb PUBLIC
        sioclient)

#target_link_libraries(rkb PUBLIC
#        sioclient sioclient_tls)
