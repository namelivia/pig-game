#include <irrlicht.h>
#include "Camara.h"

Camara::Camara(ISceneManager *smgr,IAnimatedMeshSceneNode *player){
	//Cargamos una cámara FPS (De prueba)
	//camara = smgr->addCameraSceneNodeFPS();
	camara = smgr->addCameraSceneNode(0,core::vector3df(0.0f,0.0f,0.0f),core::vector3df(0.0f,0.0f,0.0f), -1);
	camara->setID(0);
	direction = 0;
	zdirection = 0;
	playerNode = player;
}

Camara::~Camara(){
	delete camara;
}

ICameraSceneNode *Camara::getNode(){
	return camara;
}

void Camara::moveCameraControl(IrrlichtDevice *device)
{
     position2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
     ICameraSceneNode* camera = getNode();
     vector3df cameraPos = camera->getAbsolutePosition();
     
     float change_x = ( cursorPos.X - 0.5 ) * 256.0f;
     float change_y = ( cursorPos.Y - 0.5 ) * 256.0f;
     direction += change_x;
     zdirection -= change_y;
     if( zdirection <- 90 )
         zdirection = -90;
     else
     if( zdirection > 90 )
         zdirection = 90;
     device->getCursorControl()->setPosition( 0.5f, 0.5f );
     
     vector3df playerPos = playerNode->getPosition();
     
     float xf = playerPos.X - cos( direction * PI / 180.0f ) * 64.0f;
     float yf = playerPos.Y - sin( zdirection * PI / 180.0f ) * 64.0f;
     float zf = playerPos.Z + sin( direction * PI / 180.0f ) * 64.0f;
     
     camera->setPosition( vector3df( xf, yf, zf ) );
     camera->setTarget( vector3df( playerPos.X, playerPos.Y+25.0f, playerPos.Z ) );
     //playerNode->setRotation(vector3df( 0, direction, 0 ) );
}
