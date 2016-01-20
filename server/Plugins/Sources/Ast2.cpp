#include "Ast2.h"

#ifdef __linux__
Ast2	*Ast2::instance;
#endif

Ast2::Ast2() : ABlock(15, true, 20, 20)
{
  this->addSprite(91);
  this->idGlobal_ = 13;
}

Ast2::Ast2(const Ast2 &tie) : ABlock(tie)
{}

Ast2::~Ast2()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Ast2());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Ast2());
	}
}
#endif
