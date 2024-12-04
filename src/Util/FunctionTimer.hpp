#pragma once

// Returns time to execute given fuction in miliseconds.
template <typename T, typename ...Arguments>
double timer(T function, Arguments&&... args) {
    using clock = std::chrono::high_resolution_clock;
    
    auto t1 = clock::now();
    function(std::forward<Arguments>(args)...);
    auto t2 = clock::now();
    
    return std::chrono::duration<double, std::milli>(t2-t1).count();
}