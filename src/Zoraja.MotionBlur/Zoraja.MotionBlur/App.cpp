#include "pch.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

ref class App sealed : public IFrameworkView
{
public:

	bool WindowClosed;

	virtual void Initialize(CoreApplicationView^ AppView)
	{
		WindowClosed = false;

		AppView->Activated += ref new TypedEventHandler
			<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);

		CoreApplication::Suspending +=
			ref new EventHandler<SuspendingEventArgs^>(this, &App::Suspending);
		CoreApplication::Resuming +=
			ref new EventHandler<Object^>(this, &App::Resuming);
	}


	virtual void SetWindow(CoreWindow^ Window) 
	{

		Window->Closed += ref new TypedEventHandler
			<CoreWindow^, CoreWindowEventArgs^>(this, &App::Closed);

		Window->PointerPressed += ref new TypedEventHandler
			<CoreWindow^, PointerEventArgs^>(this, &App::PointerPressed);

		Window->KeyDown += ref new TypedEventHandler
			<CoreWindow^, KeyEventArgs^>(this, &App::KeyDown);
	}

	
	virtual void Load(String^ EntryPoint) {}

	
	virtual void Run() 
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();

		while (!WindowClosed)
		{
			Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// Run game code here
			// ...
			// ...
		}
	}


	virtual void Uninitialize() {}


	// Application event handlers
	void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}

	void Suspending(Object^ Sender, SuspendingEventArgs^ Args) {}
	void Resuming(Object^ Sender, Object^ Args) {}


	// Window event handlers
	void Closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
	{
		WindowClosed = true; 
	}

	void PointerPressed(CoreWindow^ Window, PointerEventArgs^ args)
	{
		MessageDialog Dialog("Thanks for playing the game!", "Hello there!");
		Dialog.ShowAsync();
	}

	void KeyDown(CoreWindow^ Window, KeyEventArgs^ Args)
	{
		//if (Args->VirtualKey == VirtualKey::A)
		//{
		//}
	}
};


ref class AppSource sealed : IFrameworkViewSource
{
	public: virtual IFrameworkView^ CreateView()
	{
		return ref new App();
	}
};

[MTAThread]
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());    
	return 0;
}
