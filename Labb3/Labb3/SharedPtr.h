#pragma once
#pragma once
#include <cassert>

template<typename T>
class ControlBlock
{
public:
	int count = 1;

	T* object;

	ControlBlock(T* obj)
	{
		object = obj;
		count = 1;
	}

	ControlBlock()
	{
		object = nullptr;
		count = 1;
	}

	T* GetObject()
	{
		return object;
	}

	int GetCount()
	{
		return count;
	}
	void IncreaseCount()
	{
		count++;
	}

	void DecreaseCount()
	{
		count--;
	}

	~ControlBlock()
	{
		delete object;
		object = nullptr;
	}
};

template<typename T>
class SharedPtr
{
	ControlBlock<T>* cBlock;

public:

	SharedPtr();
	SharedPtr(T* ptr);
	SharedPtr(const SharedPtr& rhs);
	SharedPtr(SharedPtr&& rhs);


	SharedPtr& operator=(SharedPtr<T>&);
	bool operator==(const SharedPtr& rhs) const;
	bool operator<(const SharedPtr<T>& rhs);
	operator bool()
	{
		if (cBlock == nullptr || Get() == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	T& operator*() const
	{
		return *cBlock->GetObject();
	}
	T* operator->() const
	{
		return cBlock->GetObject();
	}
	T* Get() const
	{
		return cBlock->GetObject();
	}

	void Reset(T* ptr = nullptr);
	bool Unique()
	{
		assert(Invariant());

		if (cBlock->GetCount() <= 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


public:
	bool Invariant()
	{
		if (cBlock != nullptr)
		{
			if (cBlock->GetCount() > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	~SharedPtr()
	{
		Reset();
	}
};

template<typename T>
SharedPtr<T>::SharedPtr()
{
	cBlock = new ControlBlock<T>();
}

template<typename T>
SharedPtr<T>::SharedPtr(T * ptr)
{
	cBlock = new ControlBlock<T>(ptr);
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr & rhs)
{
	rhs.cBlock->IncreaseCount();
	cBlock = rhs.cBlock;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr && rhs)
{
	cBlock = rhs.cBlock;
	rhs.cBlock = nullptr;
}

template<typename T>
bool SharedPtr<T>::operator==(const SharedPtr& rhs) const
{
	if (Get() == rhs.Get())
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<typename T>
void SharedPtr<T>::Reset(T* ptr = nullptr)
{
	cout << "ny" << std::endl;
	assert(Invariant());

	if (cBlock != nullptr)
	{
		if (cBlock->count == 1)
		{
			cout << "delete" << std::endl;
			delete cBlock;
		}
		else if (cBlock->count > 1)
		{
			cBlock->DecreaseCount();
		}
	}

	if (ptr != nullptr)
	{
		cBlock = new ControlBlock<T>(ptr);
	}
	else
	{
		cBlock = nullptr;
	}

	assert(Invariant());
	cout << "klar" << std::endl;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>& rhs)
{
	assert(Invariant());
	if (cBlock != rhs.cBlock)
	{
		rhs.cBlock->IncreaseCount();
		cBlock = rhs.cBlock;
	}
	assert(Invariant());
	return *this;
}


template<typename T>
bool SharedPtr<T>::operator<(const SharedPtr<T>& rhs)
{
	assert(Invariant());
	if (Get() < rhs.Get())
	{
		return true;
	}
	else
	{
		return false;
	}
}