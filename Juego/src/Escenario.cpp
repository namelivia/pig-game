#include <irrlicht.h>
#include "Escenario.h"

Escenario::Escenario(ISceneManager *smgr,IVideoDriver *driver){

	//TATAMI (MODELO 3D)
	//===================

	tatamiMesh = smgr->getMesh("media/isla.obj");
	tatamiNode = smgr->addMeshSceneNode(tatamiMesh);

	if (tatamiNode)
	{
		tatamiNode->setMaterialFlag(EMF_LIGHTING, true);
		tatamiNode->setMaterialTexture( 0, driver->getTexture("media/isla.png") );
	}


//Creamos selector para el terreno, que utilizaremos para las colisiones
	selector = smgr->createTriangleSelector(tatamiMesh, 0);
	tatamiNode->setTriangleSelector(selector);

//Ponemos el agua
	water = new RealisticWaterSceneNode(
      smgr, 20480, 20480, driver->getTexture("media/waterbump.png"),
      dimension2du(1024, 1024), smgr->getRootSceneNode(), 666);
	if(water)
      {
         water->setWindForce(5.5f);
         water->setPosition(vector3df(0.0f,-28.0f,0.0f));
      }

//Ponemos el cielo
	skydome = smgr->addSkyDomeSceneNode(driver->getTexture("media/skydome.jpg"),16,8,0.95f,2.0f);

//Ponemos luz de ambiente
smgr->setAmbientLight(video::SColorf(1,1,0.8,1));
//driver->setFog(SColor(0,138,125,81), EFT_FOG_LINEAR, 250, 1000, .003f, true, false);

}

Escenario::~Escenario(){
}

ITriangleSelector *Escenario::getSelector(){
	return selector;
}
