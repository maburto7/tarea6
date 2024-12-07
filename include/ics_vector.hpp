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
#include <iosfwd>
#include <vector_exception.hpp>

/*
Which include directives should you put here?
(hint: we may throw VectorExceptions. We also want to use ostream)
*/


/*
Templated Vector class definition with templated Iterator class member
The template type name can be T
*/
template <typename T> class Vector{
    /* Begin by specifying private members of Vector */
    private:
        size_t m_capacity;
        size_t m_size;
        T* buffer;

        /* We want to nest the Iterator class definition right here */

            /* Write out the private members of Iterator */

        /* there should be an m_container and an index */

        class Iterator{

            private:
                Vector<T>& m_container; //reference of a vector of type T is stored in variable
                size_t index;

            public:
        
    /* Here are our your public members of Iterator*/


        /* Write your constructors here */
                Iterator(Vector<T>& m_container , size_t index) //vectors take a container and an index only
                : m_container(m_container), index(index) {} //assign the values  to the private attributes of class vector


                //big 5
                //deepcopy iterator constructor
                Iterator(const Iterator& other) noexcept: m_container(other.m_container), index(other.index) {}

                //copy assignment operator
                Iterator& operator=(const Iterator& other) noexcept {
                    if (this != &other) {
                        m_container = other.m_container;
                        index = other.index;
                    }
                    return *this;
                }
                //move constructor
                Iterator(Iterator&&other) noexcept: m_container(other.m_container),index(other.index){other.index =0;}

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
                    if (&m_container != &second.m_container){
                        throw VectorException("iterators point to different containers");}
                    return index - second.index;
                }
                    
                    

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
                    return &m_container == &second.m_container && index == second.index;}
                
                
        /* Overloaded != operator. The right hand side is const Iterator& */
                bool operator!=(const Iterator& second) const noexcept{
                    return m_container != second.m_container || index != second.index;}


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

                friend Iterator operator+(size_t offset, const Iterator &iter){
                    Iterator temp = iter;
                    //temp.index += offset;
                    //if (temp.index + offset > temp.m_container.size()) { throw VectorException("out of bounds on vector");}
                    for(size_t i=0; i<offset;i++ ){
                        ++temp;
                    }
                    //temp.index = temp.index + offset;
                    return temp;
            }


                friend Iterator operator+(const Iterator &iter, size_t offset) {
                    Iterator temp = iter;
                    //if (temp.index + offset > temp.m_container.size()) { throw VectorException("out of bounds on vector");}
                    //temp.index = temp.index + offset;

                    for(size_t i=0; i<offset;i++){
                        ++temp;
                    }
                    return temp;
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
        Vector() : m_capacity(0), m_size(0), buffer(nullptr){}


    /* An overloaded constructor (see README) */
        Vector(size_t m_capacity): m_capacity(m_capacity), m_size(0),buffer(nullptr){
            buffer = new T[m_capacity];
        }


        /* Vector copy constructor. Does a deep copy! */
        Vector(const Vector& other) noexcept
            : m_capacity(other.capacity()), m_size(other.size()), buffer(new T[other.capacity()]) {
            for (size_t i = 0; i < m_size; ++i) {
                buffer[i] = other.buffer[i];
            }
        }

        //copy assignment operator
        Vector& operator=(const Vector &other) {
            if (this != &other){
                delete [] buffer;
                m_capacity = other.capacity();
                m_size = other.size();
                T* temp = new T[other.capacity()];
                for (size_t i = 0; i < size(); ++i){
                    temp[i] = other.buffer[i];
                }
                buffer = temp;
            }
            
        return *this;

            } 
        
     
        //move semantics constructo
        Vector(Vector&& other) noexcept :m_capacity(other.capacity()),m_size(other.size()),buffer(other.buffer){
            other.buffer = nullptr;
            other.m_capacity = 0;
            other.m_size = 0;

        }
            
        //move assignment operator
        Vector& operator=(Vector&& other) noexcept{
            if(this!=&other){
                delete[] buffer;

                buffer = other.buffer;
                m_capacity = other.m_capacity;
                m_size = other.m_size;
                

                other.buffer = nullptr;
                other.m_capacity = 0;
                other.m_size = 0;
                    
            }
            return *this;
        }


          bool operator==(const Vector& other) const noexcept {
            //]if (this == &other) {
            //    return true;
            //}
            if (this == &other) {
                return true;
            }

            if (m_size == other.size()) {
                for (size_t i = 0; i < size(); ++i) {
                    if (buffer[i] != other.buffer[i]) {
                        return false;
                    }
                }return true;
                }
                return false;
            
        }

        
        /* Overloaded != operator. */
        bool operator!=(const Vector &other) const noexcept{
            //if(this != &other){
            //    return true;}
            
            //return false;
            return !(*this == other);
        }
        

    /* The begin() function */
        Iterator begin() noexcept{return Iterator(*this, 0);}


    /* The const version of begin(). Note: it returns a const T* type */
        T const * begin() const noexcept{
            if (m_size == 0) {return nullptr;}

            return &buffer[0];
        }

    /* The empty() function */
        bool empty() const noexcept{return m_size == 0;}
        

    /* The end() function */
        Iterator end() noexcept{ return Iterator(*this, m_size);}


    /* The const version of end(). Note: it returns a const T* */
        T const * end() const noexcept{if (m_size == 0) {return nullptr; }
            
            return &buffer[m_size];
        }

    //m_size
        size_t size() const noexcept{return m_size;}


    /* The front() function */
        T & front() noexcept{return buffer[0];}

    /* The const version of front(). Note it returns a const T& this is different from begin()! */

        T const & front() const noexcept{return buffer[0];}

    /* The back() function */
        T & back() noexcept{return buffer[m_size-1];}

    /* The const version of back(). Note: it returns a const T& */

        T const & back() const noexcept{return buffer[m_size-1];}


    /* The push_back() function */

        void push_back(const T& item){
            
            if (size() == capacity()) {resize(m_capacity == 0 ? 1 : m_capacity * 2); }
            buffer[size()] = item; 
            ++m_size; 
        }

    /* The push_back function that takes an RValue reference (Type of T&&) */
        void push_back(T&& item){
            // If size is 0, set m_capacity to 1
            
            if (size() == capacity()) {
                if (size() == capacity()) {resize(m_capacity == 0 ? 1 : m_capacity * 2); }
                }

            buffer[size()] = std::move(item);
            ++m_size; 
        }


    /* The pop_back() function*/
        void pop_back(){
            if(empty()){
                throw VectorException("popping from empty");
            } else{
                buffer[m_size-1].~T();
                --m_size;
            }
        }


    /* The m_capacity() function */
        size_t capacity() const noexcept{return m_capacity;}

 
        /* The data() function. Returns type T* */
        T * data() noexcept{ return buffer;}


        /* The const version of data(). Returns type const T* */
        T const * data() const noexcept{return buffer;}

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


        void erase(Iterator start, Iterator end){
            if(start==end){return;}

            std::size_t offsetDelete = end - start; 
            Iterator m_start = start;
            Iterator m_end = end;
            //while(m_end != *this->end()){
            //      Iterator tmp = m_start;
            //      m_start = std::move(m_end);
            //      m_end = std::move(tmp)
            //      ++m_end;
            //      ++m_start;
            //}
            while(m_end != this->end()){
                swap_elements(m_start, m_end);
                ++m_end;
                ++m_start;
            }

            //size - offsetDelete = begin
            
            resize(size() - offsetDelete);

    }
        

    /* swap_elements(). Takes two iterators. Use std::move ! */
        void swap_elements(Iterator lhs, Iterator rhs) noexcept {
            T temp = std::move(*lhs);
            *lhs = std::move(*rhs);
            *rhs = std::move(temp);
        }

    /* Subscript operator[] overload */


    /* Const version of the subscript operator[] overload */
        T & operator[](size_t index) noexcept{return buffer[index];}
        
        T const & operator[](size_t index) const noexcept{return buffer[index]; }

    /* 
    Overloaded == operator. The right hand side is another const<T>& vector.
    Make sure the sizes of the vectors are equal
    Also check the elements inside are equal.
    */
      
        
    /* 
    Vector assignment operator.
    Make sure you don't leak memory here. 
    */

 
    /* at() function. */
        T & at(size_t index){
            if((index >= m_size) || index < 0 ){throw VectorException("out of bounds");}

            return buffer[index];
        }


    /* const version of at() */
        T const & at(size_t index) const{
            if((index >= m_size) || index < 0){throw VectorException("out of bounds");}

            return buffer[index];
        }

//if(empty()){throw VectorException("front empty");}

    /* 
    operator<< 
    We want to write code that can write Vectors to an output stream
    like std::cout << v << std::endl;
    You should use the friend keyword somewhere in here. 
    */
        friend std::ostream& operator<<(std::ostream& out, const Vector& vec){
            for (size_t i = 0; i < v.size(); ++i){
                out << vec.at(i) << " "; 
            }
            return out;
    }

    /*
    Vector resize() function here.
    Allocate a new buffer to move all the old elements from the old one to.
    And then assign that new buffer to the `this`
    Make sure to use std::move() to move data from the old buffer to the new one.
    Make sure you don't leak memory!
    */
        void resize(size_t new_capacity) {
            // Allocate a new buffer
            if(new_capacity == m_capacity){return;}
            
            T* new_buffer = new T[new_capacity];

            if(m_size< new_capacity){
                for (size_t i = 0; i < m_size; ++i) {
                    new_buffer[i] = std::move(buffer[i]);}

            } else{
                for (size_t i = 0; i < new_capacity; ++i) {
                    new_buffer[i] = std::move(buffer[i]);
                }
                m_size = new_capacity;
            }

            delete[] buffer;
            buffer = new_buffer;
            m_capacity = new_capacity;
        

            /*
            if(new_capacity >= m_size){
                for (size_t i = 0; i < new_capacity; ++i) {
                    new_buffer[i] = std::move(buffer[i]);}
                m_size = new_capacity;

            }else{
                for (size_t i = 0; i < m_size; ++i) {
                    new_buffer[i] = std::move(buffer[i]);
                }
            }
            */
            
            
        }



    /*
    clear() function. Make sure the destructor of each element gets called.
    delete[] will automatically do this. 
    But there other ways of implementing this function.
    */

        void clear() noexcept {
            for (size_t i = 0; i < size(); ++i) { //destructing every value
                buffer[i].~T(); }
        
            m_size = 0;
        }


    /* Move constructor here */


    /* 
    Move assignment here
    Make sure there are not memory leaks!
    */
    
    /* The Vector destructor goes here. Make sure there are no leaks */
        ~Vector(){
            clear();
            delete [] buffer;
        }

/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/

};
#endif


