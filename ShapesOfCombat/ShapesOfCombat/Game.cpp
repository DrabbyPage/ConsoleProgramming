
#include "pch.h"
#include "Game.h"

// this is the game's start function (only happens once)
void ShapesOfCombat::Initialize()
{
    // DIRECTX STUFF
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

    // It created the adapter object based on what it already knew about the hardware. If we can access that DXGIAdapter object, it will tell us the address of the factory.

    // First, convert our ID3D11Device1 into an IDXGIDevice1
    // For every ID3D11Device1 there is a corresponding IDXGIDevice1 that lets us access DXGI components
    ComPtr<IDXGIDevice1> dxgiDevice;
    dev.As(&dxgiDevice);

    // Second, use the IDXGIDevice1 interface to get access to the adapter
    // This could simply be described as the virtutal representation of the video card (assuming the video card is separate, and not built into the motherboard).
    ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(&dxgiAdapter);

    // Third, use the IDXGIAdapter interface to get access to the factory
    // This is the interface to our factory. From this interface we can create our swap chain. The 2 at the end indicates that this is version 2 of the interface. 
    ComPtr<IDXGIFactory2> dxgiFactory;

    // Calling GetParent() gets us access to the factory of our adapter and of the device. It has two parameters:
    // the type of interface we are obtaining, and a pointer to store the address in.
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

    /*
    Swap chain descriptions
    width: An integer value indicating the width of the swapchain buffers in pixels. You can use this to force your
           game into lower or higher resolutions than the screen shows by default. If you set it to 0, the swap 
           chain automatically sizes itself to the current window resolution.

    height: Same as the width but, you know, the height instead.

    scaling: Scaling is a special value with two possible choices: DXGI_SCALING_STRETCH and DXGI_SCALING_NONE.
             Choosing the stretch option only matters if you set a custom width and height. The swap chain
             will stretch the image to fill the entire screen (or shrink it to fit the screen, if you chose
             a larger resolution). If you choose the none option, the rendered images will just appear in
             the top-left corner of the window.

    BufferCount: BufferCount tells the swap chain how many buffers to create. We want one front buffer and one back 
                    buffer, so we'll typically put 2 in this value.

    Format: This tells the swap chain what format our pixels are stored in. In other words, what arrangement of bits
            are we using to store the various colors. here are the formats: http://msdn.microsoft.com/en-us/library/windows/desktop/bb173059(v=vs.85).aspx

    SampleDesc.Quality: This indicates the quality of the anti-aliasing.

    BufferUsage: This value is required, and it tells DXGI what this swap chain is to be used for. There's only one 
                 value we will probably ever use here, and that is DXGI_USAGE_RENDER_TARGET_OUTPUT.

    SwapEffect: This is another required value that we will probably never change. It tells DXGI what to do with 
                the buffers once they have been shown and are no longer of use.

    AlphaMode: This is a value that sets how semi-transparency works.

    Stereo: This is a boolean value which allows an advanced programmer to enable use of 3D glasses.

    Flags: Here we can place some even more advanced options.

    */
    // set up the swap chain description
    DXGI_SWAP_CHAIN_DESC1 scd = { 0 };
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // how the swap chain should be used
    scd.BufferCount = 2;                                  // a front buffer and a back buffer
    scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;              // the most common swap chain format
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;    // the recommended flip mode
    scd.SampleDesc.Count = 1;                             // disable anti-aliasing

    CoreWindow^ Window = CoreWindow::GetForCurrentThread();    // get the window pointer

    dxgiFactory->CreateSwapChainForCoreWindow(
        dev.Get(),                                  // IUnknown* pDevice:  IUnknown is COM-speak for any COM object. It's trusting us to provide the right type of object (a device).
        reinterpret_cast<IUnknown*>(Window),        // IUnknown* pWindow: The next parameter is a pointer to a COM object representing the window. 
        &scd,                                       // DXGI_SWAP_CHAIN_DESC1* pDesc:  It's the address of the swap chain description struct.
        nullptr,                                    // IDXGIOutput* pRestrictToOutput: This is an advanced parameter that allows us to restrict graphics to a specific monitor in a multi-monitor system. We want the user to pick any monitor they choose, so we'll put nullptr here.
        &swapchain);                                // IDXGISwapChain1** ppSwapChain): we place a pointer to the swapchain ComPtr we defined earlier.
                                                      
               
               
               
               

}

// this is the games update function (happens repeatedly)
void ShapesOfCombat::Update()
{

}

// this function renders a single frame of 3D graphics
void ShapesOfCombat::Render()
{
    // switch the back buffer and the front buffer
    swapchain->Present(1, 0);
}