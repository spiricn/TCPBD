#ifndef WT_PACKET_H
#define WT_PACKET_H

#include <iostream>
#include <stdint.h>
#include <td/td.h>

#include "Buffer.h"

class Packet{
public:
	Packet();

	Packet(const std::string& data);

	Packet(const void* data, uint32_t size);

	Packet(const Packet& other);

	void clear();

	ByteBuffer& getPayload();

	const ByteBuffer& getPayload() const;

	template<class T>
	void write(const T& val){
		mData.put( reinterpret_cast<const uint8_t*>(&val), sizeof(T) );
	}

	void write(const void* data, uint32_t size);

	template<class T>
	void read(T* val){
		mData.get( reinterpret_cast<uint8_t*>(val), sizeof(T) );
	}

	void read(void* data, uint32_t size);

	void write(const std::string& data);

	template<class T>
	T read();

	void read(std::string* val);

private:
	ByteBuffer mData;

}; // </Packet>


template<class T>
T Packet::read(){
	T res;
	read(&res);

	return res;
}

#endif // </WT_PACKET_H>

