#include <irrlicht.h>
#include "Personaje.h"

//Inicializamos parámetros iniciales
Personaje::Personaje(ISceneManager *smgr,IVideoDriver *driver,IAnimatedMesh *mesh,ITexture *texture,f32 whatMaxSpeed){
	estado=false;
	anteriorEstado=false;
	velocidad = 0.0f;
	maxSpeed = whatMaxSpeed;

	//Añadimos el nodo
	vector3df TScale = vector3df(1.0f, 1.0f, 1.0f);
	auxNode = smgr->addAnimatedMeshSceneNode(mesh);
	
	auxNode->setScale(TScale);
	auxNode->setPosition(vector3df(0.f,30.f,0.f));
	auxNode->setMaterialFlag(EMF_LIGHTING, true);
	auxNode->setMaterialTexture(0,texture);
	auxNode->setFrameLoop(251,500);
}

Personaje::~Personaje(){
}

//Actualizamos al personaje
void Personaje::actualizar(){

	anteriorEstado=estado;

	if (velocidad == 0.0f){
		estado = false;
	} else{
		estado = true;
		if (velocidad > 0.0f){
			velocidad -= 0.5f;
		} else {
			velocidad += 0.5f;
		}
	}

	if (anteriorEstado!=estado) {
		if (estado) getNode()->setFrameLoop(251,500);
		else getNode()->setFrameLoop(0,250);
	}

	vector3df direccion = getNode()->getRotation().rotationToDirection();
	getNode()->setPosition(getNode()->getPosition()+(direccion*velocidad));
}

void Personaje::acelera(bool direccion){
	previousPosition = getNode()->getPosition();
	if (direccion){
		velocidad = maxSpeed;
	} else {	
		velocidad = -maxSpeed;
	}
}
void Personaje::gira(bool direccion){
	if (!direccion){
		getNode()->setRotation(getNode()->getRotation()+vector3df(0.0f,3.0f,0.0f));
	} else {
		getNode()->setRotation(getNode()->getRotation()-vector3df(0.0f,3.0f,0.0f));
	}
}
void Personaje::goBack(){
	getNode()->setPosition(previousPosition);
	velocidad = 0;
}

IAnimatedMeshSceneNode *Personaje::getNode(){
	return auxNode;
}
