#include <iostream>
#include "MyMes.pb.h"

int main() {
	MyMes mes;
	mes.set_id(2);
	mes.set_amount(3.4);
	mes.set_name("aye");

	// serialize
	std::string serializedData;
	mes.SerializeToString(&serializedData);

	// std::cout<<"Serialized Str: "<<serializedData<<std::endl;
	
	// deserialize
	MyMes mes2;
	if(mes2.ParseFromString(serializedData)){
		std::cout<<"Id: "<< mes2.id()<<std::endl;
		std::cout<<"Amount: "<< mes2.amount()<<std::endl;
		std::cout<<"Name: "<< mes2.name()<<std::endl;
	}
	else {
		std::cerr<<"Failed to parse MyMes"<<std::endl;
	}

	return 0;
}

