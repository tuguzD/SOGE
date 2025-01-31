﻿#include "sogepch.hpp"

#include "SOGE/Graphics/Resources/TextureResource.hpp"


namespace soge
{
    TextureResource::TextureResource(GraphicsCore& aCore, const eastl::string_view aName, cppfs::FilePath aFullPath,
                                     nvrhi::TextureDesc aTextureDesc)
        : ResourceBase{aName, std::move(aFullPath)}, m_core{aCore}, m_textureDesc{std::move(aTextureDesc)}
    {
    }

    nvrhi::ITexture* TextureResource::GetTextureResource()
    {
        return m_textureHandle;
    }
}
