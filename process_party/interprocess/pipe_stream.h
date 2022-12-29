#ifndef PROCESS_PARTY_PIPE_STREAM_H
#define PROCESS_PARTY_PIPE_STREAM_H


namespace process_party::process {
    class pipe_stream {
    public:
        pipe_stream();

        int read_fd;
        int write_fd;
    };
}

#endif //PROCESS_PARTY_PIPE_STREAM_H
