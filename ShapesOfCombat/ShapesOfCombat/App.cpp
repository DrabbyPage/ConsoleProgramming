// Include the precompiled headers
#include "pch.h"

// Use some common namespaces to simplify the code
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

// FOR MESSAGE DIALOGS/ OUTPUTTING STUFF
/*
Message Dialogs

At this point, we haven't learned any code that will let us draw anything on the window.
A very simple tool to let us do this is a message dialog, or message box. In WinRT, the
code to create a message dialog is obsurdly simple.

First, we create a MessageDialog object. The text of the dialog goes right in the 
constructor. Then we call the ShowAsync() function. And that's all!

// here is the dialogue:
    MessageDialog Dialog("Thank you for noticing this notice.", "Notice!");
    Dialog.ShowAsync();
*/

// the class definition for the core "framework" of our app
ref class App sealed : public IFrameworkView
{
    bool WindowClosed;    // change to true when it's time to close the window
public:
    // some functions called by Windows
    virtual void Initialize(CoreApplicationView^ AppView)
    {
        // set the OnActivated function to handle to Activated "event"
        AppView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

        // CoreApplication - This and one other event(the next one below) are called from CoreApplication, 
        // not the CoreWindow like we did last lesson.This is because in a multiple - window setup, 
        // the entire application must handle suspension in one place, not from each window.

        // EventHandler is similar to TypedEventHandler. It lacks the first template parameter, the one
        // we were passing CoreWindow^ into before.

        // The only template parameter this event uses is SuspendingEventArgs. It has only one member,
        // which is useful when saving data. I'll talk about it below.
        //CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &App::Suspending);

        // adding the resuming event
        //CoreApplication::Resuming += ref new EventHandler<Object^>(this, &App::Resuming);

        WindowClosed = false;    // initialize to false
    }

    virtual void SetWindow(CoreWindow^ Window)
    {
        // this is telling windows about the event "PointerPressed"
        Window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::PointerPressed);

        //  this is telling windows about the event "KeyDown" Event 
        Window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::KeyDown);

        // this tells windows about the "KeyUp" Event
        Window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::KeyUp);
    }

    virtual void Load(String^ EntryPoint) {}

    virtual void Run()
    {

        // Obtain a pointer to the window
        CoreWindow^ Window = CoreWindow::GetForCurrentThread();

        /*
        ProcessOneIfPresent	                Dispatch the next event waiting on the queue (if any).
        ProcessAllIfPresent	                Dispatch the next event waiting on the queue (if any) and repeat until all waiting events are handled, then return.
        ProcessOneAndAllPending	            Dispatch all waiting events. If there are none waiting, wait until another one arrives.
        ProcessUntilQuit	                Dispatch all events, and repeat. Do not return until Windows shuts the program down.
        */
        // Run ProcessEvents() to dispatch events
        //Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);

        while (!WindowClosed)
        {
            Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

            // run game code here
            // ...

        }
    }

    virtual void Uninitialize() {}

    // an "event" that is called when the application window is ready to be activated
    void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
    {
        CoreWindow^ Window = CoreWindow::GetForCurrentThread();
        Window->Activate();
    }

    // It occurs when you either click the mouse, or when the touchscreen is first touched with a pen or a finger.
    // pointer arguments:
    /*
    CurrentPoint Member	        Description
    Position.X	                The X-coordinate position (in pixels) of where the press occurs. 
                                If it is a finger touch, it is positioned at the center of the finger press.

    Position.Y	                The Y-coordinate position of where the press occurs.

    PointerID	                An integer that helps you keep track of touches. When you touch the screen 
                                or click, and then perform a drag, that entire motion is assigned this ID.
                                This helps you keep track of where a user is moving their mouse or finger.

    Properties	                This is a large class within CurrentPoint which gives you a host of additional
                                information about the touch. A table of available properties in this class can 
                                be found here.

    PointerDevice	            This is another large class within CurrentPoint which gives you lots of information
                                about the device that was used to make the touch. Here is a table of its properties.
    */
    void PointerPressed(CoreWindow^ Window, PointerEventArgs^ Args)
    {
        MessageDialog Dialog("Thank you for noticing this notice.", "Notice!");
        Dialog.ShowAsync();
    }

    void KeyDown(CoreWindow^ Window, KeyEventArgs^ Args)
    {
        // This code checks the keystroke associated with the event. If it's the 'A' key, it does
        // something. This can be an upper-case 'A' or a lower-case 'a'.
        // here are the virtual key enums:
        // https://docs.microsoft.com/en-us/uwp/api/Windows.System.VirtualKey?redirectedfrom=MSDN
        if (Args->VirtualKey == VirtualKey::A)
        {
            // do something...
        }
    }

    void KeyUp(CoreWindow^ Window, KeyEventArgs^ Args)
    {
        if (Args->VirtualKey == VirtualKey::A)
        {
            // do something...
        }
    }

    // This event triggers whenever you scroll the wheel on your mouse. It also uses PointerEventArgs.
    void PointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args)
    {
        int Wheel = args->CurrentPoint->Properties->MouseWheelDelta;
    }

    // If you are expected to save your game data when the game suspends, it's necessary for 
    // there to be a Suspending event. This event triggers when your app goes into Suspended state.
    void Suspending(Object^ Sender, SuspendingEventArgs^ Args)
    {
        // In this function, we would place code that saves the state of our game. 

    }

    // Like suspension, resuming a game has its own event. 
    void Resuming(Object^ Sender, Object^ Args)
    {

    }

};


// the class definition that creates an instance of our core framework class
ref class AppSource sealed : IFrameworkViewSource
{
public:
    virtual IFrameworkView^ CreateView()
    {
        return ref new App();    // create an App class and return it
    }
};

[MTAThread]    // define main() as a multi-threaded-apartment function

// the starting point of all programs
int main(Array<String^>^ args)
{
    CoreApplication::Run(ref new AppSource());    // create and run a new AppSource class
    return 0;
}
