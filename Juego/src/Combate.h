#include <irrlicht.h>
#include <cstdlib>
#include "Escenario.h"
#include "Camara.h"
#include "Personaje.h"
#include "Vehicle.h"
#include "EventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Combate{

  public:
    Combate(IrrlichtDevice *device,IVideoDriver *driver,ISceneManager *smgr,IGUIEnvironment* guienv);
    ~Combate();
	void actualizar(IrrlichtDevice *device,ISceneManager *smgr,IVideoDriver *driver,u32 TDeltaTime);
	void CreateStartScene(IVideoDriver *driver,ISceneManager *smgr);
	void action(ISceneManager *smgr);

  private:
	Escenario *escenario;
	Personaje *cerdo;
	Vehicle *car;
	Vehicle *plane;
	Camara *camara;
	EventReceiver *receiver;
	int closeTo;
};
