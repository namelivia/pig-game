#include <irrlicht.h>
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiver : public IEventReceiver
{
public:
	EventReceiver();
	virtual bool OnEvent(const SEvent& event);
	bool IsKeyDown(irr::EKEY_CODE) const;
private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
