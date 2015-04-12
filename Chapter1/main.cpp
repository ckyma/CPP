/* 
 * File:   main.cpp
 * Author: yuchen
 *
 * Created on January 10, 2015, 3:30 PM
 */

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <queue>
//#include <functional>

using namespace std;

/*
 * 
 */

class A
{
    int number;
public:
    A(int _number):number(_number)
    {
        cout<<"Normal constructor\n";
    }
    A()
    {
        cout<<"Default constructor\n";
    }

    A(const A& source)
    {
        number = source.number;
        cout<<"Copy constructor\n";
    }

    A & operator=(const A& source)
    {
        number = source.number;
        cout<<"Assignment operator\n";
        return *this;
    }
    
    // Optional
    ~A()
    {
        cout<<"Destructor\n";
    }
};

template<typename I>
void print (const I & start, const I & end)
{
    I it;
    for(it = start; it != end; ++it)
    {
        cout << *it << " ";
    }
    cout<<endl;
}

template<class C>
void print (const C & container)
{
    for(unsigned i = 0; i < container.size(); ++i)
    {
        cout<< container.at(i) << " ";
    }
    cout<<endl;
}

// Functor
struct DeleteOdd
{
    bool operator ()(int value)
    {
        if (value % 2 > 0 )
        {
            return true;
        }
        return false;
    }
};
// Function
bool deleteEven(int value)
{
    if (value % 2 == 0 )
    {
        return true;
    }
    return false;
}

bool compareInt(double v1, double v2)
{
    if ((int)v1 == (int)v2)
    {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    
    /*
     * 1.2 Sequential container, vector
     */
    // Caution, need the type <A>
    // vector v1(1);            // Compilation error, unknown type vector
    // vector v2(1, A(1));      // Compilation error, unknown type vector
    
    vector<A> v1(1);    //(1), the 1 here is the number of elements in the container, not an initial value, so the default constructor is called
    // Default constructor: ONLY the default constructor is called
    
    vector<A> v2(1, 1);
    // Normal constructor: int 1 to A, i.e., implicitly calls A(1)
    // Copy constructor
    // Destructor: for the new A(1)
    
    v1.push_back(2); //(2)
    // Normal constructor: int 1 to A, i.e., implicitly calls A(2)
    // Copy constructor: adjust length to 2, and copy two elements
    // Copy constructor
    // Destructor: for the one old array element due to the old array is destructed
    // Destructor: for the new A(2)
    
    v1[0]=10; 	   //(3)
    // Normal constructor: int 10 to A, i.e., A(10)
    // Assignment operator: assign object A(10)
    // Destructor: for the new A(10)
    
    /*
     * 1.3 Interator
     */
    //containers
    vector<int> v(10);
    deque<int> d(10);
    list<int> l(10);
    
    int i = 1;
    //vector
    vector<int>::iterator itV;
    // list<int>::iterator itV1 = v.begin();   // error: no viable conversion
    for(itV = v.begin()  ; itV != v.end(); ++itV,++i)
    {
        *itV = i;
    }
    for(itV = v.begin();  itV != v.end(); ++itV)
    {
        cout << *itV << " ";
    }
    cout<<endl;
    //deque
    deque<int>::iterator itD = d.begin();
    // vector<int>::iterator itD1 = d.begin();     // error: no viable conversion
    for(itD = d.begin()  ; itD != d.end(); ++itD,++i)
    {
        *itD = i;
    }
    for( itD = d.begin() ; itD != d.end(); ++itD)
    {
        cout << *itD << " ";
    }
    cout<<endl;
    
    list<int>::iterator itL = l.begin();
    // vector<int>::iterator itL1 = l.begin();  // error: no viable conversion
    for( ; itL != l.end(); ++itL,++i)
    {
        *itL = i;
    }
    // cout << l[0] << endl;   // error: type 'list<int>' does not provide a subscript operator
    for( itL = l.begin() ; itL != l.end(); ++itL)
    {
        cout << *itL << " ";
    }
    cout<<endl;
    
    /*
     * 1.4 Operations
     */
    // vector v2;   // error, unknown type vector
    print(v.begin(), v.end());
    // print<vector::iterator>(v.begin(), v.end());     // error: expected a class or namespace
    print<>(v.begin(), v.end());
    
    // use at()
    print(v);
    
    cout<<"Accessing out of range element:\n";
    cout<<v[10]<<" " <<d[10]<<endl;
    
    // Runtime exception: libc++abi.dylib: terminating with uncaught exception of type std::out_of_range: vector
    // cout<<v.at(11)<<endl;    // No compilation error
    
    try
    {
        cout<<v.at(11)<<endl;
    }
    catch (out_of_range & ex)
    {
        cout<< ex.what()<<endl;
    }
    
    list<int> lOdd(v.begin(), v.end());
    list<int> lEven(v.begin(), v.end());
    
    // Functor needs operator ()
    lEven.remove_if(DeleteOdd());
    // Function needs name ONLY
    // vEven.remove_if(deleteEven());  // error: no matching function for call to 'deleteEven'
    lOdd.remove_if(deleteEven);
    print(lOdd.begin(), lOdd.end());
    print(lEven.begin(), lEven.end());
    
    /*
     * 1.2 Sequential container
     */
    // Destructor: for the one element in v2
    // Destructor: for the two elements in v1
    // Destructor
    
    /*
     * 1.5 Container adapters
     */
    
    // Constructors
    int a1[]={1, 100, 34, 23, 9};
    //1. default constructor
    priority_queue<int>  s1;
    //2. copy constructor;
    priority_queue<int>  s2(s1);
    //3. initialization using iterators
    vector<int>  v51(a1, a1+10);
    priority_queue<int>  s3(v51.begin(), v51.end());
    //4. using nondefault storage
    priority_queue< int, deque <int> > s4;
    //5. Providing different comparator type
    priority_queue< int, vector<int>, greater <int> > s5;
    
    // Operations
    priority_queue<int>  q1(a1, a1+5);
    priority_queue< int, deque<int>, greater <int> > q2(a1, a1+5);
    cout<< "q1 queue top: " << q1.top()<<endl;
    cout<< "q2 queue top: " << q2.top()<<endl;
    cout<<"Adding value: 101\n";
    q1.push(101);
    q2.push(101);
    cout<< "q1 queue top: " << q1.top()<<endl;
    cout<< "q2 queue top: " << q2.top()<<endl;
    cout<<"Removing top of the queue: \n";
    q1.pop();
    q2.pop();
    cout<< "q1 queue top: " << q1.top()<<endl;
    cout<< "q2 queue top: " << q2.top()<<endl;
    
    return 0;
}

