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
	virtual void Initialize(CoreApplicationView^ AppView)
	{
		AppView->Activated += ref new TypedEventHandler
			<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);
	}
	virtual void SetWindow(CoreWindow^ Window) 
	{
		Window->PointerPressed += ref new TypedEventHandler
			<CoreWindow^, PointerEventArgs^>(this, &App::PointerPressed);

		Window->KeyDown += ref new TypedEventHandler
			<CoreWindow^, KeyEventArgs^>(this, &App::KeyDown);
	}
	virtual void Load(String^ EntryPoint) {}
	virtual void Run() 
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
	}
	virtual void Uninitialize() {}

	void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
	{
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}

	void PointerPressed(CoreWindow^ Window, PointerEventArgs^ args)
	{
		MessageDialog Dialog("Thanks for playing the game!", "Hello there!");
		Dialog.ShowAsync();
	}

	void KeyDown(CoreWindow^ Window, KeyEventArgs^ Args)
	{
		if (Args->VirtualKey == VirtualKey::A)
		{
		}
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
