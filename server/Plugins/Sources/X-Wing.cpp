#include "X-Wing.h"

#ifdef __linux__
XWing     *XWing::instance;
#endif

XWing::XWing() : APlayer(100, 5, 95, 20, "x-wing")
{
  this->addSprite(6);
  this->idGlobal_ = 7;
  this->shotEntity_ = 4;
}

XWing::XWing(const XWing &xwing) : APlayer(xwing)
{}

XWing::~XWing()
{}

#ifdef __linux__
extern "C"
{
  AEntity *create_instance()
  {
    return (new XWing());
  }
}
#elif _WIN32
extern "C"
{
	__declspec(dllexport) AEntity *create_instance()
	{
		return (new XWing());
	}
}
#endif
