#include "Packet.h"

Packet::Packet(){
}

Packet::Packet(const Packet& other){
	other.mData.copy( mData );
}

ByteBuffer& Packet::getPayload(){
	return mData;
}

const ByteBuffer& Packet::getPayload() const{
	return mData;
}

Packet::Packet(const std::string& data){
	write(data.c_str(), data.size() + 1);
}

Packet::Packet(const void* data, uint32_t size){
	write(data, size);
}

void Packet::clear(){
	mData = ByteBuffer();
}

bool Packet::read(void* data, uint32_t size){
	if( (mData.getCapacity() - mData.tellg()) < size){
		return false;
	}

	mData.get(static_cast<uint8_t*>(data), size);

	return true;
}

void Packet::write(const void* data, uint32_t size){
	mData.put(static_cast<const uint8_t*>(data), size);
}

void Packet::write(const std::string& val){
	mData.put( reinterpret_cast<const uint8_t*>( val.c_str() ), val.size() + 1 );
}

bool Packet::read(std::string* val){
	uint8_t* start = mData.getData() + mData.tellg();

	bool found = false;

	// Search for a NULL terminator
	for(uint32_t i=0; i<mData.getCapacity() - mData.tellg(); i++){
		if(start[i] == 0){
			found = true;
			break;
		}
	}

	// No NULL terminator found, can't create string
	if(!found){
		return false;
	}

	*val = std::string( reinterpret_cast<char*>( start ) );

	mData.seekg( mData.tellg() + val->size() + 1 );

	return true;
}

