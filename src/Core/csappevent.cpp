#include "csappevent.h"


namespace cs
{

CSAppEvent *CSAppEvent::_instance = nullptr;


CSAppEvent::~CSAppEvent()
{
    if (_instance) _instance->deleteLater();
}

CSAppEvent *CSAppEvent::instance()
{
    if (_instance) return _instance;

    _instance = new CSAppEvent();
    return _instance;
}

CSAppEvent::CSAppEvent()
{
    // Do nothing
}

}
