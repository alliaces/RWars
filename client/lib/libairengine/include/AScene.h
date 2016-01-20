#ifndef ISCENE_H
#define ISCENE_H

#include "IEntity.h"
#include "Vector2u.h"
#include "AirParticuleGenerator.h"

class AScene
{
    public:
        virtual ~AScene() {}
        virtual void OnInit() = 0;
        virtual void OnRender() = 0;
        virtual void OnResize(Vector2u wsize) = 0;
        std::vector<IEntity*>& GetEntitys() {return _entity;}
	std::vector<AirParticuleGenerator*>& GetParticules() {return _particules;}
        void AddEntity(IEntity* e)
         {
            _entity.push_back(e);
         }

	void RemoveEntity(IEntity* e)
	{
        if (e && std::find(_entity.begin(), _entity.end(), e) != _entity.end()) 
	  _entity.erase(std::find(_entity.begin(), _entity.end(), e));
	}

	void RemoveParticules(AirParticuleGenerator* e)
	{
        if (e && std::find(_particules.begin(), _particules.end(), e) != _particules.end())
	        _particules.erase(std::find(_particules.begin(), _particules.end(), e));
	}

	void AddParticules(AirParticuleGenerator* e)
	{
	  _particules.push_back(e);
	}
    private:
        std::vector<IEntity*> _entity;
	std::vector<AirParticuleGenerator*> _particules;
};

#endif // ISCENE_H
