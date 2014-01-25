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

	void write(const std::string& data);

	bool read(std::string* val);

	template<class T>
	bool read(T* val){
		if((mData.getCapacity() - mData.tellg()) < sizeof(T)){
			return false;
		}

		mData.get( reinterpret_cast<uint8_t*>(val), sizeof(T) );

		return true;
	}

	bool read(void* data, uint32_t size);

private:
	ByteBuffer mData;

}; // </Packet>

#endif // </WT_PACKET_H>

