#pragma once
#include <memory>
#include <core/iiterator.h>
#include <factory/iterator_kind.h>

class IIterable {
    public:
        virtual ~IIterable() = default;
        virtual unique_ptr<IIterator> createIterator(IteratorKind k = IteratorKind::ITER_FORWARD) = 0;
};