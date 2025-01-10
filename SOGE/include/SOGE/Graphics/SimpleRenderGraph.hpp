﻿#ifndef SOGE_GRAPHICS_SIMPLERENDERGRAPH_HPP
#define SOGE_GRAPHICS_SIMPLERENDERGRAPH_HPP

#include "SOGE/Graphics/GraphicsCompilePreproc.hpp"
#include "SOGE/Graphics/RenderGraph.hpp"
#include "SOGE/System/Memory.hpp"
#include "SOGE/Utils/PreprocessorHelpers.hpp"

#include SOGE_ABS_COMPILED_GRAPHICS_IMPL_HEADER(SOGE/Graphics, GraphicsCore.hpp)


namespace soge
{
    class FinalGraphicsRenderPass;
    class TriangleGraphicsPipeline;

    class SimpleRenderGraph : public RenderGraph
    {
    private:
        eastl::reference_wrapper<GraphicsCore> m_core;

        UniquePtr<TriangleGraphicsPipeline> m_pipeline;
        UniquePtr<FinalGraphicsRenderPass> m_renderPass;

        eastl::vector<nvrhi::ICommandList*> m_commandLists;

    public:
        explicit SimpleRenderGraph(ImplGraphicsCore& aCore);

        SimpleRenderGraph(const SimpleRenderGraph&) = delete;
        SimpleRenderGraph& operator=(const SimpleRenderGraph&) = delete;

        SimpleRenderGraph(SimpleRenderGraph&& aOther) noexcept = default;
        SimpleRenderGraph& operator=(SimpleRenderGraph&& aOther) noexcept = default;

        ~SimpleRenderGraph() override;

        void Execute(float aDeltaTime) override;
    };
}

SOGE_DI_REGISTER_NS(soge, SimpleRenderGraph, df::Single<SimpleRenderGraph, ImplGraphicsCore>,
                    tag::Overrides<RenderGraph>)

#endif // SOGE_GRAPHICS_SIMPLERENDERGRAPH_HPP
