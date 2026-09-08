# Distributed Data Pipeline Status

This repository is a focused C++17 concurrency prototype and performance-engineering exercise.

## Current scope

- Lock-free queue experimentation
- Worker-thread execution
- CMake build and GoogleTest validation
- Docker-based development
- GitHub Actions CI

## Evidence policy

Performance figures in the README are project benchmark results. They should be reproduced on a comparable machine before being presented as externally validated benchmarks.

## Next milestones

- Expand queue implementations and workload generators
- Add contention and scalability benchmarks
- Add latency/throughput reporting
- Add sanitizer jobs to CI
- Add profiling artifacts and reproducible benchmark commands
- Document memory-ordering decisions
