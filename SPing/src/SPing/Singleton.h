#pragma once

template<typename T>
class Singleton
{
public:
	Singleton() = delete;
	Singleton(const Singleton&) = delete;
	Singleton& operator =(const Singleton&) = delete;

	~Singleton() {
		if (_singleton)
		{
			delete _singleton;
			_singleton = nullptr;
		}
	}

public:
	static T& Instance()
	{
		if (_singleton == nullptr)
		{
			_singleton = new T();
		}
		return *_singleton;
	}

private:
	static T* _singleton;
};

template<typename T>
T* Singleton<T>::_singleton = nullptr;