/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "src/platform/graphics/android/device_detector.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace mga = mir::graphics::android;

namespace
{
struct MockOps : mga::PropertiesWrapper
{
    MOCK_CONST_METHOD3(property_get, int(
        char const[PROP_NAME_MAX], char[PROP_VALUE_MAX], char const[PROP_VALUE_MAX]));
};
}

TEST(DeviceDetection, two_buffers_by_default)
{
    using namespace testing;
    char const default_str[] = "";
    char const name_str[] = "anydevice";

    MockOps mock_ops;
    EXPECT_CALL(mock_ops, property_get(StrEq("ro.product.device"), _, StrEq(default_str)))
        .Times(1)
        .WillOnce(Invoke([&]
        (char const*, char* value, char const*)
        {
            strncpy(value, name_str, PROP_VALUE_MAX);
            return 0;
        }));

    mga::DeviceQuirks detector(mock_ops);
    EXPECT_EQ(2u, detector.num_framebuffers());
}

TEST(DeviceDetection, three_buffers_reported_for_mx3)
{
    using namespace testing;
    char const default_str[] = "";
    char const name_str[] = "mx3";

    MockOps mock_ops;
    EXPECT_CALL(mock_ops, property_get(StrEq("ro.product.device"), _, StrEq(default_str)))
        .Times(1)
        .WillOnce(Invoke([&]
        (char const*, char* value, char const*)
        {
            strncpy(value, name_str, PROP_VALUE_MAX);
            return 0;
        }));

    mga::DeviceQuirks detector(mock_ops);
    EXPECT_EQ(3u, detector.num_framebuffers());
}
