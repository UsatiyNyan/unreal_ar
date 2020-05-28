//
// Created by kira on 5/27/20.
//

#ifndef SMACH_LIB_UDP_INCLUDE_UDP_DATA_STREAM_H_
#define SMACH_LIB_UDP_INCLUDE_UDP_DATA_STREAM_H_

#include "udp_connection.h"
#include <vector>
#include <algorithm>
#include <iostream>

namespace udp {
template <typename T>
class DataStream {
    using Iterator = typename std::vector<T>::iterator;
 public:
    explicit DataStream(Connection &connection) : _connection(connection), _buffer(MAX_LEN, 0) {}
    void find(const T &key) {
        do {
            _connection.read_exact(_buffer.data(), MAX_LEN);
            size_t pos = _stream.size();
            _stream.insert(_stream.end(), _buffer.begin(), _buffer.end());
            _current_iterator = _stream.begin();
            std::advance(_current_iterator, pos);
            _current_iterator = std::find(_current_iterator, _stream.end(), key);
        } while (_current_iterator == _stream.end());
    }
    T &next() {
        ++_current_iterator;
        if (_current_iterator == _stream.end()) {
            size_t pos = _stream.size();
            _connection.read_exact(_buffer.data(), MAX_LEN);
            _stream.insert(_stream.end(), _buffer.begin(), _buffer.end());
            _current_iterator = _stream.begin();
            std::advance(_current_iterator, pos);
        }
        return *_current_iterator;
    }
    std::vector<T> retrieve() {
        Iterator buf_it = _current_iterator;
        std::vector<T> buffer{_stream.begin(), --buf_it};
        _stream.erase(_stream.begin(), buf_it);
        size_t size = _stream.size();
        T first = _stream[0];
        return std::move(buffer);
    }
 private:
    Connection &_connection;
    std::vector<T> _buffer;
    std::vector<T> _stream;
    Iterator _current_iterator{_stream.end()};
};
}  // namespace udp

#endif //SMACH_LIB_UDP_INCLUDE_UDP_DATA_STREAM_H_
