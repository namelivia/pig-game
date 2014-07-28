#include <irrlicht.h>
#include "Combate.h"

Combate::Combate(IrrlichtDevice *device,IVideoDriver *driver,ISceneManager *smgr,IGUIEnvironment* guienv){

	closeTo = 0;
//Inicializamos un escenario
	escenario = new Escenario(smgr,driver);

//Cargamos el modelo del cerdo y la textura
	IAnimatedMesh *pigMesh = smgr->getMesh("media/cerdo.x");
	ITexture *pigTexture = driver->getTexture("media/cerdo.png");
	IAnimatedMesh *carMesh = smgr->getMesh("media/car.x");
	ITexture *carTexture = driver->getTexture("media/car.png");
	IAnimatedMesh *planeMesh = smgr->getMesh("media/plane.x");
	ITexture *planeTexture = driver->getTexture("media/plane.png");

//Inicializamos un cerdo rosa 
	cerdo = new Personaje(smgr,driver,pigMesh,pigTexture);
	car = new Vehicle(smgr,driver,carMesh,carTexture);
	plane = new Vehicle(smgr,driver,planeMesh,planeTexture);

//Movemos el avión a otro sitio
	plane->getNode()->setPosition(vector3df(100,100,100));

//colisión entre cerdo y escenario
	ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(escenario->getSelector(),cerdo->getNode(),vector3df(3,3,3),vector3df(0,-10,0),vector3df(0,0,0));
	cerdo->getNode()->addAnimator(anim);

//colisión etre el coche y escenario
	ISceneNodeAnimator* animCar = smgr->createCollisionResponseAnimator(escenario->getSelector(),car->getNode(),vector3df(3,3,3),vector3df(0,-10,0),vector3df(0,0,0));
	car->getNode()->addAnimator(animCar);

//colisión etre el avión y escenario
	ISceneNodeAnimator* animPlane = smgr->createCollisionResponseAnimator(escenario->getSelector(),plane->getNode(),vector3df(3,3,3),vector3df(0,-10,0),vector3df(0,0,0));
	plane->getNode()->addAnimator(animPlane);

//Inicializamos receptor de eventos y cámara
	smgr->setShadowColor(video::SColor(150,0,0,0));
	receiver = new EventReceiver();
	device->setEventReceiver(receiver);
	camara = new Camara(smgr,cerdo->getNode());

//Mensaje
	 guienv->addStaticText(L"Bienvenido a la nuevo demo del cerdo",rect<s32>(10,10,260,22), true);

}


Combate::~Combate(){
delete camara;
delete receiver;
delete cerdo;
delete escenario;
}

//
void Combate::action(ISceneManager *smgr){
	if (closeTo == 1){
		camara = new Camara(smgr,car->getNode());
	} else if (closeTo == 2){
		camara = new Camara(smgr,plane->getNode());
	}
}

//Actualización del combate
void Combate::actualizar(IrrlichtDevice *device,ISceneManager *smgr,IVideoDriver *driver,u32 TDeltaTime){

//Según las teclas WSAD, aceleramos o giramos al cerdo
		if(receiver->IsKeyDown(KEY_KEY_W))
			cerdo->acelera(true);
		else if(receiver->IsKeyDown(KEY_KEY_S))
			cerdo->acelera(false);
		if(receiver->IsKeyDown(KEY_KEY_A))
			cerdo->gira(true);
		else if(receiver->IsKeyDown(KEY_KEY_D))
			cerdo->gira(false);
		if(receiver->IsKeyDown(KEY_KEY_E))
			action(smgr);

//Actualizamos al otro cerdo
		cerdo->actualizar();
		camara->moveCameraControl(device);

	
//TODO: Ver si podemos meter esto en un bucle
//Si ha colisionado con el coche, le hace volver a la posición anterior
		if(cerdo->getNode()->getTransformedBoundingBox().intersectsWithBox(car->getNode()->getTransformedBoundingBox())) {
			//Ñapa? Para que no colisionen en el primer fotograma
			if (cerdo->getNode()->getPosition().Z != 0.0f){
				cerdo->goBack();
				closeTo = 1;
			}
		}

//Si ha colisionado, le hace volver a la posición anterior
		if(cerdo->getNode()->getTransformedBoundingBox().intersectsWithBox(plane->getNode()->getTransformedBoundingBox())) {
			//Ñapa? Para que no colisionen en el primer fotograma
			if (cerdo->getNode()->getPosition().Z != 0.0f){
				cerdo->goBack();
				closeTo = 2;
			}
		}

}
