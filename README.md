 ## Overview

This project implements a multi-threaded Monte Carlo simulator for pricing European call options. It uses pthreads to distribute simulations across multiple threads and estimates the option price by averaging discounted payoffs under a Geometric Brownian Motion (GBM) model.

---

## How It Works

1. The future stock price at expiration is modeled using Geometric Brownian Motion:
   S_T = S * exp((r - 0.5 * v^2) * T + v * sqrt(T) * Z)

2. Each thread:
   - Runs an independent set of Monte Carlo simulations
   - Generates normally distributed random variables using Box–Muller
   - Computes the payoff max(S_T - K, 0)
   - Accumulates a partial payoff sum

3. The main thread:
   - Joins all worker threads
   - Aggregates partial sums
   - Computes the expected payoff
   - Discounts the result to obtain the option price


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
