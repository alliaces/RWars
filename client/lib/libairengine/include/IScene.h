#ifndef ISCENE_H
#define ISCENE_H



class AScene
{
    public:
        virtual ~AScene();
        virtual void OnInit() = 0;
        virtual void OnRender() = 0;
        virtual void OnResize(Vector2u wsize) = 0;
        std::vector<IEntity*>& GetEntitys() {return entity;}
    protected:
    private:
        std::vector<IEntity*> entity;
};

#endif // ISCENE_H
