#include <irrlicht.h>
#include "Combate.h"

Combate::Combate(IrrlichtDevice *device,IVideoDriver *driver,ISceneManager *smgr,IGUIEnvironment* guienv){

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
	cerdo = new Personaje(smgr,driver,pigMesh,pigTexture,1.0);
	car = new Personaje(smgr,driver,carMesh,carTexture,2.0);
	plane = new Personaje(smgr,driver,planeMesh,planeTexture,3.0);

	playerObject = cerdo;
	timer = 0;

//Position the objects
	plane->getNode()->setPosition(vector3df(100,100,100));
	car->getNode()->setPosition(vector3df(-100,100,100));

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
	if (playerObject == cerdo){
		if (closeTo == 1){
			camara = new Camara(smgr,car->getNode());
			playerObject = car;
			cerdo->getNode()->setVisible(false);
		} else if (closeTo == 2){
			camara = new Camara(smgr,plane->getNode());
			playerObject = plane;
			cerdo->getNode()->setVisible(false);
		}
	} else {
			if (playerObject == plane){
				vector3d<f32> * edges = new vector3d<f32>[8];
				plane->getNode()->getTransformedBoundingBox().getEdges(edges);
				cerdo->getNode()->setPosition(plane->getNode()->getPosition()+edges[0]);
			} else {
				vector3d<f32> * edges = new vector3d<f32>[8];
				car->getNode()->getTransformedBoundingBox().getEdges(edges);
				cerdo->getNode()->setPosition(car->getNode()->getPosition()+edges[0]);
			}
			camara = new Camara(smgr,cerdo->getNode());
			playerObject = cerdo;
			cerdo->getNode()->setVisible(true);
	}
}

//Actualización del combate
void Combate::actualizar(IrrlichtDevice *device,ISceneManager *smgr,IVideoDriver *driver,u32 TDeltaTime){

	if (timer > 0){
		timer --;
	}

	//Según las teclas WSAD, aceleramos o giramos al cerdo
		if(receiver->IsKeyDown(KEY_KEY_W))
			playerObject->acelera(true);
		else if(receiver->IsKeyDown(KEY_KEY_S))
			playerObject->acelera(false);
		if(receiver->IsKeyDown(KEY_KEY_A))
			playerObject->gira(true);
		else if(receiver->IsKeyDown(KEY_KEY_D))
			playerObject->gira(false);
		if(receiver->IsKeyDown(KEY_KEY_E)){
			if (timer == 0){
				action(smgr);
				timer = 100;
			}
		}

//Actualizamos al otro cerdo
		playerObject->actualizar();
		camara->moveCameraControl(device);

	
//TODO: Ver si podemos meter esto en un bucle
//Si ha colisionado con el coche, le hace volver a la posición anterior
closeTo = 0;
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
