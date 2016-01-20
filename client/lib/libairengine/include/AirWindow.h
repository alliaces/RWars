#ifndef AIRWINDOW_H
#define AIRWINDOW_H

#include <SFML/Graphics.hpp>
#include "Vector2u.h"
#include "AirMusic.h"
#include "AirSound.h"

class AScene;

class AirWindow
{
    public:
        AirWindow(std::string title, const Vector2u& size);
        virtual ~AirWindow();
        void SetSize(const Vector2u& size);
        void SetTitle(const std::string &tilte);
        const std::string& GetTitle() const;
        Vector2u GetSize() const;
        sf::RenderWindow& GetWindows();
        void Update();
        bool IsOpen();
        void SetScene(AScene* scene);
        void AddMusic(IAirMusic *music);
        void RemoveMusic(IAirMusic *music);
        void PlaySoundA(IAirSound *sound);
	AScene* GetScene();
    protected:
        std::string _title;
        sf::RenderWindow _window;
        AScene* _scene;
        std::map<std::string, IAirMusic*> _musics;
        IAirSound *_sound;
    private:
};

#endif // AIRWINDOW_H
