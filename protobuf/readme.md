sudo apt install protobuf-compiler libprotobuf-dev
protoc --cpp_out=. MyMes.proto
g++ -std=c++11 -o mymes MyMes.pb.cc mymes.cpp -lprotobuf
./mymes
