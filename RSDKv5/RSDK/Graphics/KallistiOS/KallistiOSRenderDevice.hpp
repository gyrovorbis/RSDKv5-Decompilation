#pragma once
#define KOS_HARDWARE_RENDERER
using ShaderEntry = ShaderEntryBase; // DCFIXME

class RenderDevice : public RenderDeviceBase
{
public:
    struct WindowInfo {
        union {
            struct {
                int32 width;
                int32 height;
                int32 refresh_rate;
            };
        } * displays;
    };
    static WindowInfo displayInfo;

    static bool Init();
    static void CopyFrameBuffer();
    static void FlipScreen();
    static void Release(bool32 isRefresh);

    static void RefreshWindow();
    static void GetWindowSize(int32 *width, int32 *height);

    static void SetupImageTexture(int32 width, int32 height, uint8 *imagePixels);
    static void SetupVideoTexture_YUV420(int32 width, int32 height, uint8 *imagePixels);
    static void SetupVideoTexture_YUV422(int32 width, int32 height, uint8 *imagePixels);
    static void SetupVideoTexture_YUV424(int32 width, int32 height, uint8 *imagePixels);

    static bool ProcessEvents();

    static void InitFPSCap();
    static bool CheckFPSCap();
    static void UpdateFPSCap();

    // Public since it's needed for the ModAPI
    static void LoadShader(const char *fileName, bool32 linear);

    static void SetWindowTitle();
    static bool GetCursorPos(void*);
    static void ShowCursor(bool);

    // KallistiOS only!!!
    static void BeginScene();
    static void EndScene();
    static float GetDepth();
    static void SetDepth(uint32 depth);

#if defined(KOS_HARDWARE_RENDERER)
    static uint32 GetGamePaletteBankIndex(int32 y);
    static uint32 GameToPvrPaletteBankIndex(uint32 gamePaletteBankIndex);
    static void PopulatePvrPalette(uint32 gamePaletteBankIndex, uint32 pvrPaletteBankIndex);
    static bool InkToBlendModes(int inkEffect, int* srcBlend, int* dstBlend);

    static bool PreparePrimitive(int primitiveType,
                                 uint32 gamePaletteBankIndex,
                                 uint32 pvrPaletteBankIndex,
                                 int srcBlend,
                                 int dstBlend,
                                 pvr_ptr_t texture);

    static void PrepareTexturedQuad(int32 y, GFXSurface* surface);
    static void DrawTexturedQuad(
            int32 x, int32 y,
            int32 width, int32 height,
            int32 sprX0, int32 sprX1,
            int32 sprY0, int32 sprY1,
            GFXSurface* surface
    );

    static void PrepareTexturedPoly(int32 y, int srcBlend, int dstBlend, GFXSurface* surface);
    static void DrawTexturedPoly(
            int32 x, int32 y,
            int32 width, int32 height,
            int32 sprX0, int32 sprX1,
            int32 sprY0, int32 sprY1,
            GFXSurface* surface,
            int32 alpha
    );

    static void PrepareColoredPoly(int32 y, int srcBlend, int dstBlend);
    static void DrawColoredPoly(
            int32 x, int32 y,
            int32 width, int32 height,
            uint32 color
    );
#endif

private:
    static bool InitShaders();
    static bool SetupRendering();
    static void InitVertexBuffer();
    static bool InitGraphicsAPI();

    static void GetDisplays();
};
