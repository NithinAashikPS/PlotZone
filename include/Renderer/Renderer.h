//
// Created by Aashik on 06-07-2024.
//

#pragma once

#include "platform.h"
#include "urlClient.h"

namespace Tangram {

    class Renderer final : public Platform {

    public:

        Renderer();
        explicit Renderer(UrlClient::Options urlClientOptions);
        ~Renderer() override;
        void shutdown() override;
        void requestRender() const override;
        std::vector<FontSourceHandle> systemFontFallbacksHandle() const override;
        bool startUrlRequestImpl(const Url& _url, const UrlRequestHandle _request, UrlRequestId& _id) override;
        void cancelUrlRequestImpl(const UrlRequestId _id) override;

    protected:
        std::unique_ptr<UrlClient> m_urlClient;
    };

} // namespace Tangram