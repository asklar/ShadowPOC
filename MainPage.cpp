#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::ShadowPOC::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

        const auto uiVisual = Hosting::ElementCompositionPreview::GetElementVisual(myButton());
        const auto compositor = uiVisual.Compositor();

        auto panel = myButton().Parent().as<Panel>();
        Grid g{};
        uint32_t index{ };
        panel.Children().IndexOf(myButton(), index);
        panel.Children().SetAt(index, g);

        auto visual = compositor.CreateSpriteVisual();
        visual.Size(myButton().ActualSize());

        const auto dropShadow = compositor.CreateDropShadow();
        dropShadow.BlurRadius(8.f);
        dropShadow.Color(Windows::UI::Colors::PaleVioletRed());

        visual.Shadow(dropShadow);
        Border border{};
        border.Width(myButton().ActualWidth() + 16);
        border.Height(myButton().ActualHeight() + 16);

        Hosting::ElementCompositionPreview::SetElementChildVisual(border, visual);

        g.Children().Append(border);
        g.Children().Append(myButton());

    }
}
