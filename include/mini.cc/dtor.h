#pragma once

namespace mini
{
    template<typename T, typename Dtor>
    struct AttachDtor {
    public:
        AttachDtor(T &target, Dtor dtor) : target_(target), dtor_(dtor) {}

        ~AttachDtor() {
            dtor_(&target_);
        }
    private:
        T &target_;
        Dtor dtor_;
    };

}
