#pragma once
#include <functional>
#include <memory>
#include <string>
#include <mutex> 
#include <unordered_map>
#include <shared_mutex>
#include <middleware/core/IHandler.h>

using namespace std;

class ChainFactoryRegistry {
public:
    using Creator = function<unique_ptr<IHandler>()>;

    static ChainFactoryRegistry& instance() {
        static ChainFactoryRegistry inst;
        return inst;
    }

    void registerFactory(const string& name, Creator creator) {
        unique_lock<shared_mutex> lk(mutex_);
        creators_[name] = move(creator);
    }

    Creator getCreator(const string& name) const {
        shared_lock<shared_mutex> lk(mutex_);
        auto it = creators_.find(name);
        if (it == creators_.end()) return nullptr;
        return it->second;
    }

    unique_ptr<IHandler> createChain(const string& name) const {
        auto c = getCreator(name);
        if (!c) return nullptr;
        return c();
    }

private:
    mutable shared_mutex mutex_;
    unordered_map<string, Creator> creators_;
    ChainFactoryRegistry() = default;
    ChainFactoryRegistry(const ChainFactoryRegistry&) = delete;
    ChainFactoryRegistry& operator=(const ChainFactoryRegistry&) = delete;
};

struct ChainFactoryRegistrar {
    ChainFactoryRegistrar(const string& name, ChainFactoryRegistry::Creator c) {
        ChainFactoryRegistry::instance().registerFactory(name, move(c));
    }
};