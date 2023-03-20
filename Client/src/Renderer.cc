#include <Renderer.hh>

#include <iostream>
#include <chrono>
#include <thread>

// #ifdef WASM_BUILD
// #include <emscripten.h>

// extern "C"
// {
//     void Render(app::Renderer *renderer)
//     {
//         renderer->Render();
//     }
// }
// #else
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
// #endif

#include <Simulation.hh>

namespace app
{
    Renderer::Renderer(Simulation &simulation)
        : m_Simulation(simulation)
    {
    }

    void Renderer::Initialize()
    {
// #ifndef WASM_BUILD
        constexpr int32_t CANVAS_WIDTH = 800;
        constexpr int32_t CANVAS_HEIGHT = 500;
        glfwSetErrorCallback([](int error, char const *description)
                             { std::cerr << "code " << error << ' ' << description << '\n'; });

        glfwInit();
        GLFWwindow *window = glfwCreateWindow(CANVAS_WIDTH, CANVAS_HEIGHT, "rrolf native client", NULL, NULL);

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
        GrBackendRenderTarget backendRenderTarget(CANVAS_WIDTH, CANVAS_HEIGHT,
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
            glfwSwapBuffers(window);
        }
// #else
//         EM_ASM({
//             Module.canvas = document.createElement("canvas");
//             Module.ctx = Module.canvas.getContext("2d");
//             devicePixelRatio = 1; // fight me
//             Module.canvas.width = window.innerWidth;
//             Module.canvas.height = window.innerHeight;

//             function Draw()
//             {
//                 Module._Render($0);
//                 requestAnimationFrame(Draw);
//             }
//             Draw();
//         }, this);
// #endif
    }

    void Renderer::Clear()
    {
// #ifndef WASM_BUILD
        m_Canvas->clear(0);
// #else
//         EM_ASM({
//             Module.ctx.setTransform(1, 0, 0, 1, 0, 0);
//             Module.ctx.clearRect(0, 0, Module.canvas.width, Module.canvas.height);
//         });
// #endif
    }

    void Renderer::Translate(float x, float y)
    {
// #ifndef WASM_BUILD
        m_Canvas->translate(x, y);
// #else
//         EM_ASM({
//             Module.ctx.translate($0, $1);
//         }, x, y);
// #endif
    }

    void Renderer::Scale(float x, float y)
    {
// #ifndef WASM_BUILD
        m_Canvas->scale(x, y);
// #else
//         EM_ASM({
//             Module.ctx.scale($0, $1);
//         }, x, y);
// #endif
    }

    void Renderer::Save()
    {
// #ifndef WASM_BUILD
        m_Canvas->save();
// #else
//         EM_ASM({
//             Module.ctx.save();
//         });
// #endif
    }

    void Renderer::Restore()
    {
// #ifndef WASM_BUILD
        m_Canvas->restore();
// #else
//         EM_ASM({
//             Module.ctx.restore();
//         });
// #endif
    }

    void Renderer::DrawCircle(float x, float y, float size, Paint const &paint)
    {
// #ifndef WASM_BUILD
        SkPaint skPaint;
        skPaint.setStyle(static_cast<SkPaint::Style>(paint.m_Style));
        skPaint.setStrokeWidth(paint.m_StrokeWidth);
        skPaint.setAntiAlias(paint.m_AntiAliased);
        skPaint.setColor(SkColorSetARGB(paint.m_Alpha, paint.m_Red, paint.m_Blue, paint.m_Green));
        m_Canvas->drawCircle(x, y, size, skPaint);
// #else
//         EM_ASM({
//             Module.ctx.save();
//             Module.ctx.lineWidth = $1;
//             Module.ctx.fillStyle = Module.ctx.strokeStyle = "rgba(" + $1 + "," + $2 + "," + $3 + "," + $4 + ")";
//             Module.ctx.beginPath();
//             Module.ctx.arc($5, $6, $7, 0, 2*Math.PI);
//             if ($8 % 2 === 0) Module.ctx.fill();
//             if ($8 > 0) Module.ctx.stroke();
//             Module.ctx.restore();
//         }, paint.m_StrokeWidth, paint.m_Red, paint.m_Green, paint.m_Blue, paint.m_Alpha, x, y, size, (uint8_t)paint.m_Style);
// #endif
    }

    void Renderer::Render()
    {
        Clear();
        Save();
        Translate(400, 250);
        Paint paint;
        paint.m_Red = 0xff;
        DrawCircle(0, 0, 100, paint);
        Restore();
    }
}
