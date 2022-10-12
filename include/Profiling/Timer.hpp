#pragma once

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
    float elapsed() const
    {
        return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count()) * 0.001f * 0.001f * 0.001f;
    }

    /**
     * @brief Get the elapsed time in milliseconds
     *
     * @return float
     */
    float elapsed_millis() const
    {
        return elapsed() * 1000.0f;
    }

    // << operator
    friend std::ostream &operator<<(std::ostream &os, const Timer &timer)
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
    }

    ~TimedBlock()
    {
        std::cout << m_Name << ": " << m_Timer << std::endl;
    }

    Timer m_Timer;
    std::string m_Name;
};
