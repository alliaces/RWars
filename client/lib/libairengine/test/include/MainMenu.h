#ifndef MAINMENU_H
#define MAINMENU_H

#include <AirEngine.h>

class MainMenu : public AScene, public OnClickListener
{
    public:
        MainMenu();
        virtual ~MainMenu();
        void OnInit();
        void OnRender();
        void OnResize(Vector2u wsize);
        void OnClick(void *);
    protected:
    private:
    	AirCheckBox *check;
};

#endif // MAINMENU_H
