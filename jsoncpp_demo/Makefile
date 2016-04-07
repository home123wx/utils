object = json_value.o json_writer.o json_read.o
jsoncpp_a=jsoncpp.a

all: jsoncpp.a client server

jsoncpp.a:$(object)
	ar -cr $@ $(object)

client:client.o
	g++ $< -o $@ $(jsoncpp_a)

server:server.o
	g++ $< -o $@ $(jsoncpp_a)

client.o:client.cpp
	g++ -c $< -o $@

server.o:server.cpp
	g++ -c $< -o $@

json_value.o:lib_json/json_value.cpp
	g++ -c $< -o $@

json_writer.o:lib_json/json_writer.cpp
	g++ -c $< -o $@

json_read.o:lib_json/json_reader.cpp
	g++ -c $< -o $@

clean:
	rm -f jsoncpp.a
	rm -f *.o client server
