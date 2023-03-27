#include <Client/Renderer.hh>

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

static app::Renderer *g_Renderer = nullptr;

#ifdef EMSCRIPTEN
#include <emscripten.h>

extern "C"
{
    void KeyEvent(uint8_t op, int32_t key)
    {
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

#include <Client/Simulation.hh>

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
#ifndef EMSCRIPTEN
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
            Module.paths = [...Array(100)].fill(null);
            Module.availablePaths = new Array(100).fill(0).map((_,i) => i);
            Module.addPath = _ => {
                if (Module.availablePaths.length) {
                    const index = Module.availablePaths.pop();
                    Module.paths[index] = new CanvasKit.Path();
                    return index;
                }
                throw new Error('Out of Paths: Can be fixed by allowing more paths');
            };
            Module.removePath = index => {
                Module.paths[index] = null;
                Module.availablePaths.push(index);
            };
            InitCanvas();
        });
    }
});
#endif
    }

    Renderer::ContextLock Renderer::AutoSaveRestore()
    {
        return Renderer::ContextLock(this);
    }

    Renderer::ContextLock::ContextLock(Renderer *renderer)
      : m_Renderer(renderer)
    {
        m_Renderer->Save();
    }

    Renderer::ContextLock::~ContextLock()
    {
        m_Renderer->Restore();
    }

    Renderer::Path::Path() 
    {
#ifdef EMSCRIPTEN
        m_Index = EM_ASM_INT({
            return Module.addPath();
        });
#endif
    }

    Renderer::Path::~Path()
    {
#ifdef EMSCRIPTEN
        EM_ASM({
            Module.availablePaths.push($0);
            Module.paths[$0] = null;
        }, m_Index);
#endif
    }

    void Renderer::Path::MoveTo(float x, float y)
    {
#ifndef EMSCRIPTEN
        m_Path.moveTo(x, y);
#else 
        EM_ASM({
            Module.paths[$0].moveTo($1, $2);
        }, m_Index, x, y);
#endif
    }
    
    void Renderer::Path::LineTo(float x, float y)
    {
#ifndef EMSCRIPTEN
        m_Path.lineTo(x, y);
#else
        EM_ASM({
            Module.paths[$0].lineTo($1, $2);
        }, m_Index, x, y);
#endif
    }

    void Renderer::Path::QuadTo(float x1, float y1, float x, float y)
    {
#ifndef EMSCRIPTEN
        m_Path.quadTo(x1, y1, x, y);
#else
        EM_ASM({
            Module.paths[$0].quadTo($1, $2, $3, $4);
        }, m_Index, x1, y1, x, y);
#endif
    }

    void Renderer::Path::Arc(float x, float y, float r, float sA, float eA)
    {
#ifndef EMSCRIPTEN
        m_Path.addArc(SkRect::MakeXYWH(x, y, r, r), sA, eA);
#else
        EM_ASM({
            Module.paths[$0].arc($1, $2, $3, $4, $5, false);
        }, m_Index, x, y, r, sA, eA);
#endif
    }
    void Renderer::Path::AddCircle(float x, float y, float r)
    {

    }
    void Renderer::Clear()
    {
#ifndef EMSCRIPTEN
        m_Canvas->clear(0);
#else
    EM_ASM({
        Module.canvas.clear(Module.CanvasKit.BLACK);
    });
#endif
    }

    void Renderer::Translate(float x, float y)
    {
#ifndef EMSCRIPTEN
        m_Canvas->translate(x, y);
#else
    EM_ASM({Module.canvas.translate($0, $1)}, x, y);
#endif
    }

    void Renderer::Scale(float x, float y)
    {
#ifndef EMSCRIPTEN
        m_Canvas->scale(x, y);
#else
    EM_ASM({Module.canvas.scale($0, $1)}, x, y);
#endif
    }

    void Renderer::Save()
    {
#ifndef EMSCRIPTEN
        m_Canvas->save();
#else
    EM_ASM({
        Module.canvas.save();
    });
#endif
    }

    void Renderer::Restore()
    {
#ifndef EMSCRIPTEN
        m_Canvas->restore();
#else
    EM_ASM({
        Module.canvas.restore();
    });
#endif
    }

    void Renderer::DrawCircle(float x, float y, float size, Paint const &paint)
    {
#ifndef EMSCRIPTEN
        SkPaint skPaint;
        skPaint.setStyle(static_cast<SkPaint::Style>(paint.m_Style));
        skPaint.setStrokeWidth(paint.m_StrokeWidth);
        skPaint.setAntiAlias(paint.m_AntiAliased);
        skPaint.setColor(SkColorSetARGB((paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255));
        m_Canvas->drawCircle(x, y, size, skPaint);
#else
    EM_ASM({
        const paint = new Module.CanvasKit.Paint();
        if ($0 == 0)
            paint.setStyle(Module.CanvasKit.PaintStyle.Fill);
        if ($0 == 1) 
        {
            paint.setStyle(Module.CanvasKit.PaintStyle.Stroke);
            paint.setStrokeWidth($3);
        };
        if ($1 == 0)
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Butt);
        else if ($1 == 1)
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Round);
        else
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Square);
        paint.setAntiAlias($4);
        paint.setColor(Module.CanvasKit.Color4f($6 / 255, $7 / 255, $8 / 255, $5 / 255));
        Module.canvas.drawCircle($9, $10, $11, paint);
    }, paint.m_Style, paint.m_Cap, paint.m_Join, paint.m_StrokeWidth, paint.m_AntiAliased, (paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255, x, y, size);
#endif
    }
    void Renderer::DrawLine(float x0, float y0, float x1, float y1, Paint const &paint)
    {
#ifndef EMSCRIPTEN
        SkPaint skPaint;
        skPaint.setStyle(static_cast<SkPaint::Style>(paint.m_Style));
        skPaint.setStrokeWidth(paint.m_StrokeWidth);
        skPaint.setAntiAlias(paint.m_AntiAliased);
        skPaint.setColor(SkColorSetARGB((paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255));
        m_Canvas->drawLine(x0, y0, x1, y1, skPaint);
#else
    EM_ASM({
        const paint = new Module.CanvasKit.Paint();
        if ($0 == 0)
            paint.setStyle(Module.CanvasKit.PaintStyle.Fill);
        if ($0 == 1) 
        {
            paint.setStyle(Module.CanvasKit.PaintStyle.Stroke);
            paint.setStrokeWidth($3);
        };
        if ($1 == 0)
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Butt);
        else if ($1 == 1)
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Round);
        else
            paint.setStrokeCap(Module.CanvasKit.StrokeCap.Square);
        paint.setAntiAlias($4);
        paint.setColor(Module.CanvasKit.Color4f($6 / 255, $7 / 255, $8 / 255, $5 / 255));
        Module.canvas.drawLine($9, $10, $11, $12, paint);
    }, paint.m_Style, paint.m_Cap, paint.m_Join, paint.m_StrokeWidth, paint.m_AntiAliased, (paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255, x0, y0, x1, y1);
#endif
    }
    void Renderer::DrawPath(Path const &path, Paint const &paint) 
    {
#ifndef EMSCRIPTEN
        SkPaint skPaint;
        skPaint.setStyle(static_cast<SkPaint::Style>(paint.m_Style));
        skPaint.setStrokeWidth(paint.m_StrokeWidth);
        skPaint.setAntiAlias(paint.m_AntiAliased);
        skPaint.setColor(SkColorSetARGB((paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255));
        m_Canvas->drawPath(path.m_Path, skPaint);
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
            paint.setColor(Module.CanvasKit.Color4f($4 / 255, $5 / 255, $6 / 255, $3 / 255));
            Module.canvas.drawPath(Module.paths[$7], paint);
        }, paint.m_Style, paint.m_StrokeWidth, paint.m_AntiAliased, (paint.m_Color >> 24) & 255, (paint.m_Color >> 16) & 255, (paint.m_Color >> 8) & 255, paint.m_Color & 255, path.m_Index);
#endif
    }
    void Renderer::ClipPath(Path const &path) 
    {
#ifndef EMSCRIPTEN
        m_Canvas->clipPath(path.m_Path, true);
#else
        EM_ASM({
            Module.canvas.clipPath(Module.paths[$0], Module.CanvasKit.ClipOp.Intersect, true);
        }, path.m_Index);
#endif
    }
    void Renderer::SetSize(int32_t width, int32_t height)
    {
#ifdef EMSCRIPTEN
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
