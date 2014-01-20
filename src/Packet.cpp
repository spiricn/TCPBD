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

void Packet::read(void* data, uint32_t size){
	mData.get(static_cast<uint8_t*>(data), size);
}

void Packet::write(const void* data, uint32_t size){
	mData.put(static_cast<const uint8_t*>(data), size);
}

void Packet::write(const std::string& val){
	mData.put( reinterpret_cast<const uint8_t*>( val.c_str() ), val.size() + 1);
}

void Packet::read(std::string* val){
	// TODO probably not safe
	*val = std::string( reinterpret_cast<char*>( mData.getData() + mData.tellg()  ) );
	mData.seekg( mData.tellg() + val->size() + 1 );
}

