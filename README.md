# Distributed Data Pipeline

> C++17 concurrency and performance-engineering laboratory focused on **lock-free communication, work stealing, memory behavior, and measurable throughput**.

The project explores how scheduler design, synchronization, cache locality, and memory management affect high-throughput CPU workloads.

## Architecture

```text
                 Producers
                    │
                    ▼
          ┌──────────────────┐
          │ Lock-Free Queue  │
          └────────┬─────────┘
                   │
                   ▼
        ┌─────────────────────┐
        │ Worker Thread Pool  │
        │ + Work Stealing     │
        └──────────┬──────────┘
                   │
                   ▼
           Result Aggregation
                   │
                   ▼
                Output
```

Python handles orchestration and benchmark automation; performance-critical execution remains in C++.

## What it demonstrates

- Lock-free SPSC/MPSC-style queue design
- Work-stealing scheduling
- Multi-threaded task execution
- Memory and resource management
- Stress and concurrency testing
- Benchmark-driven optimization
- Reproducible Dockerized development
- CI validation with GitHub Actions

## Performance

Reported project results include:

- **100,000+ tasks** processed per execution
- **40% throughput improvement** over the baseline implementation
- **25% lower CPU utilization** while maintaining throughput
- **Zero memory leaks detected** during Valgrind validation

Treat these as project benchmark results; reproduce the benchmark locally before using them as externally validated performance claims.

## Why these techniques?

### Lock-free queues
Reduce mutex contention on high-frequency producer/consumer paths.

### Work stealing
Allow idle workers to acquire work from busy workers instead of relying on static partitioning.

### Cache-aware design
Data placement and access patterns can dominate performance once synchronization overhead is reduced.

### Profiling first
Optimization is driven by `perf`, Valgrind, benchmarks, and regression checks rather than intuition.

## Testing

The test strategy covers:

- Queue correctness
- Scheduler behavior
- Thread-safety scenarios
- Edge cases
- Stress workloads
- Benchmark regression

**Framework:** GoogleTest

## Tooling

**Languages:** C++17 · Python  
**Build:** CMake  
**Testing:** GoogleTest  
**Profiling:** Linux perf · Valgrind  
**Environment:** Docker  
**CI:** GitHub Actions

## Repository structure

```text
src/         # concurrency and pipeline implementation
tests/       # automated tests
benchmarks/  # performance workloads
scripts/     # orchestration / benchmark tooling
docs/        # design notes
.github/     # CI workflows
```

Use the repository tree as the source of truth for the current implementation.

## Engineering takeaways

1. Contention can dominate an otherwise efficient algorithm.
2. Work distribution matters as much as raw worker count.
3. Cache locality becomes increasingly important in throughput-sensitive systems.
4. Performance improvements are only useful when correctness survives concurrency.

## Status

🚧 Active systems-engineering project.

## Author

**Naga Lokesh Sai Alla**  
[GitHub](https://github.com/lokesh8286235) · [LinkedIn](https://linkedin.com/in/naga-lokesh-sai-alla-538242251) · [Portfolio](https://portfolio-r7n2.vercel.app)
