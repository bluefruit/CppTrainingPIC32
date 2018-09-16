#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <cstddef>
#include <cstdint>

template<typename T>
class MemoryView
{
public:
    using iterator = T*;
    using reference = T&;

protected:
    iterator dataBegin{nullptr};
    iterator dataEnd{nullptr};

public:
    MemoryView() = default;

    template<size_t N>
    MemoryView(T (&array)[N])
        : dataBegin{array}
        , dataEnd{array + N}
    {
    }

    MemoryView(iterator begin, iterator end)
        : dataBegin{begin}
        , dataEnd{end}
    {
    }

    reference operator[](size_t index)
    {
        return dataBegin[index];
    }
    iterator begin() const
    {
        return dataBegin;
    }

    iterator end() const
    {
        return dataEnd;
    }

    size_t size() const
    {
        return dataEnd - dataBegin;
    }
};

class MutableMemoryView;

class ConstMemoryView : public MemoryView<uint8_t const>
{
public:
    using MemoryView::MemoryView;

    ConstMemoryView() = default;
    ConstMemoryView(char const* string);
    ConstMemoryView(MutableMemoryView const& view);
    ConstMemoryView& operator=(MutableMemoryView const& view);

    ConstMemoryView SubView(size_t index, size_t length) const;
};

class MutableMemoryView : public MemoryView<uint8_t>
{
public:
    using MemoryView::MemoryView;

    MutableMemoryView SubView(size_t index, size_t length);

    size_t CopyFrom(ConstMemoryView const& view);
    size_t CopyFrom(MutableMemoryView& view);
};

#endif // MEMORYVIEW_H
