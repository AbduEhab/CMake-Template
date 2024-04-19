#pragma once
#include <Constants.hpp>

/**
 * @brief A simple timer class that can be used to measure the time it takes to execute a function or a block of code.
 */
struct Timer
{
    /**
     * @brief Construct a new Timer object
     *
     */
    Timer()
    {
        reset();
    }

    /**
     * @brief Reset the timer
     *
     */
    void reset()
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }

    /**
     * @brief Get the elapsed time in seconds
     *
     * @return float
     */
    [[nodiscard]] auto elapsed() const -> float
    {
        return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count()) * 0.001f * 0.001f * 0.001f;
    }

    /**
     * @brief Get the elapsed time in milliseconds
     *
     * @return float
     */
    [[nodiscard]] auto elapsed_millis() const -> float
    {
        return elapsed() * 1000.0f;
    }

    // << operator
    friend auto operator<<(std::ostream &os, const Timer &timer) -> std::ostream &
    {
        os << timer.elapsed();
        return os;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

struct TimedBlock
{
    /**
     * @brief Construct a new Timed Block object
     *
     * @param name The name of the block
     */
    TimedBlock(const std::string &name)
        : m_Name(name)
    {
        m_Timer.reset();
        debug_print("Starting block: ", name);
    }

    ~TimedBlock()
    {
        debug_print("Block '", m_Name, "' took: ", m_Timer.elapsed(), " seconds");
    }

    Timer m_Timer;
    std::string m_Name;
};
