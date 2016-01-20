#ifndef SCENEMEDIATOR_H
#define SCENEMEDIATOR_H

#include <map>
#include <AirEngine.h>
#include "ResourceMediator.h"

class Ui;

class SceneMediator
{
public:
	SceneMediator(Ui *ui, AirWindow *window, ResourceMediator *resourceMediator);
	~SceneMediator();
	AScene *getSceneByName(const std::string &name);
private:
	std::map<std::string, AScene*> scenes_;
	ResourceMediator *resourceMediator_;
};

#endif // SCENEMEDIATOR_H
