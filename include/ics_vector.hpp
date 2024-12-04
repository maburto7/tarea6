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
        size_t size;
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

        
        /* Write your operator overloads here.*/
                

        /* Post and pre increment and decrement operators*/

                Iterator & operator++(){ //by reference
                    if (index >= m_container.size()){throw VectorException("out of bounds");}
                    
                    ++index;
                    return *this;
                }

                Iterator operator++(){
                    if (index >= m_container.size()){throw VectorException("out of bounds"); }
                    
                    Iterator temp = *this; //make copy because it is post increment
                    ++index;
                    return temp;
                }

                Iterator & operator--(){ //by reference
                    if (index < m_container.size()|| index ==0){throw VectorException("out of bounds");}
                    --index;
                    return *this;
                    }

                
                Iterator operator--(){
                    if (index < m_container.size() || index ==0){throw VectorException("out of bounds");}
                    
                    Iterator temp = *this;
                    --index;
                    return temp;
                        }


        /* Overloaded += size_t operator */

                Iterator & operator+=(size_t offset) const{
                    if((index + offset) > m_container.size()){throw VectorException("out of bounds");}
                    Iterator temp = *this;
                    temp.index += offset;
                    //index += offset;
                    return *this;
                                    }

        /* Overloaded -= size_t operator */

                Iterator & operator-=(size_t offset) const{
                    if((index - offset) <= 0){throw VectorException("out of bounds");}

                    Iterator temp = *this;
                    temp.index -= offset;
                    //index -= offset;
                    return *this;
                                    }


        /* Overloaded - operator. The right hand side is a const Iterator& */
                size_t operator-(const Iterator & second) const{
                    if (m_container == second.m_container){
                        return index - second.index;
                    } else{
                        throw VectorException("iterators point to different containers");
                    }
                }

        /* Overloaded - operator.  The right hand side is a size_t */
                Iterator operator-(size_t offset) const{
                 if((index - offset) <= 0){throw VectorException("out of bounds");}

                Iterator temp = *this;
                temp.index = index - offset;
                return temp;
                }
    

        /* Overloaded == operator. The right hand side is a const Iterator& */

                bool operator==(const Iterator& second) const noexcept{
                // Ensure they are from the same container and point to the same index
                if (m_container == second.m_container && index == second.m_container){
                    return true;
                
                } else{
                    return false;
                }
        }


        /* Overloaded != operator. The right hand side is const Iterator& */
                bool operator!=(const Iterator& second) const noexcept{
                    
                if (m_container != second.m_container || index != second.m_container){
                    return true;
                
                }
                return false;
                
        }


        /* Overloaded star (*) operator to dereference. This returns a T& */
                T & operator*() const{
                    if (index == m_container.size()){
                        throw VectorException("out of bounds");
                        }

                    return m_container.buffer[index];
                }


        /* Overloaded -> operator. This returns a T* */
                T & operator->() const{
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
        Vector() : capacity(0), size(0), buffer(nullptr){}


    /* An overloaded constructor (see README) */
        Vector(size_t capacity): capacity(capacity), buffer(capacity){}


    /* The begin() function */
        Iterator begin() noexcept{
            return Iterator(*this, 0)
        }


    /* The const version of begin(). Note: it returns a const T* type */
        T const * begin(){
            if (size == 0) {return nullptr; }
            
            return const Iterator(*this, 0);
        }

    /* The empty() function */
    bool empty() const noexcept{
        size == 0 ? true: false;
    }
        

    /* The end() function */
        Iterator end() noexcept{
            return Iterator(*this, size);
        }



    /* The const version of end(). Note: it returns a const T* */
        T const * end() const noexcept{
            if (size == 0) {return nullptr; }
            return const Iterator(*this, size);
        }



    /* The front() function */




    /* The const version of front(). Note it returns a const T& this is different from begin()! */




    /* The back() function */




    /* The const version of back(). Note: it returns a const T& */




    /* The push_back() function */









    /* The push_back function that takes an RValue reference (Type of T&&) */









    /* The pop_back() function*/








    /* The capacity() function */


    /* The size() function */


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











    /* Overloaded != operator. */


    /* Vector copy constructor. Does a deep copy! */







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


};






    
    /* The Vector destructor goes here. Make sure there are no leaks */
    ~Vector(){
        delete [] buffer;
    }

/* 
And we are finished with this header file! 
If you used an #ifndef #define, what should you add at the very end?
*/
