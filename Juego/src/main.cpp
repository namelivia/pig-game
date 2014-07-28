#include "Combate.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{

	//Creamos el device, driver, tamaño de pantalla, etc
	IrrlichtDevice *device =
		createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, true);
	if (!device)
		return 1;

	//Inicializamos cosas
	IVideoDriver *driver = device->getVideoDriver();
	ISceneManager *smgr = device->getSceneManager();
	ITimer *timer = device->getTimer();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	// Precargamos las texturas
	driver->getTexture("media/ice0.jpg");
	driver->getTexture("media/rust0.jpg");

	// Creamos la escena principal
	Combate *unCombate = new Combate(device,driver,smgr,guienv);

	device->getCursorControl()->setVisible(0);
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 5.f;

	//Bucle principal
	u32 TimeStamp = timer->getTime(), DeltaTime = 0;
	while(device->run())
	{

		//Actualizamos el combate
		DeltaTime = timer->getTime() - TimeStamp;
		TimeStamp = timer->getTime();
		unCombate->actualizar(device,smgr,driver,DeltaTime);
		//Dibujamos la pantalla
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		//Calculamos e imprimimos los FPS
		if (lastFPS != fps)
		{
			core::stringw str = L"Juego del cerdo [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}

	}

	//Salimos
	device->drop();
	return 0;
}
