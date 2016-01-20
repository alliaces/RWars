//#include "AirEngine.h"
#include "MainMenu.h"
#include <thread>
#include <unistd.h>
#include <AirMusic.h>
#include <AirSound.h>

int main()
{
  AirWindow win("test",Vector2u(900,700));
  win.GetWindows().setActive(false);
  win.GetWindows().setFramerateLimit(60);
  win.SetScene(new MainMenu());
  IAirMusic *music = new AirMusic("ressource/Musique_traditionnelle_japonaise_quatuor.ogg");
  win.AddMusic(music);
  while (win.IsOpen())
    {
      win.Update();
    }
  win.RemoveMusic(music);
}
