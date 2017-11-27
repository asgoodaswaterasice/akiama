#ifndef AKIAMA_RPC_RPCSERVER_H
#define AKIAMA_RPC_RPCSERVER_H

namespace akiama {
namespace rpc {

class RPCServer {
public:
    virtual void start() = 0;
    virtual void shutdown() = 0;
};

}; // end of ns rpc 
}; // end of ns akiama

#endif
