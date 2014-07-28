#include <irrlicht.h>
#include "RealisticWater.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class Escenario{

    //ITerrainSceneNode *terrain;
	IAnimatedMesh *tatamiMesh;
	IMeshSceneNode *tatamiNode;
	RealisticWaterSceneNode *water;
	ISceneNode *skydome;
	ITriangleSelector *selector;
	float *heightVal;
	
  public:
    Escenario(ISceneManager *smgr,IVideoDriver *driver);
    ~Escenario();
	ITriangleSelector *getSelector();
};
