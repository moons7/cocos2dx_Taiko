#ifndef  REIMU_GAMEDEFINE_H
#define REIMU_GAMEDEFINE_H

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#define  STATIC_CLASS_NAMBER(_className_) \
public:\
static inline  _className_* getInstance()  \
{  \
    if (nullptr == _instance)  \
            {  \
        _instance = new _className_();  \
        return _instance;  \
            } \
    return _instance; \
}; \
private:  \
static _className_* _instance; \
public:

#define  STATIC_NAMBER_INIT(_className_) _className_* _className_::_instance=nullptr
#endif