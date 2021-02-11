cmake_minimum_required(VERSION 3.13)
project(idps-20-21)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -pthread")
add_executable(idps-20-21 Sources/main.cpp Sources/FeatureExtractor.cpp Sources/Packet.cpp Sources/PacketsReader.cpp Sources/PacketsReaderSQLITE.cpp Sources/PacketsReaderCSV.cpp Sources/FeatureExtractor.cpp Sources/IncStats.cpp Sources/IncStatsData.cpp Sources/IncStatsDataSocket.cpp Sources/IncStatsDataChannel.cpp Sources/Time.cpp Sources/FeatureMapper.cpp Sources/Cluster.cpp Sources/Parser.cpp Sources/RelativeIncStats.cpp Sources/AnomalyDetector.cpp)
target_link_libraries(idps-20-21 LINK_PUBLIC sqlite3)
