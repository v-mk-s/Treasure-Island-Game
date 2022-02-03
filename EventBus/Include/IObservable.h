//
// Created by alexey on 07.12.2021.
//

#ifndef ISLANDGAME_IOBSERVABLE_H
#define ISLANDGAME_IOBSERVABLE_H

#include "Event.h"

class IObservable {
public:
    virtual void update(Event event) = 0;
};

#endif //ISLANDGAME_IOBSERVABLE_H
