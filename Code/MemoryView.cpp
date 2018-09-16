#include "MemoryView.h"

#include <cstring>
#include <algorithm>

using namespace ::std;

ConstMemoryView::ConstMemoryView(char const* string)
    : MemoryView{ reinterpret_cast<uint8_t const*>(string),
            reinterpret_cast<uint8_t const*>(string) + strlen(string) }
{
}

ConstMemoryView::ConstMemoryView(MutableMemoryView const& view)
    : MemoryView{view.begin(), view.end()}
{
}

ConstMemoryView& ConstMemoryView::operator=(MutableMemoryView const& view)
{
    dataBegin = view.begin();
    dataEnd = view.end();

    return *this;
}

ConstMemoryView ConstMemoryView::SubView(size_t index, size_t length) const
{
    auto start = begin() + index;
    if(start < begin() || start > end())
    {
        return {};
    }

    if((index + length) > size())
    {
        return {};
    }

    return { start, start + length };
}


MutableMemoryView MutableMemoryView::SubView(size_t index, size_t length)
{
    auto start = begin() + index;
    if(start < begin() || start > end())
    {
        return {};
    }

    if((index + length) > size())
    {
        return {};
    }

    return { start, start + length };
}


size_t MutableMemoryView::CopyFrom(ConstMemoryView const& view)
{
    size_t elementsToCopy = min(size(), view.size());
    copy_n(view.begin(), elementsToCopy, begin());
    return elementsToCopy;
}

size_t MutableMemoryView::CopyFrom(MutableMemoryView& view)
{
    size_t elementsToCopy = min(size(), view.size());
    copy_n(view.begin(), elementsToCopy, begin());
    return elementsToCopy;
}
