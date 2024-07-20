#include <Application.h>

#include <Service/DataManagerService.h>
#include <Utils/ServiceLocator.h>

#include <UI/Map/MapWindow.h>
#include <UI/DataTable/DataTableWindow.h>

int main(int, char**)
{
    auto* dataManager = new DataManagerService();
    ServiceLocator::provide(dataManager);

    Application app("My Test App",1280, 720);

    if (const std::shared_ptr<Data> data = dataManager->openFile("C:/Users/Aashik/Downloads/geographic-units-by-industry-and-statistical-area-20002023-descending-order-/stations.geojson"); data->isValid())
    {
        auto tableWindow = std::make_unique<DataTableWindow>(data);
        app.registerUi(std::move(tableWindow));
    }

    // app.setOnDropListener([&](const Paths& paths)
    // {
    //     for (const auto& path : paths)
    //     {
    //         if (const std::shared_ptr<Data> data = dataManager->openFile(path); data->isValid())
    //         {
    //             auto tableWindow = std::make_unique<DataTableWindow>(data);
    //             app.registerUi(std::move(tableWindow));
    //         }
    //     }
    // });

    // auto mapWindow = std::make_unique<MapWindow>();
    // app.registerUi(std::move(mapWindow));

    app.setOnRenderListener( [&]()
    {

    });

    return app.exec();
}
