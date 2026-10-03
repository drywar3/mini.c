#pragma once

namespace mini
{
    template<typename Fn>
    struct ScopeGuard {
        ScopeGuard(Fn fn) : fn(fn) {}
        ~ScopeGuard() {
            fn();
        }

        /* todo: remove move/copy operators */
    private:
        Fn fn;
    };
} // namespace mini
