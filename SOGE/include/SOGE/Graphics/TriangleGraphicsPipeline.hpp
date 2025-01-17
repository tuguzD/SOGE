﻿#ifndef SOGE_GRAPHICS_TRIANGLEGRAPHICSPIPELINE_HPP
#define SOGE_GRAPHICS_TRIANGLEGRAPHICSPIPELINE_HPP

#include "SOGE/Graphics/FinalGraphicsRenderPass.hpp"
#include "SOGE/Graphics/GraphicsCore.hpp"
#include "SOGE/Graphics/GraphicsPipeline.hpp"


namespace soge
{
    class TriangleGraphicsPipeline : public GraphicsPipeline
    {
    private:
        eastl::reference_wrapper<GraphicsCore> m_core;
        eastl::reference_wrapper<FinalGraphicsRenderPass> m_renderPass;

        nvrhi::ShaderHandle m_nvrhiVertexShader;
        nvrhi::InputLayoutHandle m_nvrhiInputLayout;
        nvrhi::ShaderHandle m_nvrhiPixelShader;
        nvrhi::BindingLayoutHandle m_nvrhiBindingLayout;
        nvrhi::GraphicsPipelineHandle m_nvrhiGraphicsPipeline;

        eastl::vector<nvrhi::CommandListHandle> m_commandLists;

    public:
        class Entity
        {
        public:
            struct Tag
            {
            };

            struct ConstantBuffer
            {
                glm::mat4x4 m_modelViewProjection;
            };

            struct Vertex
            {
                alignas(16) glm::vec3 m_position;
                glm::vec4 m_color;
            };

            using Index = std::uint32_t;

            constexpr explicit Entity() noexcept = default;

            constexpr Entity(const Entity&) = delete;
            constexpr Entity& operator=(const Entity&) = delete;

            constexpr Entity(Entity&&) noexcept = default;
            constexpr Entity& operator=(Entity&&) noexcept = default;

            constexpr virtual ~Entity() = default;

            [[nodiscard]]
            constexpr virtual nvrhi::BindingSetHandle GetBindingSet(Tag) = 0;
            [[nodiscard]]
            constexpr virtual nvrhi::BufferHandle GetConstantBuffer(Tag) = 0;
            [[nodiscard]]
            constexpr virtual nvrhi::BufferHandle GetVertexBuffer(Tag) = 0;
            [[nodiscard]]
            constexpr virtual nvrhi::BufferHandle GetIndexBuffer(Tag) = 0;

            [[nodiscard]]
            constexpr virtual glm::mat4x4 GetWorldMatrix(Tag) = 0;
        };

        explicit TriangleGraphicsPipeline(GraphicsCore& aCore, FinalGraphicsRenderPass& aRenderPass);

        TriangleGraphicsPipeline(const TriangleGraphicsPipeline&) = delete;
        TriangleGraphicsPipeline& operator=(const TriangleGraphicsPipeline&) = delete;

        TriangleGraphicsPipeline(TriangleGraphicsPipeline&& aOther) noexcept;
        TriangleGraphicsPipeline& operator=(TriangleGraphicsPipeline&& aOther) noexcept;

        ~TriangleGraphicsPipeline() override;

        // NOLINTNEXTLINE(readability-identifier-naming) reason: ADL support
        void swap(TriangleGraphicsPipeline& aOther) noexcept;

        [[nodiscard]]
        nvrhi::IGraphicsPipeline& GetGraphicsPipeline() noexcept override;

        [[nodiscard]]
        CommandLists Execute(const nvrhi::Viewport& aViewport, const Camera& aCamera, Entities aEntities) override;
    };
}

SOGE_DI_REGISTER_NS(soge, TriangleGraphicsPipeline,
                    df::Single<TriangleGraphicsPipeline, GraphicsCore, FinalGraphicsRenderPass>)

#endif // SOGE_GRAPHICS_TRIANGLEGRAPHICSPIPELINE_HPP
