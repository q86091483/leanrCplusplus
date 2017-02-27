#ifndef _STRVEC_
#define _STRVEC_

#include <string>

class Strvec
{
    public:
        // default constructor
        Strvec():
        elements(nullptr), first_free(nullptr), cap(nullptr){}
        // copy constructor
        Strvec(const Strvec &);
        // move constructor
        Strvec(Strvec &&) noexcept;
        // copy-assignment operator 
        Strvec & operator=(const Strvec &);
        // move-assignment operator 
        Strvec & operator=(Strvec &&);
        // destructor
        ~Strvec(){free();};
        void push_back(const std::string &);
        void push_back(std::string &&);
        // void push_back(std::string &&);
        size_t size(){return first_free - elements;}
        size_t capacity(){return cap - elements;}
        std::string *begin() const{return elements;} 
        std::string *end() const{return cap;}
    private:
        std::string *elements;
        std::string *first_free;
        std::string *cap;
        std::allocator<std::string> alloc; 
        std::pair<std::string *, std::string *>
            alloc_n_copy(std::string *, std::string *);
        void chk_n_alloc(){if(capacity() == size()) reallocate();};
        void free();
        void reallocate();
};

#endif