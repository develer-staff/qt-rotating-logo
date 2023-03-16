#include <catch2/catch_test_macros.hpp>

#include <QSignalSpy>

#include <libcommon/applicationmodel.h>

TEST_CASE("ApplicationModel")
{
    using ApplicationModel = common::ApplicationModel;

    ApplicationModel model;

    SECTION("isRotating")
    {
        REQUIRE(model.isRotating() == false);
    }

    SECTION("setRotating")
    {
        QSignalSpy rotatingChanged(&model, &ApplicationModel::rotatingChanged);

        model.setRotating(true);

        REQUIRE(model.isRotating() == true);
        REQUIRE(rotatingChanged.count() == 1);
    }
}
