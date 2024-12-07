# Rate Limiting Algorithms

Rate limiting algorithms are crucial for controlling the flow of requests in a system, ensuring fair usage, and preventing abuse. This document provides an overview of common rate-limiting algorithms, their features, and a comparison between the **Token Bucket** and **Fixed Window Counter** algorithms.

---

## Common Rate Limiting Algorithms

### 1. Fixed Window Counter
**How it works:**  
Maintains a counter for each fixed time window (e.g., 1 minute). The counter increments for each request and resets at the end of the window.

**Features:**
- **Simplicity:** Easy to implement.
- **Granularity Issues:** Can lead to spikes at window boundaries (e.g., a burst of requests at the end and start of consecutive windows).
- **Memory Efficient:** Requires only a single counter per user or client.

**Use case:**  
Basic APIs where fairness is less critical, and minor spikes are acceptable.

---

### 2. Sliding Window Log
**How it works:**  
Maintains a log of timestamps for each request. Checks the log to ensure the number of requests within the sliding window doesn't exceed the allowed limit.

**Features:**
- **Accuracy:** Offers precise control over request limits within a rolling window.
- **High Memory Consumption:** Requires storage of timestamps for each request.
- **Complexity:** More complex compared to fixed windows.

**Use case:**  
APIs requiring fine-grained control over request rates.

---

### 3. Sliding Window Counter
**How it works:**  
Breaks a time window into smaller intervals and maintains counters for each interval. Computes the rate by interpolating between counters.

**Features:**
- **Improved Fairness:** Reduces spikes compared to Fixed Window Counter.
- **Efficiency:** Requires fewer resources than a full Sliding Window Log.
- **Granularity-Dependent:** The choice of sub-interval size impacts performance and accuracy.

**Use case:**  
APIs needing smoother rate-limiting but cannot afford full Sliding Window Logs.

---

### 4. Token Bucket
**How it works:**  
A bucket is filled with tokens at a constant rate. Each request consumes one token. Requests are only allowed if there are tokens in the bucket.

**Features:**
- **Bursty Traffic:** Allows occasional bursts up to the bucket's capacity.
- **Smooth Requests:** Ensures sustained traffic doesn't exceed the refill rate.
- **Memory Efficient:** Requires just two values: tokens and last refill timestamp.

**Use case:**  
Systems needing controlled bursts, such as streaming or video services.

---

### 5. Leaky Bucket
**How it works:**  
Requests are added to a queue (bucket) and processed at a constant rate. Excess requests are discarded when the bucket overflows.

**Features:**
- **Smooth Traffic:** Maintains a steady output rate.
- **No Bursts:** Unlike Token Bucket, bursts are not allowed.
- **Memory Efficient:** Similar to Token Bucket.

**Use case:**  
Applications requiring consistent request flow without bursts, like payment gateways.

---

### 6. Rate-Limiting in Distributed Systems
In a distributed environment, synchronization is critical. Algorithms like Redis-based counters or consistent hashing are commonly used to share counters or tokens across multiple nodes.

---

## Comparison: Token Bucket vs. Fixed Window Counter

| **Feature**              | **Token Bucket**                           | **Fixed Window Counter**                   |
|---------------------------|--------------------------------------------|--------------------------------------------|
| **Traffic Behavior**      | Allows bursts of requests up to bucket size. | May lead to spikes at window boundaries.   |
| **Request Handling**      | Rejects only if no tokens are available.   | Rejects all requests beyond the limit in the window. |
| **Implementation**        | Slightly more complex due to token refill logic. | Simple to implement with a single counter. |
| **Granularity**           | Provides smoother rate-limiting.           | Coarse-grained; no control over spikes.    |
| **Use Cases**             | Ideal for bursty traffic (e.g., streaming). | Best for simple, periodic rate limits.     |

---

## Contributions
Feel free to contribute by submitting pull requests or raising issues to improve this repository.

---
