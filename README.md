# Distributed Data Pipeline

> C++17 concurrency and performance-engineering laboratory focused on **lock-free communication, work stealing, memory behavior, correctness, and measurable throughput**.

This project explores how scheduler design, synchronization, cache locality, and memory management shape high-throughput CPU workloads. Python is used for orchestration and benchmark automation; performance-critical execution remains in C++.

## Why this project stands out

This is deliberately systems-oriented rather than framework-oriented. The core questions are:

- Where does contention become the bottleneck?
- How should work move between workers under uneven load?
- How do synchronization and memory behavior affect throughput?
- Can an optimization improve performance without weakening concurrency correctness?

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

## What it demonstrates

| Area | Evidence |
|---|---|
| Concurrency | Lock-free queue patterns, worker threads, work stealing |
| Performance | Benchmark-driven optimization and throughput measurement |
| Correctness | GoogleTest, stress workloads, edge-case coverage |
| Memory | Explicit resource management and Valgrind validation |
| Profiling | Linux `perf` and benchmark analysis |
| Reproducibility | CMake + Docker + scripted benchmarks |
| Engineering discipline | GitHub Actions CI and regression checks |

## Performance

Reported project benchmark results include:

- **100,000+ tasks** processed per execution
- **40% throughput improvement** over the baseline implementation
- **25% lower CPU utilization** while maintaining throughput
- **Zero memory leaks detected** during Valgrind validation

These are **project benchmark results**. Reproduce the benchmark locally before treating them as externally validated performance claims.

## Optimization approach

```text
Baseline
   │
   ▼
Profile with perf / benchmarks
   │
   ▼
Identify contention / scheduling / memory bottleneck
   │
   ▼
Change one design variable
   │
   ▼
Run correctness + stress tests
   │
   ▼
Benchmark against baseline
   │
   ▼
Keep only measured improvements
```

## Key design choices

### Lock-free communication
Reduce mutex contention on high-frequency producer/consumer paths where the workload benefits from non-blocking coordination.

### Work stealing
Allow idle workers to acquire work from busy workers instead of depending entirely on static partitioning.

### Cache-aware thinking
Once synchronization overhead falls, data placement and access patterns can become dominant contributors to runtime.

### Profile first
Optimization is driven by measurements from `perf`, Valgrind, benchmarks, and regression checks rather than intuition.

## Testing strategy

The test plan covers:

- Queue correctness
- Scheduler behavior
- Thread-safety scenarios
- Edge cases
- Stress workloads
- Benchmark regression
- Memory validation

**Framework:** GoogleTest

## Repository structure

```text
src/         # concurrency and pipeline implementation
tests/       # automated correctness and stress tests
benchmarks/  # performance workloads and comparisons
scripts/     # orchestration / benchmark tooling
docs/        # design notes
.github/     # CI workflows
```

## Tooling

**Languages:** C++17 · Python  
**Build:** CMake  
**Testing:** GoogleTest  
**Profiling:** Linux perf · Valgrind  
**Environment:** Docker  
**CI:** GitHub Actions

## Engineering takeaways

1. Contention can dominate an otherwise efficient algorithm.
2. Work distribution can matter as much as raw worker count.
3. Cache locality becomes increasingly important in throughput-sensitive systems.
4. Performance improvements only matter when concurrency correctness survives.

## Status

🚧 **Active systems-engineering project**

## Author

**Naga Lokesh Sai Alla**  
[GitHub](https://github.com/lokesh8286235) · [LinkedIn](https://linkedin.com/in/naga-lokesh-sai-alla-538242251) · [Portfolio](https://portfolio-r7n2.vercel.app)
