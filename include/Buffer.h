#ifndef TCPBD_BUFFER_H
#define TCPBD_BUFFER_H

#include <td/td.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template<class T>
class Buffer{

private:
	T* mData;
	int32_t mCapacity, mPosPut, mPosGet;

public:
	Buffer() : mData(NULL), mCapacity(0), mPosPut(0), mPosGet(0){
	}

	Buffer(uint32_t capacity){
		mData=NULL;
		mCapacity=0;
		mPosPut=0;
		mPosGet=0;
		create(capacity);
	}

	void copy(Buffer& dst) const{
		dst.create(mCapacity);

		memcpy(dst.mData, mData, sizeof(T)*mCapacity);

		dst.mPosPut = mPosPut;
		dst.mPosGet = mPosGet;
	}

	void create(uint32_t capacity){
		this->destroy();

		mCapacity = capacity;
		mPosPut=0;
		mPosGet=0;
		mData = new T[mCapacity];
	}

	void clearMem(unsigned char val=0x00){
		memset(mData, val, this->getSize());
	}

	void grow(int32_t newCapacity){
		TD_ASSERT(newCapacity > mCapacity, "Invalid grow capacity");

		T* newData = new T[newCapacity];
		memcpy(newData, mData, mCapacity*sizeof(T));

		mCapacity = newCapacity;

		T* tmp = mData;
		mData = newData;

		delete[] tmp;
	}

	/** returns the maximum number of elements of type T this buffer is able to contain */
	uint32_t getCapacity() const{
		return mCapacity;
	}

	/** returns the total buffer size in BYTES */
	uint32_t getSize() const{
		return mCapacity*sizeof(T);
	}

	uint32_t tellg() const{
		return mPosGet;
	}

	uint32_t tellp() const{
		return mPosPut;
	}

	void seekp(uint32_t pos){
		#ifdef WT_CHECKED
		if(pos > mCapacity){
			WT_THROW("Seek position out of bounds (bounds=%d, pos=%d)",
				mCapacity, pos);
		}
		#endif

		mPosPut = pos;
	}

	void seekg(uint32_t pos){
		#ifdef WT_CHECKED
		if(pos > mCapacity){
			WT_THROW("Seek position out of bounds (bounds=%d, pos=%d)",
				mCapacity, pos);
		}
		#endif

		mPosGet = pos;
	}

	void destroy(){
		if(mData != NULL){
			delete[] mData;
			mData=NULL;
		}

		mCapacity=0;
		mPosGet=0;
		mPosPut=0;
	}

	T* getData(){
		return mData;
	}

	const T* getData() const{
		return mData;
	}

	void get(T* val, int32_t count){
		TD_ASSERT(mPosGet+count <= mCapacity, "Buffer underflow");

		memcpy(val, mData+mPosGet, count*sizeof(T));
		mPosGet += count;
	}

	void get(T* val){
		get(val, 1);
	}

	void put(const T* t, int32_t count){
		if(mPosPut+count > mCapacity){
			// Grow
			grow(mPosPut+count);
		}

		memcpy(mData+mPosPut, t, count*sizeof(T));
		mPosPut += count;
	}

	void put(const T& t){
		put(&t, 1);
	}

	T& operator[](uint32_t index){
		#ifdef WT_CHECKED
		if(index >= mCapacity){
			WT_THROW("Attempted to index buffer (size %d) index %d", mCapacity, index);
		}
		#endif

		return mData[index];
	}

	const T& operator[](uint32_t index) const{
		#ifdef WT_CHECKED
		if(index >= mCapacity){
			WT_THROW("Attempted to index buffer (size %d) index %d",
				mCapacity, index);
		}
		#endif

		return mData[index];
	}

	~Buffer(){
		destroy();
	}


}; // </Buffer>

typedef Buffer<float> FloatBuffer;

typedef Buffer<uint8_t> ByteBuffer;

#endif // </TCPBD_BUFFER_H>
