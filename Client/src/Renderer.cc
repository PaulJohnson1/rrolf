#include <Renderer.hh>

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

static app::Renderer *g_Renderer = nullptr;

#ifdef WASM_BUILD
#include <emscripten.h>

extern "C"
{
    void KeyEvent(uint8_t op, int32_t key)
    {
        std::cout << std::to_string(op) << ' ' << key << '\n';
        if (op == 1)
            g_Renderer->m_KeysPressed[key] = 1;
        else if (op == 0)
            g_Renderer->m_KeysPressed[key] = 0;
    }
    void Render(int32_t width, int32_t height)
    {
        if (!g_Renderer)
            return;
        g_Renderer->SetSize(width, height);
        g_Renderer->Render();
    }
}
#else
#define SK_GL
#include <GLFW/glfw3.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkColor.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkColorSpace.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/GrBackendSurface.h>
void SkDebugf(const char format[], ...)
{
}

void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        g_Renderer->m_KeysPressed[key] = 1;
    else if (action == GLFW_RELEASE)
        g_Renderer->m_KeysPressed[key] = 0;
}

#endif

#include <Simulation.hh>

namespace app
{
    Renderer::Renderer(Simulation &simulation)
        : m_Simulation(simulation)
    {
        assert(!g_Renderer);
        g_Renderer = this;
    }

    void Renderer::Initialize()
    {
#ifndef WASM_BUILD
        // 16:9 aspect ratio for 500 height
        m_Width = 889;
        m_Height = 500;
        glfwSetErrorCallback([](int error, char const *description)
                             { std::cerr << "code " << error << ' ' << description << '\n'; });
        glfwInit();
        GLFWwindow *window = glfwCreateWindow(m_Width, m_Height, "rrolf native client", NULL, NULL);
        glfwSetKeyCallback(window, GlfwKeyCallback);

        if (!window)
        {
            std::cerr << "window thing failed\n";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        sk_sp<GrGLInterface const> interface = GrGLMakeNativeInterface();
        GrDirectContext *context = GrDirectContext::MakeGL(interface).release();
        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0;
        framebufferInfo.fFormat = GL_RGBA8;
        SkColorType colorType = kRGBA_8888_SkColorType;
        GrBackendRenderTarget backendRenderTarget(m_Width, m_Height,
                                                  0, // sample count
                                                  0, // stencil bits
                                                  framebufferInfo);
        SkSurface *surface = SkSurface::MakeFromBackendRenderTarget(context, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
        m_Canvas = surface->getCanvas();

        while (!glfwWindowShouldClose(window))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            context->flush();
            Render();
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
#else
        EM_ASM({
            const canvasElement = document.createElement("canvas");
            canvasElement.id = "rrolf";
            document.body.appendChild(canvasElement);
            const script = document.createElement("script");
            script.src = "https://unpkg.com/canvaskit-wasm@0.19.0/bin/canvaskit.js";
            document.getElementsByTagName("head")[0].appendChild(script);
            script.onload = function()
            {
                const ckLoaded = CanvasKitInit({
                    locateFile(file) { return 'https://unpkg.com/canvaskit-wasm@0.19.0/bin/'+file; } });
        ckLoaded.then(function(CanvasKit) {
            const fps = 60;
            const tickDelay = 1000 / 60;
            let lastTick = Date.now();
            const Draw = function(canvas)
            {
                Module.surface.requestAnimationFrame(Draw);
                if (Date.now() - lastTick < tickDelay)
                    return;

                console.log("frame");                

                Module.canvas = canvas;
                Module._Render(canvasElement.width, canvasElement.height);
            };
            const InitCanvas = function()
            {
                canvasElement.width = innerWidth;
                canvasElement.height = innerHeight;
                const surface = CanvasKit.MakeCanvasSurface("rrolf");
                Module.CanvasKit = CanvasKit;
                Module.surface = surface;
                Module.surface.requestAnimationFrame(Draw);
            };
            window.addEventListener(
                "resize", function() { InitCanvas(); });

            window.addEventListener("keydown", function ({ which }) { Module._KeyEvent(1, which);});
            window.addEventListener("keyup", function ({ which }) { Module._KeyEvent(0, which);});
            InitCanvas();
        });
    }
});
#endif
    }

    void Renderer::Clear()
    {
#ifndef WASM_BUILD
        m_Canvas->clear(0);
#else
    EM_ASM({
        Module.canvas.clear(Module.CanvasKit.BLACK);
    });
#endif
    }

    void Renderer::Translate(float x, float y)
    {
#ifndef WASM_BUILD
        m_Canvas->translate(x, y);
#else
    EM_ASM({Module.canvas.translate($0, $1)}, x, y);
#endif
    }

    void Renderer::Scale(float x, float y)
    {
#ifndef WASM_BUILD
        m_Canvas->scale(x, y);
#else
    EM_ASM({Module.canvas.scale($0, $1)}, x, y);
#endif
    }

    void Renderer::Save()
    {
#ifndef WASM_BUILD
        m_Canvas->save();
#else
    EM_ASM({
        Module.canvas.save();
    });
#endif
    }

    void Renderer::Restore()
    {
#ifndef WASM_BUILD
        m_Canvas->restore();
#else
    EM_ASM({
        Module.canvas.restore();
    });
#endif
    }

    void Renderer::DrawCircle(float x, float y, float size, Paint const &paint)
    {
#ifndef WASM_BUILD
        SkPaint skPaint;
        skPaint.setStyle(static_cast<SkPaint::Style>(paint.m_Style));
        skPaint.setStrokeWidth(paint.m_StrokeWidth);
        skPaint.setAntiAlias(paint.m_AntiAliased);
        skPaint.setColor(SkColorSetARGB(paint.m_Alpha, paint.m_Red, paint.m_Blue, paint.m_Green));
        m_Canvas->drawCircle(x, y, size, skPaint);
#else
    EM_ASM({
        const paint = new Module.CanvasKit.Paint();
        if ($0 == 0)
            paint.setStyle(Module.CanvasKit.PaintStyle.Fill);
        if ($0 == 1)
            paint.setStyle(Module.CanvasKit.PaintStyle.Stroke);
        if ($0 == 1)
            paint.setStrokeWidth($1);
        paint.setAntiAlias($2);
        paint.setColor(Module.CanvasKit.Color4f($3 / 255, $4 / 255, $5 / 255, $6 / 255));
        Module.canvas.drawCircle($7, $8, $9, paint);
    },
           paint.m_Style, paint.m_StrokeWidth, paint.m_AntiAliased, paint.m_Red, paint.m_Blue, paint.m_Green, paint.m_Alpha, x, y, size);
#endif
    }

    void Renderer::SetSize(int32_t width, int32_t height)
    {
#ifdef WASM_BUILD
        m_Width = width;
        m_Height = height;
#else
    assert(false);
#endif
    }

    void Renderer::Render()
    {
        m_Simulation.TickRenderer(this);
    }
}
