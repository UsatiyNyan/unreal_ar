//
// Created by kira on 07.03.2020.
//

#include <unistd.h>
#include <sys/wait.h>

#include "process.h"
#include "base_exception.h"
#include "file_descriptor.h"


using exception::Exception;

namespace process {
Process::Process(const std::string &path) : _status(), _pid(), _readable(true) {
    fd::Pipe pipein;
    fd::Pipe pipeout;
    _pid = fork();
    if (_pid == -1) {
        throw Exception("process was not created");
    }
    if (_pid == 0) {
        fd::FileDescriptor fd_in(fd::READ);
        fd::FileDescriptor fd_out(fd::WRITE);

        pipein.read().link(fd_in);
        pipeout.write().link(fd_out);

        pipein.read().close();
        pipein.write().close();
        pipeout.read().close();
        pipeout.write().close();

        execlp(path.c_str(), path.c_str(), nullptr);
        throw Exception("binary haven't executed");
    } else {
        pipein.read().close();
        pipeout.write().close();
        _pipein = pipein.write();
        _pipeout = pipeout.read();
    }
}

Process::~Process() {
    close();
    waitpid(_pid, &_status, 0);
}

size_t Process::write(const void *data, size_t len) {
    ssize_t written = ::write(_pipein.get(), data, len);
    if (written == -1) {
        throw Exception("write error");
    }
    return written;
}

void Process::write_exact(const void *data, size_t len) {
    size_t written = 0;
    while (len != written) {
        written += write(static_cast<const char *>(data) + written, len - written);
    }
}

size_t Process::read(void *data, size_t len) {
    ssize_t read_n = ::read(_pipeout.get(), data, len);
    if (read_n <= 0) {
        _readable = false;
    }
    if (read_n == -1) {
        throw Exception("read error");
    }
    return read_n;
}

void Process::read_exact(void *data, size_t len) {
    size_t read_n = 0;
    while (len != read_n && _readable) {
        read_n += read(static_cast<char *>(data) + read_n, len - read_n);
    }
}

bool Process::is_readable() const {
    return _readable;
}

void Process::close_stdin() {
    _pipein.close();
}

void Process::close() {
    _pipein.close();
    _pipeout.close();
    ::kill(_pid, SIGTERM);
}
}  // namespace process
