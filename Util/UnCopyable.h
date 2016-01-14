#ifndef __CRYSTAL_UTIL_UNCOPYABLE_H__
#define __CRYSTAL_UTIL_UNCOPYABLE_H__

struct UnCopyable {
    UnCopyable() = default;
    UnCopyable(const UnCopyable&) = delete;
    UnCopyable& operator=(const UnCopyable&) = delete;
};

#endif