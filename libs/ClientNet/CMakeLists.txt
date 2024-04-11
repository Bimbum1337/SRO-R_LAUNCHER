add_library(ClientNet STATIC src/ClientNet/Msg.cpp src/ClientNet/Msg.h src/ClientNet/BSNet.h src/ClientNet/NetEngine.cpp src/ClientNet/NetEngine.h)

target_sources(ClientNet PRIVATE
        src/ClientNet/ClientNet.cpp
        )

target_link_libraries(ClientNet PUBLIC )
target_include_directories(ClientNet PUBLIC src/)
