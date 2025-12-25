 <Monte-Carlo-Options-Simulation>

> A multi-threaded Monte Carlo options simulator that accelerates option pricing by running large-scale randomized payoff simulations in parallel.

---

## Build and Run

### Requirements
- GCC or Clang
- POSIX-compatible system (Linux / macOS)
- pthreads

### Build
```bash
make

---

## Input Parameters

You already prompt the user interactively — explain what those mean:

```md
## Input Parameters

- **S**: Initial stock price
- **K**: Strike price
- **r**: Risk-free interest rate (annualized)
- **v**: Volatility (annualized)
- **T**: Time to expiration (in years)

---

## Example

Input:
- S = 100
- K = 100
- r = 0.05
- v = 0.20
- T = 1

Final Price: ~10.4
Results vary slightly due to randomness
