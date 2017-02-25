#include "Strvec.h"

#include <memory>

// copy constructor
Strvec::Strvec(const Strvec & s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    Strvec::elements = newdata.first;
    Strvec::first_free = Strvec::cap = newdata.second;
}

//Strvec Strvec::Strvec(Strvec && rhs)
//{
//}

// copy-assignment operator
Strvec & Strvec::operator=(const Strvec & rhs)
{
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    this->elements = newdata.first;
    this->first_free = this->cap = newdata.second;
    return *this;
}

//Strvec & operator=(Strvec && rhs)
//{
 //   this->free = rhs.free;
  //  this->elements = rhs.elements;
   // this->end = rhs.end;
    //rhs.free = rhs.elements = rhs.end = nullptr;
//}

void Strvec::push_back(const std::string & s)
{
    Strvec::chk_n_alloc();
    Strvec::alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *>
    Strvec::alloc_n_copy(std::string *b, std::string *e) 
{
    auto data = Strvec::alloc.allocate(e-b);
    return {data, std::uninitialized_copy(b, e, data)}; 
}

void Strvec::free()
{
    if(this->elements)
    {
        for (auto p = first_free; p != elements; )
            {
                Strvec::alloc.destroy(--p);
            }
        Strvec::alloc.deallocate(elements, cap - elements);
    }
}

void Strvec::reallocate()
{
    size_t ndata = Strvec::capacity() ? 1 : 2*Strvec::size();
    auto data = Strvec::alloc.allocate(ndata);
    auto start = data;
    auto dest = data;
    auto elem = elements;
    for (int i = 0; i != size(); i++)
    {  
        Strvec::alloc.construct(dest++, std::move(*elem++));
    }
    free();
    this->elements = start;
    this->first_free = dest;
    this->cap = start + ndata;
}