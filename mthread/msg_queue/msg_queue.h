//
// Created by skybcyang on 2022/7/12.
//

#ifndef SNIPPETS_MSG_QUEUE_H
#define SNIPPETS_MSG_QUEUE_H


#include <thread>

struct GeneralMsgHandler {

};


struct MsgQueue {
    MsgQueue() = default;
    ~MsgQueue() = default;
    MsgQueue(const MsgQueue&) = delete;
    MsgQueue& operator=(MsgQueue&) = delete;
    MsgQueue(MsgQueue&&) = delete;
    MsgQueue& operator=(MsgQueue&&) = delete;

private:
    std::thread m_thread;
};


#endif //SNIPPETS_MSG_QUEUE_H
