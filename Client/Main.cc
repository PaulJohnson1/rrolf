#include <iostream>
#include <unistd.h>

#ifndef EMSCRIPTEN
#define SK_GL
#define SK_GANESH
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkMatrix.h>
#include <skia/include/core/SkColorSpace.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/GrBackendSurface.h>
#endif

#include <BinaryCoder/BinaryCoder.hh>
#include <BinaryCoder/NativeTypes.hh>

#include <Client/Simulation.hh>
#include <Client/Socket.hh>
#include <Client/Renderer.hh>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        g_InputData->m_KeysPressed[key] = 1; // mouse is a global that shouldn't be tied to the renderer alr that works too
    else if (action == GLFW_RELEASE)
        g_InputData->m_KeysPressed[key] = 0;
}
void GlfwMouseCallback(GLFWwindow *window, int button, int action, int mods)
{
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    g_InputData->m_MouseX = (float)x;
    g_InputData->m_MouseY = (float)y;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
        g_InputData->m_MouseButtons |= 1;
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        g_InputData->m_MouseButtons |= 2;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        g_InputData->m_MouseButtons |= 4;
}
#endif

extern "C"
{
    void __Renderer_KeyEvent(uint8_t op, int32_t key)
    {
        if (op == 1)
            g_InputData->m_KeysPressed[key] = 1;
        else if (op == 0)
        {
            g_InputData->m_KeysPressed[key] = 0;
            if (key >= 48 && key <= 57)
            {
                static uint8_t outgoingInputPacket[16];
                bc::BinaryCoder coder{outgoingInputPacket};
                coder.Write<bc::Uint8>(2);
                coder.Write<bc::Uint8>(key - 48);
                g_Simulation->m_Socket->SendPacket(coder.Data(), coder.At());
            }
        }
    }
    void __Renderer_MouseEvent(float x, float y, uint8_t state, uint8_t button)
    {
        g_InputData->m_MouseX = x;
        g_InputData->m_MouseY = y;
        g_InputData->m_State = state;
        if (state == 1) //press down
            g_InputData->m_MouseButtons |= (1 << button);
        else if (state == 0)
            g_InputData->m_MouseButtons &= ~(1 << button);
    }
    void __Renderer_Render(int32_t width, int32_t height, float devicePixelRatio)
    {
        if (!g_Renderer)
            return;
        g_Renderer->SetSize(width, height);
        float a = g_Renderer->m_Height / 1080;
        float b = g_Renderer->m_Width / 1920;
        g_Renderer->m_WindowScale = b < a ? a : b;
        g_Renderer->m_Container.m_X = width * 0.5f / g_Renderer->m_WindowScale;
        g_Renderer->m_Container.m_Y = height * 0.5f / g_Renderer->m_WindowScale;
        g_Renderer->m_Container.m_Width = width / g_Renderer->m_WindowScale;
        g_Renderer->m_Container.m_Height = height / g_Renderer->m_WindowScale;
        g_Simulation->TickRenderer();
        //g_Renderer->SetTransform(1, 0, 0, 1, width * 0.5f, height * 0.5f);
        g_Renderer->ResetTransform();
        g_Renderer->m_Container.Render();
    }
}

// #include <fenv.h>
void Initialize()
{
#ifndef EMSCRIPTEN
    // 16:9 aspect ratio for 500 height
    g_Renderer->m_Width = 889;
    g_Renderer->m_Height = 500;
    glfwSetErrorCallback([](int error, char const *description)
                         { std::cerr << "code " << error << ' ' << description << '\n'; });
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(g_Renderer->m_Width, g_Renderer->m_Height, "rrolf native client", NULL, NULL);
    glfwSetKeyCallback(window, GlfwKeyCallback);
    glfwSetMouseButtonCallback(window, GlfwMouseCallback);

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
    GrBackendRenderTarget backendRenderTarget(g_Renderer->m_Width, g_Renderer->m_Height,
                                              0, // sample count
                                              0, // stencil bits
                                              framebufferInfo);
    SkSurface *surface = SkSurface::MakeFromBackendRenderTarget(context, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
    g_Renderer->m_Canvas = surface->getCanvas();

    while (!glfwWindowShouldClose(window))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        context->flush();
        g_Renderer->m_Container.m_Width = g_Renderer->m_Width;
        g_Renderer->m_Container.m_Height = g_Renderer->m_Height;
        float a = g_Renderer->m_Height / 1080;
        float b = g_Renderer->m_Width / 1920;
        g_Renderer->m_WindowScale = b < a ? a : b;
        g_Simulation->TickRenderer();
        g_Renderer->ResetTransform();
        g_Renderer->m_Container.Render();
        g_InputData->m_MouseButtons = 0;
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
#else
    EM_ASM({
        document.oncontextmenu = function() { return false; };
        Module.canvas = document.createElement("canvas");
        Module.canvas.id = "canvas";
        document.body.appendChild(Module.canvas);
        Module.ctxs = [Module.canvas.getContext('2d')];
        Module.availableCtxs = new Array(100).fill(0).map(function(_, i) { return i; });
        window.addEventListener(
            "keydown", function({which}) { Module.___Renderer_KeyEvent(1, which); });
        window.addEventListener(
            "keyup", function({which}) { Module.___Renderer_KeyEvent(0, which); });
        window.addEventListener("mousedown", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 1, button)});
        window.addEventListener("mousemove", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 2, button)});
        window.addEventListener("mouseup", function({clientX, clientY, button}){Module.___Renderer_MouseEvent(clientX*devicePixelRatio, clientY*devicePixelRatio, 0, button)});
        Module.paths = [... Array(100)].fill(null);
        Module.availablePaths = new Array(100).fill(0).map(function(_, i) { return i; });
        Module.addPath = function()
        {
            if (Module.availablePaths.length)
            {
                const index = Module.availablePaths.pop();
                Module.paths[index] = new Path2D();
                return index;
            }
            throw new Error('Out of Paths: Can be fixed by allowing more paths');
            return -1;
        };
        Module.removePath = function(index)
        {
            Module.paths[index] = null;
            Module.availablePaths.push(index);
        };
        Module.addCtx = function()
        {
            if (Module.availableCtxs.length)
            {
                const index = Module.availableCtxs.shift();
                if (index == 0)
                    return 0; // used for the main ctx, because that has special behavior
                const ocanvas = new OffscreenCanvas(0, 0);
                Module.ctxs[index] = ocanvas.getContext('2d');
                return index;
            }
            throw new Error('Out of Contexts: Can be fixed by allowing more contexts');
            return -1;
        };
        Module.removeCtx = function(index)
        {
            if (index == 0)
                throw new Error('Tried to delete the main context');
            Module.ctxs[index] = null;
            Module.availableCtxs.push(index);
        };
        Module.ReadCstr = function(ptr)
        {
            let str = "";
            let char;
            while ((char = Module.HEAPU8[ptr++]))
                str += String.fromCharCode(char);
            return str;
        };
        function loop()
        {
            requestAnimationFrame(loop);
            Module.canvas.width = innerWidth * devicePixelRatio;
            Module.canvas.height = innerHeight * devicePixelRatio;
            Module.___Renderer_Render(Module.canvas.width, Module.canvas.height, devicePixelRatio);
        };
        requestAnimationFrame(loop);
    });
#endif
}
int main()
{
    // feenableexcept(FE_INVALID);
    using namespace app;

#ifdef EMSCRIPTEN
    Initialize();
#endif
    // heap allocate so the dtor doesn't automatically get called
    static Renderer *renderer = new Renderer();
    Renderer *test = new Renderer();
    static InputData *mouse = new InputData();
    g_Simulation = new Simulation(renderer);
    static Socket *socket = new Socket(
        "ws://localhost:8000", [&]()
        { std::cout << "open\n"; },
        [&]()
        { std::cout << "close\n"; },
        [&](uint8_t *m)
        {
            g_Simulation->ReadBinary(m);
            static uint8_t outgoingInputPacket[16];
            bc::BinaryCoder coder{outgoingInputPacket};
            coder.Write<bc::Uint8>(0);
            coder.Write<bc::Uint8>(0); // keyboard movement
            uint8_t movementFlags = 0;
            movementFlags |= (mouse->m_KeysPressed[87] || mouse->m_KeysPressed[38]) << 0;
            movementFlags |= (mouse->m_KeysPressed[65] || mouse->m_KeysPressed[37]) << 1;
            movementFlags |= (mouse->m_KeysPressed[83] || mouse->m_KeysPressed[40]) << 2;
            movementFlags |= (mouse->m_KeysPressed[68] || mouse->m_KeysPressed[39]) << 3;
            movementFlags |= mouse->m_MouseButtons << 4;
            coder.Write<bc::Uint8>(movementFlags);

            socket->SendPacket(coder.Data(), coder.At());
        });
    g_Simulation->m_Socket = socket;
#ifdef EMSCRIPTEN
    std::cout << "wasm init " << __TIME__ << '\n';
#else
    std::thread([&]()
                { Initialize(); })
        .detach();
#endif

    socket->Connect();
}