#include <stdexcept>

namespace Details{
    template <typename F>
    class ScopeGuard {
    public:
        explicit ScopeGuard(F&& fn) : m_fn(fn) {}
        ~ScopeGuard() {
            if (!m_dismiss) {
                m_fn();
            }
        }
        void Dismiss() {
            m_dismiss = true;
        }
    private:
        F m_fn;
        bool m_dismiss = false;
    };

    struct ScopeGuardOnExit{};

    template<typename F>
    static inline ScopeGuard<F> operator+ (ScopeGuardOnExit, F&& fn) {
        return ScopeGuard<F>(std::forward<F>(fn));
    }
}

#define ON_SCOPE_EXIT auto __onGuardExit__ = Details::ScopeGuardOnExit{} + [&]

#define CANCEL_SCOPE_EXIT __onGuardExit__.Dismiss();