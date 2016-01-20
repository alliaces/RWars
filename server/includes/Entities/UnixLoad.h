#pragma once

#include <stdexcept>
#include <dlfcn.h>

template <class T>
class ULoad
{
public:
  ULoad()
  {
    isClose = false;
  }
  
  ~ULoad()
  {
  }

  T	*load(const char *path)
  {
    open(path);
    return (creator());
  }

  void *open(const char *path)
  {
    if ((this->inst = dlopen(path, RTLD_NOW | RTLD_GLOBAL)) == NULL)
	throw std::runtime_error(dlerror());
    return (this->inst);
  }

  T	*creator()
  {
    if ((this->create = reinterpret_cast<T *(*)()>(dlsym(this->inst, "create_instance"))) == NULL)
      throw std::runtime_error(dlerror());
    this->objet = this->create();
    return (this->objet);
  }

  void	close()
  {
    if (isClose)
      return;
    isClose = true;
    if (dlclose(this->inst) != 0)
      throw std::runtime_error(dlerror());
  }

  T	*getObjet()
  {
    return (this->objet);
  }

private:
  bool isClose;
  T *(*create)();
  T *objet;
  void *inst;
};
