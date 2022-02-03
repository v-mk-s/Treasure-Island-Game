//
// Created by alexey on 07.12.2021.
//

#include "EventBus.h"

void EventBus::subscribe(IObservable *sub, int type) {
    subscribers.push_back({sub, type});
}

void EventBus::dispatch(int type, const Event& event) {
    for (auto sub: subscribers) {
        if (sub.type == type) {
            sub.sub->update(event);
        }
    }
}

void EventBus::unsubscribe(IObservable *sub_to_delete, int type) {
    std::vector<Subscriber> new_subs = {};

    for (auto sub: subscribers) {
        if (sub.type != type || sub.sub != sub_to_delete) {
            new_subs.push_back(sub);
        }
    }

    subscribers = new_subs;
}
