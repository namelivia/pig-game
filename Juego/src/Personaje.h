#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Personaje{
	bool estado;
	bool anteriorEstado;
	f32 velocidad;
	IAnimatedMeshSceneNode* auxNode;
	vector3df previousPosition;
  public:
    Personaje(ISceneManager *smgr,IVideoDriver *driver,IAnimatedMesh *mesh,ITexture *texture);
    ~Personaje();
	void actualizar();
	void acelera(bool direccion);
	void gira(bool direccion);
	void goBack();
	IAnimatedMeshSceneNode *getNode();
};
