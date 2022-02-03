//
// Created by alexey on 07.12.2021.
//

#ifndef ISLANDGAME_EVENTBUS_H
#define ISLANDGAME_EVENTBUS_H

#include "IObservable.h"
#include <vector>

struct Subscriber {
    IObservable *sub;
    int type;
};

class EventBus {
public:
    void subscribe(IObservable *sub, int type);
    void unsubscribe(IObservable *sub, int type);

    void dispatch(int type, const Event& event);

private:
    std::vector<Subscriber> subscribers;
};

#endif //ISLANDGAME_EVENTBUS_H
