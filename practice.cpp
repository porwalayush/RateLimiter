#include<bits/stdc++.h>
#include <ctime>
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
    double refill_rate;
    int tokens;
    time_t lastRefillTime;

public:
	    // Constructor
    TokenBucket() 
    : capacity(100), refill_rate(1.0), tokens(100), lastRefillTime(time(0)) {}
    
    TokenBucket(int capacity, double refill_rate)
    : capacity(capacity), refill_rate(refill_rate), tokens(capacity), lastRefillTime(time(0)) {}
    bool allowRequest() {
        time_t current_time = time(0);  // Get current time in time_t

        // Print the current and last refill times for debugging
        cout << "Last Refill Time: " << ctime(&lastRefillTime);
        cout << "Current Time: " << ctime(&current_time);

        double elapsedTime = difftime(current_time, lastRefillTime);  // Calculate elapsed time in seconds
        lastRefillTime = current_time;  // Update last refill time

        // Refill tokens based on elapsed time
        tokens = min(static_cast<double>(capacity), tokens + elapsedTime * refill_rate);
        
        if (tokens > 0) {
            tokens--;  // Deduct one token for the request
            return true;
        }
        return false;
    }
};

class RateLimitter {
public:
    RateLimitter() {
        role_wise_config["admin"] = make_pair(10, 4.0);
        role_wise_config["user"] = make_pair(10, 2.0);
    }

    bool allowRequest(string username, string role) {
        if (role_wise_config.find(role) == role_wise_config.end()) {
            cout << "Role not available" << endl;
            return false;
        }

        if (user_to_bucket.find(username) == user_to_bucket.end()) {
            pair<int, double> val = role_wise_config[role];
            user_to_bucket[username] = TokenBucket(val.first, val.second);
        }
        
        return user_to_bucket[username].allowRequest();
    }

private:
    unordered_map<string, pair<int, double> > role_wise_config;
    unordered_map<string, TokenBucket> user_to_bucket;
};

int32_t main() {
    io();
    RateLimitter rateLimiter;
    string userId1 = "user123";
    string userId2 = "admin456";

    for (int i = 0; i < 15; ++i) {
        cout << "Request " << i + 1 << " from " << userId1 << " (user): "
             << (rateLimiter.allowRequest(userId1, "user") ? "Allowed" : "Denied") << "\n";

        cout << "Request " << i + 1 << " from " << userId2 << " (admin): "
             << (rateLimiter.allowRequest(userId2, "admin") ? "Allowed" : "Denied") << "\n";

        this_thread::sleep_for(chrono::milliseconds(30)); // Simulate time between requests
    }

    return 0;
}
