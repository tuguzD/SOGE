#include "GAME/Layers/MainGameLayer.hpp"
#include "GAME/AppEntryPoint.hpp"


namespace soge_game
{
    MainGameLayer::MainGameLayer() : Layer("MainGameLayer")
    {
        SOGE_INFO_LOG("Global engine instance pointer is {}", static_cast<void*>(soge::Engine::GetInstance()));
    }

    void MainGameLayer::OnAttach()
    {
        SOGE_APP_INFO_LOG(R"(Layer "{}" attached...)", m_layerName.c_str());
    }

    void MainGameLayer::OnDetach()
    {
        SOGE_APP_INFO_LOG(R"(Layer "{}" detached...)", m_layerName.c_str());
    }

    void MainGameLayer::OnUpdate()
    {
        const auto engine = soge::Engine::GetInstance();
        if (const auto inputModule = engine->GetModule<soge::InputModule>(); inputModule->IsKeyPressed(soge::Keys::W))
        {
            SOGE_APP_INFO_LOG("Key W pressed!");
        }
        else if (inputModule->IsKeyPressed(soge::Keys::Escape))
        {
            SOGE_APP_INFO_LOG("Key W pressed");
        }
    }

    void MainGameLayer::OnFixedUpdate(float aDeltaTime)
    {
    }
}
