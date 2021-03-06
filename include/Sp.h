#ifndef TCPBD_SP_H
#define TCPBD_SP_H

template<class T>
class Sp{
public:
	Sp(T* ptr) : mRef(ptr), mRefCount(new uint32_t){
		*mRefCount = 1;
	}

	Sp() : mRefCount(0), mRef(NULL){
	}

	Sp(const Sp& other) : mRefCount(0), mRef(NULL){
		*this = other;
	}

	~Sp(){
		decRefCount();
	}

	uint32_t getRefCount() const{
		return mRefCount?*mRefCount:0;
	}

	Sp& operator=(const Sp& other){
		decRefCount();

		mRefCount = other.mRefCount;
		mRef = other.mRef;

		incRefCount();

		return *this;
	}

	operator bool() const{
		return mRef != NULL;
	}

	T* operator->(){
		return mRef;
	}

	T& operator*(){
		return *mRef;
	}

	const T* operator->() const{
		return mRef;
	}

	const T& operator*() const{
		return *mRef;
	}

	/* cast operators */
	operator T*(){
		return mRef;
	}

	operator const T*() const{
		return mRef;
	}


	T* get(){
		return mRef;
	}

	const T* get() const{
		return mRef;
	}
private:
	uint32_t* mRefCount;
	T* mRef;

	void incRefCount(){
		if(mRefCount){
			if(*mRefCount){
				(*mRefCount)++;
			}
		}
	}

	void decRefCount(){
		if(mRefCount){
			(*mRefCount)--;
			if(*mRefCount == 0){
				delete mRef;
				delete mRefCount;
				mRef = NULL;
				mRefCount = NULL;
			}
		}
	}

}; // </Sp>

#endif // </TCPBD_SP_H>
