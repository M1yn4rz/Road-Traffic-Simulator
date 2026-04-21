#ifndef IDGENERATOR_H
#define IDGENERATOR_H

/**
 * @brief Template utility class generating unique identifiers.
 *
 * Separate counters are maintained for each template type.
 *
 * @tparam T Type for which identifiers are generated.
 */
template<typename T>
class IdGenerator
{
public:

    /**
     * @brief Returns next available identifier.
     * @return Unique integer ID.
     */
    static int Next()
    {
        static int current = 1;
        return current++;
    }
};

#endif
