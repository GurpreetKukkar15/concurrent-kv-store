# Concurrent Persistent Key-Value Store

A from-scratch key-value storage server written in C on Linux to explore
TCP networking, concurrent request processing, persistence, crash recovery,
and systems performance.

> **Status:** Work in progress. The current milestone implements a single-client
> TCP request/response path over IPv4 loopback. A client connects to the server,
> sends `HELLO`, receives `OK`, and both sides perform explicit socket cleanup.

## Current Progress

- [x] IPv4 TCP socket creation
- [x] Server address configuration
- [x] `bind()` and `listen()`
- [x] Blocking `accept()`
- [x] Client `connect()`
- [x] Bidirectional `send()` / `recv()`
- [x] Connection shutdown and socket cleanup
- [ ] Persistent server accept loop
- [ ] Application protocol and message framing
- [ ] `SET`, `GET`, and `DELETE`
- [ ] Custom hash table
- [ ] Concurrent request processing / thread pool
- [ ] Write-ahead log
- [ ] Crash recovery
- [ ] Retry/deduplication semantics
- [ ] Fault injection
- [ ] Benchmarking and profiling