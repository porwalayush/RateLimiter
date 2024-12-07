// Token Bucket
// How it works: A bucket is filled with tokens at a constant rate. Each request consumes one token. Requests are only allowed if there are tokens in the bucket.
// Features:
// Bursty traffic: Allows occasional bursts up to the bucket's capacity.
// Smooth requests: Ensures sustained traffic doesn't exceed the refill rate.
// Memory efficient: Requires just two values: tokens and last refill timestamp.
// Use case: Systems needing controlled bursts, such as streaming or video services.



// Token Bucket Algo implementation - per user and role wise configs

#include <bits/stdc++.h>
#include<ctime>
#include <thread>
using namespace std;

void io()
{
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  freopen("Error.txt", "w", stderr);
#endif
}

class TokenBucket {
private:
    int capacity;
    double refill_rate; // Tokens per second
    double tokens;
    time_t last_refill_time;
    double refill_interval; // Derived value for refill intervals- here we will be using =capacity/refill_rate

public:
    // Constructors
    TokenBucket() : capacity(0), refill_rate(0), tokens(0), last_refill_time(time(0)), refill_interval(0) {}

    TokenBucket(int capacity, double refill_rate)
        : capacity(capacity),
          refill_rate(refill_rate),
          tokens(capacity),
          last_refill_time(time(0)),
          refill_interval(static_cast<double>(capacity) / refill_rate) {}

    bool allowRequest() {
        time_t now = time(0);
        double elapsed_time = difftime(now, last_refill_time);

        cout << '\n';
        cout << "Last Refill Time: " << ctime(&last_refill_time);
        cout << "Current Time: " << ctime(&now);
        cout << "Elapsed Time: " << elapsed_time << '\n';

        // Refill tokens if enough time has passed
        if (tokens < capacity && elapsed_time >= refill_interval) {
            int refill_cycles = static_cast<int>(elapsed_time / refill_interval); // How many full intervals have passed
            tokens = min(static_cast<double>(capacity), tokens + refill_cycles * (refill_rate * refill_interval));
            last_refill_time += refill_cycles * refill_interval; // Adjust last refill time
        }

        if (tokens >= 1) {
            --tokens;
            return true;
        }

        return false;
    }
};



class RateLimiter {
private:
  unordered_map<string, pair<int, double> > roleLimits;
  unordered_map<string, TokenBucket > userTokens;

public:
  RateLimiter() {
    roleLimits["admin"] = make_pair(7, 0.583); // burst = 7 and refill bucket after every 12 sec with 7 token-(7/12 = 0.583)
    roleLimits["user"] = make_pair(5, 0.5);  // burst = 5 and refill bucket after every 10 sec with 5 token-(5/10 = 0.5)
    // We can add more configs here
  }

  bool allowRequest(string username, string role) {
    if(roleLimits.find(role)==roleLimits.end()) {
      cout<<"Role configurations not available"<<endl;
      return false;
    }
    if(userTokens.find(username)==userTokens.end()) {
      pair<int, double> config = roleLimits[role];
      userTokens[username] = TokenBucket(config.first, config.second);
    }
    return userTokens[username].allowRequest();
  }

};

int main() {
  io();
  RateLimiter rateLimiter;
  string user = "user123";
  string admin = "admin123";
  for(int i=0;i<=15;i++) {
    cout<<"Request from "<<user<<(rateLimiter.allowRequest(user, "user")?"Allowed":"Denied")<<'\n';
    cout<<"Request from "<<admin<<(rateLimiter.allowRequest(admin, "admin")?"Allowed":"Denied")<<'\n';

    this_thread::sleep_for(chrono::milliseconds(1000)); // assuming 1 sec latency for each call
  }
}






// output:


// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:52 2024
// Elapsed Time: 0
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:52 2024
// Elapsed Time: 0
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:53 2024
// Elapsed Time: 1
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:53 2024
// Elapsed Time: 1
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:54 2024
// Elapsed Time: 2
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:54 2024
// Elapsed Time: 2
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:55 2024
// Elapsed Time: 3
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:55 2024
// Elapsed Time: 3
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:56 2024
// Elapsed Time: 4
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:56 2024
// Elapsed Time: 4
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:57 2024
// Elapsed Time: 5
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:57 2024
// Elapsed Time: 5
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:58 2024
// Elapsed Time: 6
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:58 2024
// Elapsed Time: 6
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:59 2024
// Elapsed Time: 7
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:14:59 2024
// Elapsed Time: 7
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:00 2024
// Elapsed Time: 8
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:00 2024
// Elapsed Time: 8
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:01 2024
// Elapsed Time: 9
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:01 2024
// Elapsed Time: 9
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:02 2024
// Elapsed Time: 10
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:02 2024
// Elapsed Time: 10
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:15:02 2024
// Current Time: Sat Dec  7 17:15:03 2024
// Elapsed Time: 1
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:03 2024
// Elapsed Time: 11
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:15:02 2024
// Current Time: Sat Dec  7 17:15:04 2024
// Elapsed Time: 2
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:04 2024
// Elapsed Time: 12
// Denied
// Request from user123
// Last Refill Time: Sat Dec  7 17:15:02 2024
// Current Time: Sat Dec  7 17:15:05 2024
// Elapsed Time: 3
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:14:52 2024
// Current Time: Sat Dec  7 17:15:05 2024
// Elapsed Time: 13
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:15:02 2024
// Current Time: Sat Dec  7 17:15:06 2024
// Elapsed Time: 4
// Allowed
// Request from admin123
// Last Refill Time: Sat Dec  7 17:15:04 2024
// Current Time: Sat Dec  7 17:15:06 2024
// Elapsed Time: 2
// Allowed
// Request from user123
// Last Refill Time: Sat Dec  7 17:15:02 2024
// Current Time: Sat Dec  7 17:15:07 2024
// Elapsed Time: 5
// Denied
// Request from admin123
// Last Refill Time: Sat Dec  7 17:15:04 2024
// Current Time: Sat Dec  7 17:15:07 2024
// Elapsed Time: 3
// Allowed
