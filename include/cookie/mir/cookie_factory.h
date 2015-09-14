/*
 * Copyright © 2015 Canonical Ltd.
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
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#ifndef MIR_COOKIE_FACTORY_H_
#define MIR_COOKIE_FACTORY_H_

#include <vector>
#include <memory>
#include "mir_toolkit/common.h"
#include <nettle/hmac.h>

namespace mir
{
namespace cookie
{
/**
 * \brief A source of moderately-difficult-to-spoof cookies.
 *
 * The primary motivation for this is to provide event timestamps that clients find it difficult to spoof.
 * This is useful for focus grant and similar operations where shell behaviour should be dependent on
 * the timestamp of the client event that caused the request.
 *
 * Some spoofing protection is desirable; experience with X clients shows that they will go to some effort
 * to attempt to bypass focus stealing prevention.
 *
 */

// Using the NVI Idiom
class CookieFactory
{
public:
    CookieFactory() = default;
    virtual ~CookieFactory() noexcept = default;

    MirCookie timestamp_to_cookie(uint64_t const& timestamp);

    bool attest_timestamp(MirCookie const& cookie);

private:
    virtual void calculate_mac(MirCookie& cookie) = 0;
    virtual bool verify_mac(MirCookie const& cookie) = 0;
};

class CookieFactoryNettle : public CookieFactory
{
public:
    CookieFactoryNettle(std::vector<uint8_t> const& secret);
    virtual ~CookieFactoryNettle() noexcept;

private:
    virtual void calculate_mac(MirCookie& cookie) override;
    virtual bool verify_mac(MirCookie const& cookie) override;

    // The minimum secret size for which a resonable mac can be generated
    static unsigned const minimum_secret_size;

    // hmac context used to generate macs from libnettle
    struct hmac_sha1_ctx ctx;
};

std::vector<uint8_t> get_random_data(unsigned size);

}
}
#endif // MIR_COOKIE_FACTORY_H_
