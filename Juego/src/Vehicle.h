#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Vehicle{
	bool estado;
	bool anteriorEstado;
	f32 velocidad;
	IAnimatedMeshSceneNode* auxNode;
  public:
    Vehicle(ISceneManager *smgr,IVideoDriver *driver,IAnimatedMesh *mesh,ITexture *texture);
    ~Vehicle();
	void actualizar();
	void acelera(bool direccion);
	void gira(bool direccion);
	IAnimatedMeshSceneNode *getNode();
};
