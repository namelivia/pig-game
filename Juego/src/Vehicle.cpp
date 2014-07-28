#include <irrlicht.h>
#include "Vehicle.h"

//Inicializamos parámetros iniciales
Vehicle::Vehicle(ISceneManager *smgr,IVideoDriver *driver,IAnimatedMesh *mesh, ITexture *texture){
	estado=false;
	anteriorEstado=false;
	velocidad = 0.0f;

	//Añadimos el nodo
	vector3df TScale = vector3df(1.0f, 1.0f, 1.0f);
	auxNode = smgr->addAnimatedMeshSceneNode(mesh);
	
	auxNode->setScale(TScale);
	auxNode->setPosition(vector3df(100.f,30.f,0.f));
	auxNode->setMaterialFlag(EMF_LIGHTING, true);
	auxNode->setMaterialTexture(0,texture);
	auxNode->setFrameLoop(251,500);
}

Vehicle::~Vehicle(){
}

//Actualizamos al personaje
void Vehicle::actualizar(){

	anteriorEstado=estado;
	
	if (velocidad>0.0f) {velocidad -= .05f;
						 estado = true;}

	else estado=false;

	if (anteriorEstado!=estado) {
		if (estado) getNode()->setFrameLoop(251,500);
		else getNode()->setFrameLoop(0,250);
	}

	vector3df direccion = getNode()->getRotation().rotationToDirection();
	getNode()->setPosition(getNode()->getPosition()+(direccion*velocidad));
}

void Vehicle::acelera(bool direccion){
	velocidad = 1.f;
}
void Vehicle::gira(bool direccion){
	if (!direccion){
		getNode()->setRotation(getNode()->getRotation()+vector3df(0.0f,1.0f,0.0f));
	} else {
		getNode()->setRotation(getNode()->getRotation()-vector3df(0.0f,1.0f,0.0f));
	}
}

IAnimatedMeshSceneNode *Vehicle::getNode(){
	return auxNode;
}
