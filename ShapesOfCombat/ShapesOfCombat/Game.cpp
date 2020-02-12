
#include "pch.h"
#include "Game.h"

// this is the game's start function (only happens once)
void ShapesOfCombat::Initialize()
{
    // Define temporary pointers to a device and a device context
    ComPtr<ID3D11Device> dev11;
    ComPtr<ID3D11DeviceContext> devcon11;

    // Create the device and device context objects
    // Its job is to initialize Direct3D and to create the device and device context objects.
    // As simple as its job is, it has many parameters, but it's not hard to use.
    D3D11CreateDevice(
        nullptr,                            // IDXGIAdapter* Adapter: describes teh graphics adapter
        D3D_DRIVER_TYPE_HARDWARE,           // D3D_DRIVER_TYPE DriverType: six possible params, we use HARDWARE to use acclerated graphics
        nullptr,                            // HMODULE Software: This parameter is where we include that software engine.
        0,                                  // UINT Flags: None of the flags that this function accepts are useful to us right now
        nullptr,                            // D3D_FEATURE_LEVEL* pFeatureLevels: This parameter allows you to create a list of feature levels. This list tells Direct3D what features you are expecting your program to work with
        0,                                  // UINT FeatureLevels: This parameter indicates how many feature levels you had in your list. We'll just put 0.
        D3D11_SDK_VERSION,                  // UINT SDKVersion: This parameter is always the same: D3D11_SDK_VERSION because Each machine will usually have varying minor versions of DirectX. This tells the user's DirectX which version you developed your game for.
        &dev11,                             // ID3D11Device** ppDevice: This function will create the object for us, and the address of the interface will be stored in our smart pointer. 
        nullptr,                            // D3D_FEATURE_LEVEL* pFeatureLevel: This is a pointer to a feature level variable. When the function is completed, the variable will be filled with the flag of the highest feature level that was found.
        &devcon11);                         // ID3D11DeviceContext** ppImmediateContext:  It will then be filled with the address of the device context interface.

    // Convert the pointers from the DirectX 11 versions to the DirectX 11.1 versions
    {
        // The As() function is a member of the ComPtr class. Its job is to store the interface it represents into another ComPtr.
        dev11.As(&dev);
        devcon11.As(&devcon);
    }

}

// this is the games update function (happens repeatedly)
void ShapesOfCombat::Update()
{

}

// this is how the game renders info to screen (happens repeatedly)
void ShapesOfCombat::Render()
{

}