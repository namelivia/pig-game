#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Camara{
    ICameraSceneNode *camara;
    IAnimatedMeshSceneNode *playerNode;
	float direction;
	float zdirection;
  public:
    Camara(ISceneManager *smgr,IAnimatedMeshSceneNode *player);
    ~Camara();
	ICameraSceneNode *getNode();
	void moveCameraControl(IrrlichtDevice *device);
};
