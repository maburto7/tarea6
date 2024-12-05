#ifndef ICS_VECTOR_HPP
#define ICS_VECTOR_HPP

/*
We are giving you guiding comments to help you fill out this header file.
The indentation of the comments serve as hints to how your code is structured. 

These are HINTS. PLEASE READ THE README.
Anything not specified here will be in the README.
For example, some functions may be const versions while others may not.
Some functions may throw exceptions while others are noexcept.
*/

/* Preprocessor directives. Guard the header file upon include */
#include <ostream>
#include <vector_exception.hpp>

/*
Which include directives should you put here?
(hint: we may throw VectorExceptions. We also want to use ostream)
*/

template <typename T>
/*
Templated Vector class definition with templated Iterator class member
The template type name can be T
*/
class Vector{
    /* Begin by specifying private members of Vector */
    private:
        size_t capacity;
        size_t m_size;
        T* buffer;

        /* We want to nest the Iterator class definition right here */

            /* Write out the private members of Iterator */

        /* there should be an m_container and an index */

        class Iterator{

            
            friend Iterator operator+(size_t offset, const Iterator &iter){
                Iterator temp = iter;
                //temp.index += offset;
                if (temp.index + offset > temp.m_container.size()) { throw VectorException("out of bounds on vector");}
                
                temp.index = temp.index + offset;
                return temp;
            }


            friend Iterator operator+(const Iterator &iter, size_t offset) {
                Iterator temp = iter;
                if (temp.index + offset > temp.m_container.size()) { throw VectorException("out of bounds on vector");}
                
                temp.index = temp.index + offset;
                return temp;
        }


            private:
                Vector<T>& m_container; //reference of a vector of type T is stored in variable
                size_t index;

            public:
        
    /* Here are our your public members of Iterator*/


        /* Write your constructors here */
                Iterator(Vector<T>& m_container , size_t index) //vectors take a container and an index only
                : m_container(m_container), index(index) {} //assign the values  to the private attributes of class vector


                //big 5
                //deepcopy iterator
                Iterator(const Iterator& other) noexcept: m_container(other.m_container), index(other.index) {}

                //copy assignment operator
                Iterator& operator=(const Iterator& other) noexcept {
                    if (this != &other) {
                        m_container = other.m_container;
                        index = other.index;
                    }
                    return *this;
                }

                //move assignment operator
                Iterator& operator=(Iterator&& other) noexcept {
                    if (this != &other) {
                        m_container = other.m_container;
                        index = other.index;
                        other.index = 0; 

                    }
                    return *this;
                }


        /* Write your operator overloads here.*/
                

        /* Post and pre increment and decrement operators*/

                Iterator & operator++(){ //by reference
                    if (index >= m_container.size()){throw VectorException("out of bounds");}
                    
                    ++index;

                    return *this;
                }

                Iterator operator++(int){
                    if (index > m_container.size()){throw VectorException("out of bounds"); }
                    
                    Iterator temp = *this; //make copy because it is post increment
                    ++index;
                    return temp;
                }

                Iterator & operator--(){ //by reference
                    if (index <=0){throw VectorException("out of bounds");}
                    --index;
                    return *this;
                    }

                //post incrementor
                Iterator operator--(int){
                    if (index <=0){throw VectorException("out of bounds");}
                    
                    Iterator temp = *this;
                    --index;
                    return temp;
                     }


        /* Overloaded += size_t operator */

                Iterator & operator+=(size_t offset){
                    if((index + offset) >= m_container.size()){throw VectorException("out of bounds");}
                    index += offset;
                    //index += offset;
                    return *this;
                                    }

        /* Overloaded -= size_t operator */

                Iterator & operator-=(size_t offset){
                    if (index < offset) { throw VectorException("out of bounds");}
                    index -= offset;
                    return *this;
                                    }


        /* Overloaded - operator. The right hand side is a const Iterator& */
                size_t operator-(const Iterator & second) const{
                    if (m_container == second.m_container && index == second.index){
                        return index - second.index;
                    } 
                    throw VectorException("iterators point to different containers");}
                    
                    

        /* Overloaded - operator.  The right hand side is a size_t */
                Iterator operator-(size_t offset) const{
                    
                    if (index < offset) { throw VectorException("out of bounds");}
                    Iterator temp = *this;
                    temp.index = index - offset;
                    return temp;
                }
    

        /* Overloaded == operator. The right hand side is a const Iterator& */

                bool operator==(const Iterator& second) const noexcept{
                // Ensure they are from the same container and point to the same index
                if (m_container == second.m_container && index == second.index){
                    return true;
                } 
                return false;
                
        }


        /* Overloaded != operator. The right hand side is const Iterator& */
                bool operator!=(const Iterator& second) const noexcept{
                    if (m_container != second.m_container || index != second.index){
                        return true;
                    }
                    return false;
              
        }


        /* Overloaded star (*) operator to dereference. This returns a T& */
                T & operator*() const{
                    if (index >= m_container.size()){
                        throw VectorException("out of bounds");
                        }

                    return m_container.buffer[index];
                }


        /* Overloaded -> operator. This returns a T* */
                T * operator->() const{
                    if (index == m_container.size()){throw VectorException("out of bounds");}
                    
                    return &m_container.buffer[index];
                }

        /*
        It is correct to add a size_t to an Iterator.
        What keyword should you use to specify these next two overloads? (It's in the README)
        Remember, using + on Iterators is commutative.
        1 + Iterator and Iterator + 1 both return an Iterator that is one forward.
        */
        };

    /* Specify your private Vector member fields. There should be three */
    public:
/* You will define your public Vector members here*/

    /* Default constructor */
        Vector() : capacity(0), m_size(0), buffer(nullptr){}


    /* An overloaded constructor (see README) */
        Vector(size_t capacity): capacity(capacity), buffer(capacity){}


        Vector& operator=(Vector& other) noexcept {
            if (this != &other) {
                if (capacity != other.capacity){
                delete[] buffer; //deallocate buffer

                //recreate vector
                buffer = new T[capacity];

                for (size_t i = 0; i < m_size; ++i) { //copying every value
                    buffer[i] = other.buffer[i];
                }

                //buffer = other.buffer;
                capacity = other.capacity;
                m_size = other.m_size;

            }}
        return *this;
    }

        //move semantics
        Vector(Vector&& other) noexcept{
        
            buffer = other.buffer;
            capacity = other.capacity;
            m_size = other.m_size;

            other.buffer = nullptr;
            other.capacity = 0;
            other.m_size = 0;
            
        }


    /* The begin() function */
        Iterator begin() noexcept{

            return Iterator(*this, 0);
        }


    /* The const version of begin(). Note: it returns a const T* type */
        T const * begin() const noexcept{
            if (m_size == 0) {
                //return end();
                return nullptr;
                }
            
            return &buffer[0];
        }

    /* The empty() function */
        bool empty() const noexcept{
            return m_size == 0;
        }
        

    /* The end() function */
        Iterator end() noexcept{
            return Iterator(*this, m_size);
        }



    /* The const version of end(). Note: it returns a const T* */
        T const * end() const noexcept{
            if (m_size == 0) {return nullptr; }
            return &buffer[m_size];
        }

    //m_size
        size_t size() const noexcept{
            return m_size;
        }


    /* The front() function */
        T & front() noexcept{
            if(empty()){throw VectorException("front empty");}
            return buffer[0];
        }

    /* The const version of front(). Note it returns a const T& this is different from begin()! */

        T const & front() const noexcept{
            if(empty()){throw VectorException("front empty");}
            return buffer[0];
        }

    /* The back() function */




    /* The const version of back(). Note: it returns a const T& */




    /* The push_back() function */

        void push_back(const T& item) {
            // If size is 0, set capacity to 1
            if (m_size == 0) {
                capacity = 1;
                buffer = new T[capacity]; 
            } else if (m_size == capacity) {
                resize(capacity * 2); 
            }

            buffer[m_size] = item; 
            ++m_size; 
        }

 
    /* The push_back function that takes an RValue reference (Type of T&&) */









    /* The pop_back() function*/








    /* The capacity() function */


    /* The m_size() function */


    /* The data() function. Returns type T* */


    /* The const version of data(). Returns type const T* */


    /* 
    The erase function. It takes in a start and end Iterator.
    Once again, it is end-exclusive
    Hints for implementation:
        0 1 2 3 4 5
    We want to delete 1 2 3: start points to 1 and end points to 4
        0    1    2    3    4    5
             ^start         ^end
    Replace what is at start with what is at end and advance start and end until it reaches the vec.end()
        0    4    2    3    4    5
                  ^s             ^e
        0    4    5    3    4    5
                       ^s            e=vec.end()
    Is anything after what s is now including s used?
    Hint: resize the vector to include only 0 4 5. You will implement resize anyways.
    */












    /* swap_elements(). Takes two iterators. Use std::move ! */






    /* Subscript operator[] overload */


    /* Const version of the subscript operator[] overload */


    /* 
    Overloaded == operator. The right hand side is another const<T>& vector.
    Make sure the sizes of the vectors are equal
    Also check the elements inside are equal.
    */
    bool operator==(const Vector & other) const noexcept{
        if(m_size == other.m_size){
            int m = m_size;
            for(int i=0;i<m;i++){
                if(buffer[i] != other.buffer[i]){
                    return false;
                }
            }
            return true;
        }
        return false;
    }




    /* Overloaded != operator. */
    bool operator!=(const Vector &other) const noexcept{
        if(m_size!= other.size()){
            return true;
        }
        return false;
    }

    /* Vector copy constructor. Does a deep copy! */
    Vector(const Vector& other){
        size_t capacity, m_size;
        capacity = other.capacity;
        m_size  = other.m_size;
        
        buffer = new T[capacity];

        for (size_t i = 0; i < m_size; ++i) { //copying every value
            buffer[i] = other.buffer[i];
        }
    }



    /* 
    Vector assignment operator.
    Make sure you don't leak memory here. 
    */









    /* at() function. */









    /* const version of at() */









    /* 
    operator<< 
    We want to write code that can write Vectors to an output stream
    like std::cout << v << std::endl;
    You should use the friend keyword somewhere in here. 
    */






    /*
    Vector resize() function here.
    Allocate a new buffer to move all the old elements from the old one to.
    And then assign that new buffer to the `this`
    Make sure to use std::move() to move data from the old buffer to the new one.
    Make sure you don't leak memory!
    */
    void resize(size_t new_capacity) {
        // Allocate a new buffer
        T* new_buffer = new T[new_capacity];

        //this = new_buffer;
        
        // Copy existing elements to the new buffer
        for (size_t i = 0; i < m_size; ++i) {
            new_buffer[i] = std::move(buffer[i]);
        }
        
        delete[] buffer;
        buffer = new_buffer;
        capacity = new_capacity;
    }





















    /*
    clear() function. Make sure the destructor of each element gets called.
    delete[] will automatically do this. 
    But there other ways of implementing this function.
    */






    /* Move constructor here */







    /* 
    Move assignment here
    Make sure there are not memory leaks!
    */
    
    /* The Vector destructor goes here. Make sure there are no leaks */
    ~Vector(){
        delete [] buffer;
    }

/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/


};
#endif


