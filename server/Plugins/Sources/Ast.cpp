#include "Ast.h"

#ifdef __linux__
Ast	*Ast::instance;
#endif

Ast::Ast() : ABlock(15, true, 70, 70)
{
  this->addSprite(91);
  this->idGlobal_ = 11;
}

Ast::Ast(const Ast &tie) : ABlock(tie)
{}

Ast::~Ast()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new Ast());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new Ast());
	}
}
#endif
