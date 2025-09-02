#include "middleware/router/MiddlewareManager.h"
#include "middleware/handlers/AbstractHandler.h"
using namespace std;

void MiddlewareManager::addChain(const string& name, unique_ptr<IHandler> head) {
    chains[name] = move(head);
}

IHandler* MiddlewareManager::getChain(const string& name)  {
    auto it = chains.find(name);
    if (it == chains.end()) return nullptr;
    return it->second.get();
}

void MiddlewareManager::append(const string& chainName, unique_ptr<IHandler> handler) {
    auto head = getChain(chainName);
    if (!head) { chains[chainName] = move(handler); return; }
    AbstractHandler* cur = static_cast<AbstractHandler*>(head);
    while (cur->next) cur = static_cast<AbstractHandler*>(cur->next.get());
    cur->setNext(move(handler));
}

void MiddlewareManager::prepend(const string& chainName, unique_ptr<IHandler> handler) {
    auto it = chains.find(chainName);
    if (it == chains.end() || !it->second) {
        chains[chainName] = move(handler);
        return;
    }
    AbstractHandler* newHead = static_cast<AbstractHandler*>(handler.get());
    newHead->setNext(move(it->second));
    chains[chainName] = move(handler);
}

void MiddlewareManager::insertAfter(const string& chainName, const string& existingHandlerName, unique_ptr<IHandler> handler) {
    if (!handler) return;

    auto it = chains.find(chainName);
    if (it == chains.end() || !it->second) {
        chains[chainName] = move(handler);
        return;
    }

    AbstractHandler* cur = dynamic_cast<AbstractHandler*>(it->second.get());
    while (cur) {
        if (cur->name == existingHandlerName) {
            AbstractHandler* newNode = dynamic_cast<AbstractHandler*>(handler.get());
            newNode->setNext(move(cur->next));
            cur->setNext(move(handler));      
            return;
        }
        cur = dynamic_cast<AbstractHandler*>(cur->next.get());
    }
}

void MiddlewareManager::removeHandler(const string& chainName, const string& handlerName) {
    auto it = chains.find(chainName);
    if (it == chains.end() || !it->second) return;

    AbstractHandler* head = dynamic_cast<AbstractHandler*>(it->second.get());
    if (head->name == handlerName) {
        it->second = move(head->next);
        return;
    }
    AbstractHandler* prev = head;
    while (prev->next) {
        AbstractHandler* cur = dynamic_cast<AbstractHandler*>(prev->next.get());
        if (cur->name == handlerName) {
            prev->setNext(move(cur->next));
            return;
        }
        prev = cur;
    }
}
