#ifndef __SIMPLEETHERNET_APPLICATIONDISPATCHER_H_
#define __SIMPLEETHERNET_APPLICATIONDISPATCHER_H_

#include <omnetpp.h>

using namespace omnetpp;

class ApplicationDispatcher : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
