/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_GRAPHICS_BUFFER_IPC_PACKER_H_
#define MIR_GRAPHICS_BUFFER_IPC_PACKER_H_

#include <memory>

namespace mir
{
namespace graphics
{
enum class BufferIpcMsgType
{
    full_msg, //pack the full ipc representation of the buffer
    update_msg //assume the client has a full representation, and pack only updates to the buffer 
};
class Buffer;
class BufferIpcMessage;
struct PlatformIPCPackage;

class BufferIpcPacker
{
public:
    virtual ~BufferIpcPacker() = default;
    /**
     * Arranges the IPC package for a buffer that is to be sent through
     * the frontend from server to client. This should be called every
     * time a buffer is to be sent cross-process.
     *
     * The Buffer IPC message will be sent to clients when receiving a buffer.
     * The implementation must use the provided packer object to perform the packing.
     *
     * \param [in] message   the message that will be sent
     * \param [in] buffer    the buffer to be put in the message
     * \param [in] ipc_type what sort of ipc message is needed
     */
    virtual void pack_buffer(BufferIpcMessage& message, Buffer const& buffer, BufferIpcMsgType msg_type) const = 0;

    /**
     * Arranges the IPC package for a buffer that was sent over IPC
     * client to server. This must be called every time a buffer is
     * received, as some platform specific processing has to be done on
     * the incoming buffer.
     * \param [in] message   the message that was sent to the server
     * \param [in] buffer    the buffer associated with the message
     */
    virtual void unpack_buffer(BufferIpcMessage& message, Buffer const& buffer) const = 0;

    /**
     * Gets the connection package for the platform.
     *
     * The IPC package will be sent to clients when they connect.
     */
    virtual std::shared_ptr<PlatformIPCPackage> get_ipc_package() = 0;

protected:
    BufferIpcPacker() {}
    BufferIpcPacker(BufferIpcPacker const&) = delete;
    BufferIpcPacker& operator=(BufferIpcPacker const&) = delete;

};

}
}

#endif /* MIR_GRAPHICS_BUFFER_IPC_PACKER_H_ */
