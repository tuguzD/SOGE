#ifndef SOGE_CORE_DI_CONTAINER_HPP
#define SOGE_CORE_DI_CONTAINER_HPP

#include "SOGE/Core/DI/Dependency.hpp"

#include <kangaru/container.hpp>
#include <kangaru/operator_service.hpp>


namespace soge::di
{
    class Container
    {
    private:
        kgr::container m_container;

    public:
        template <Dependency T, typename... Args>
        bool Create(Args&&... args)
        {
            using Service = DependencyDefinition<T>;

            return m_container.emplace<Service>(std::forward<Args>(args)...);
        }

        template <Dependency T>
        [[nodiscard]]
        auto Provide() -> decltype(auto)
        {
            using Service = DependencyDefinition<T>;

            return m_container.service<Service>();
        }

        template <Dependency T>
        [[nodiscard]]
        Lazy<T> ProvideLazy()
        {
            using Service = kgr::lazy_service<DependencyDefinition<T>>;

            return m_container.service<Service>();
        }

        template <PolymorphicDependency T>
        [[nodiscard]]
        PolymorphicRange<T> ProvideRange()
        {
            using Service = kgr::override_range_service<DependencyDefinition<T>>;

            return m_container.service<Service>();
        }
    };
}

#endif // SOGE_CORE_DI_CONTAINER_HPP
