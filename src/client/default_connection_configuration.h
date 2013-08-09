/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#ifndef MIR_CLIENT_DEFAULT_CONNECTION_CONFIGURATION_H_
#define MIR_CLIENT_DEFAULT_CONNECTION_CONFIGURATION_H_

#include "connection_configuration.h"

#include "mir/cached_ptr.h"

#include <string>

namespace mir
{
namespace client
{

namespace rpc
{
class RpcReport;
}

class DefaultConnectionConfiguration : public ConnectionConfiguration
{
public:
    DefaultConnectionConfiguration(std::string const& socket_file);

    std::shared_ptr<SurfaceMap> the_surface_map();
    std::shared_ptr<rpc::MirBasicRpcChannel> the_rpc_channel();
    std::shared_ptr<mir::logging::Logger> the_logger();
    std::shared_ptr<ClientPlatformFactory> the_client_platform_factory();
    std::shared_ptr<input::receiver::InputPlatform> the_input_platform();
    std::shared_ptr<DisplayConfiguration> the_display_configuration();

    virtual std::string the_socket_file();
    virtual std::shared_ptr<rpc::RpcReport> the_rpc_report();

protected:
    CachedPtr<rpc::MirBasicRpcChannel> rpc_channel;
    CachedPtr<mir::logging::Logger> logger;
    CachedPtr<ClientPlatformFactory> client_platform_factory;
    CachedPtr<input::receiver::InputPlatform> input_platform;
    CachedPtr<SurfaceMap> surface_map;
    CachedPtr<DisplayConfiguration> display_configuration;

    CachedPtr<rpc::RpcReport> rpc_report;

private:
    std::string const socket_file;
};

}
}

#endif /* MIR_CLIENT_DEFAULT_CONNECTION_CONFIGURATION_H_ */
