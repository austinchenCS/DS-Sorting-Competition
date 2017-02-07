#ifndef VECTOR
#define VECTOR

#include<iostream>

template<class T>
class Vector{

  public:
      Vector();
      Vector(int);
      Vector(const Vector<T>&);
      void add(T);
      void add(T, int);
      T get(int);
      ~Vector();
      int size();
      int getCap();
      void sort();
      void sort(int, int);
      void insertionSort(int, int);
      T& operator[](int);
      Vector<T>& operator=(Vector<T>&);
      Vector<T>& operator+=(T);

  private:
      T* arr;
      int length;
      int capacity;
      void resize();
};

// return current vector length (ie: how many elements present)
template<class T>
int Vector<T>::size()
{
    return this->length;
}

//return current vector capacity
template<class T>
int Vector<T>::getCap()
{
    return this->capacity;
}

//default constructor
template<class T>
Vector<T>::Vector()
{
    length = 0;
    capacity = 10;// i].add(currentPage);
    arr = new T[capacity];
}

//constructor with capacity arg
template<class T>
Vector<T>::Vector(int cap)
{
    length = 0;
    this->capacity = cap;
    arr = new T[capacity];
}

//copy constructor
template<class T>
Vector<T>::Vector(const Vector<T> & otherVector)
{
    this->arr = new T[(otherVector.capacity)];
    this->length = otherVector.length;
    this->capacity = otherVector.capacity;
    for(int i = 0; i < length; i++)
    {
        arr[i] = otherVector.arr[i];
    }

}

//append
template<class T>
void Vector<T>::add(T obj)
{
    if(length == capacity)
    {
        this->resize();
    }

    this->arr[length] = obj;
    length++;
}

//insert and shift right
template<class T>
void Vector<T>::add(T obj, int indexLocation)
{
    //if no room, resize
    if(length == capacity)
    {
        this->resize();
    }

    //append to end
    if(indexLocation >= length || indexLocation < 0)
    {
       this->arr[length] = obj;
       length++;
    }

    else
    {
        //copy previously existing data
        for(int i = length; i > indexLocation; i--)
        {
            arr[i] = arr[i-1];
        }

        this->arr[indexLocation] = obj;
        length++;
    }

}

template<class T>
T Vector<T>::get(int indexLocation)
{
    if(indexLocation < 0 || indexLocation >= length)
    {
        //python implementation of index location out of bounds
        //need to implement exception handling
        return this->arr[(indexLocation % length)];
    }

    else
    {
        return this->arr[indexLocation];
    }

}

template<class T>
Vector<T>::~Vector()
{
    if(arr != nullptr)
    {
        delete[] arr;
    }

}

//no arg sort
template<class T>
void Vector<T>::sort()
{
    sort(0, (this->length - 1));
}

//quicksort implementation
//modified to function with templated class
template<class T>
void Vector<T>::sort(int left, int right)
{
    int i = left, j = right;
    T tmp;
    T pivot = arr[(left + right) / 2];

    while (i <= j)
    {
          while (arr[i] < pivot)
                i++;
          while (arr[j] > pivot)
                j--;
          if (i <= j)
          {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
          }
    };

    if (left < j)
          sort(left, j);

    if (i < right)
          sort(i, right);

}

template<>
void Vector<char*>::insertionSort(int left, int right)
{
    int i = left, j = right;
    char* tmp;

    for (i; i < (right-left); i++)
    {
        j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;
            j--;
        }
    }
}

//method overloaded
//manual redefinition for char*
template<>
void Vector<char*>::sort(int left, int right)
{
	int i = left, j = right;
	char* tmp;
	char* pivot = arr[(left + right) / 2];

	while (i <= j)
	{
		while (std::strcmp(arr[i], pivot) < 0)
			i++;
		while (std::strcmp(arr[j], pivot) > 0)
			j--;

		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

    if ((j - i) <= 18)
    {
        insertionSort(i, j);
    }

	if (left < j)
		sort(left, j);

	if (i < right)
		sort(i, right);
}




template<class T>
T& Vector<T>::operator[](int indexLocation)
{
    return this->arr[indexLocation];
}

template<class T>
void Vector<T>::resize()
{
    this->capacity *= 50;
    T* ptr = new T[capacity];
    for(int i = 0; i < length; i++)
    {
        ptr[i] = arr[i];
    }

    delete [] arr;
    arr = ptr;
}

//assignment operator
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& otherVector)
{
    //same functionality as copy constructor
    this->arr = new T[(otherVector.capacity)];
    this->length = otherVector.length;
    this->capacity = otherVector.capacity;
    for(int i = 0; i < length; i++)
    {
        arr[i] = otherVector.arr[i];
    }
    return *this;

}

//concatenation
template<class T>
Vector<T>& Vector<T>::operator+=(T obj)
{
    this->add(obj);
    return *this;
}

#endif
