/*
 * Copyright © 2012 Canonical Ltd.
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
 * Authored by:
 * Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_COMPOSITOR_BUFFER_QUEUE_H_
#define MIR_COMPOSITOR_BUFFER_QUEUE_H_

#include "buffer.h"
#include "buffer_ipc_package.h"
#include <memory>

namespace mir
{
namespace compositor
{

struct GraphicBufferClientResource
{
    GraphicBufferClientResource(
        std::shared_ptr<BufferIPCPackage> const& ipc_package,
        std::shared_ptr<compositor::Buffer> const& buffer) :
            ipc_package(ipc_package), buffer(buffer)
    {
    }

    std::shared_ptr<BufferIPCPackage> const ipc_package;
    std::shared_ptr<compositor::Buffer> const buffer;
};

class BufferQueue
{
public:
    virtual ~BufferQueue() {};
    virtual std::shared_ptr<GraphicBufferClientResource> secure_client_buffer() = 0;
};

}
}

#endif /* MIR_COMPOSITOR_BUFFER_QUEUE_H_ */
