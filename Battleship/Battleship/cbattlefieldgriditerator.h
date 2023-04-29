#pragma once

#include <cmath>
#include <iterator>
#include <vector>

/**
 * @brief The CBattleFieldGridIterator class
 * Wir bauen uns einen Iterator für einen 2 dimensionalen Vektor
 * @remark Ist es sinnvoll einen Container zu erfinden, und einen Iterator dafür zu bauen, wenn sich das mit STL
 * Containern umsetzen ließe? - NEIN!
 * Ist es einfacher einen Container zu erfinden, und einen Iterator dafür zu bauen, wenn sich das mit STL
 * Containern umsetzen ließe? - Um Gottes Willen, NEIN!
 * Machen wir es trotzdem? - FUCK YEAH!
 * Warum? - Weil wir es können!
 * @remark - Wir implementieren alles in den Header. Das ist nicht schön, aber wir haben eine Template Klasse, und
 * müssen den Compiler zwingen die Klasse kompiliert zu haben, wenn wir sie Brauchen. Das ist eine Möglichkeit, die
 * andere Option findet sich im Container.
 * @sa CBattleFieldGrid
 */

template <typename TIteratorType, typename TContainerType>
struct CBattleFieldGridIterator
{
public:
    /**
     * @remark Diese definitionen sind notwendig, damit der Compiler das ganze Konstrukt als Iterator nutzen kann
     * Wie bauen einen bidirektionalen Iterator, man kann also in beide Richtungen iterieren.
     */

    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<TIteratorType>;
    using pointer = TIteratorType*;
    using reference = TIteratorType&;

    /**
     * für die Bessere Lesbarkeit
     * der self_type ist nicht notwendig.
     */
    using self_type = CBattleFieldGridIterator;

    /**
     * @brief CBattleFieldGridIterator
     * Im Konstruktor bekommt der Iterator einen Zeiger auf das Grid, und eine Startposition
     * @param vv Zeiger auf den Container
     * @param outer y-Pos
     * @param inner x-Pos
     */

    CBattleFieldGridIterator(TContainerType* vv, std::size_t outer, std::size_t inner) :
        _vectorOfVectors(vv),
        _outerIndex(outer),
        _innerIndex(inner)
    {
    }

    /**
     * Ab hier Standard. Alle Iteratoren müssen die folgenden Operatoren implementieren. Die Zugriffsopteratoren (* und
     * ->) müssen const und nicht-const vorhanden sein. Aufpassen beim Lesen, *this benutzt den ersten *-Operatore zum
     * dereferenzieren des Wertes. (Also das, was der Iterator landläufig so macht.) Natürlich implementieren wir den
     * Zugriff nur einmal und benutzen ihn dann.
     */

    reference operator*()
    {
        return _vectorOfVectors->at(_outerIndex).at(_innerIndex);
    }

    reference operator*() const
    {
        return *this;
    }

    pointer operator->() const
    {
        return this;
    }
    pointer operator->()
    {
        return this;
    }

    /**
     * Inkrement und Dekrement jeweils als Postfix und als Prefix
     * Auch hier wieder einmal implementieren und dann nutzen.
     * Wir greifen auch auf den reference operator zurück
     */
    self_type& operator++()
    {
        if (numericIndex() >= numericSize())
        {
            setToEnd();
            return *this;
        }

        if (_innerIndex + 1 < width())
        {
            ++_innerIndex;
        }
        else
        {
            if (_outerIndex + 1 < height())
            {
                ++_outerIndex;
                _innerIndex = 0;
            }
            else
            {
                setToEnd();
            }
        }
        return *this;
    }

    self_type operator++(int)
    {
        auto retval = *this;
        ++(*this);
        return retval;
    }

    self_type& operator--()
    {

        if (_innerIndex > 0)
        {
            --_innerIndex;
        }
        else
        {
            if (_outerIndex > 0)
            {
                --_outerIndex;
                _innerIndex = _vectorOfVectors->at(_outerIndex).size() - 1;
            }
            else
            {
                setToBegin();
            }
        }
        return *this;
    }

    self_type operator--(int)
    {
        TIteratorType retval = *this;
        --(*this);
        return retval;
    }

    /**
     * Und weil wir es wissen wollten und einen Random Access Iterator gebaut haben (sozusagen die Künigin Mutter der
     * Iteratoren), müssen wir auch arithmetische Operatoren haben.
     */

    inline difference_type operator-(const self_type& rhs) const
    {
        return (_innerIndex + _outerIndex) - (rhs._innerIndex + rhs._outerIndex);
    }
    inline self_type operator+(const difference_type rhs) const
    {
        if (rhs < 0)
        {
            return *this - std::abs(rhs);
        }
        if (numericIndex() + rhs > numericSize())
        {
            return cend();
        }

        int outer(_outerIndex);
        int inner(_innerIndex);
        int ctr(rhs);

        while (ctr > 0)
        {
            inner++;
            if (inner >= width())
            {
                inner = 0;
                outer++;
            }
            ctr--;
        }

        return self_type(_vectorOfVectors, outer, inner);
    }
    inline self_type operator-(const difference_type rhs) const
    {
        if (rhs < 0)
        {
            return *this + std::abs(rhs);
        }

        int idx = (int)numericIndex();
        if (idx - rhs <= 0)
        {
            return cbegin();
        }

        int outer(_outerIndex);
        int inner(_innerIndex);
        int ctr(rhs);

        while (ctr > 0)
        {
            inner--;
            if (inner < 0)
            {
                inner = width() - 1;
                outer--;
            }
            ctr--;
        }

        return self_type(_vectorOfVectors, outer, inner);
    }
    friend inline self_type operator+(const difference_type lhs, const self_type& rhs)
    {
        return lhs + rhs;
    }
    friend inline self_type operator-(const difference_type lhs, const self_type& rhs)
    {
        return lhs - rhs;
    }

    /**
     * Und zu guter Letzt muss der Kram noch vergleichbar sein.
     */

    bool operator==(const self_type& other) const
    {
        return other._vectorOfVectors == _vectorOfVectors && other._outerIndex == _outerIndex &&
               other._innerIndex == _innerIndex;
    }
    bool operator!=(const self_type& other) const
    {
        return !(*this == other);
    }

    inline bool operator>(const self_type& rhs) const
    {
        return numericSize() > rhs.numericSize();
    }
    inline bool operator<(const self_type& rhs) const
    {
        return numericSize() < rhs.numericSize();
    }
    inline bool operator>=(const self_type& rhs) const
    {
        return numericSize() >= rhs.numericSize();
    }
    inline bool operator<=(const self_type& rhs) const
    {
        return numericSize() <= rhs.numericSize();
    }

    /**
     * @brief x
     * der Iterator soll auch seine Position verraten
     * @return x-coordinate
     */
    size_t x() const
    {
        return _innerIndex;
    }

    /**
     * @brief y
     * der Iterator soll auch seine Position verraten
     * @return y-coordinate
     */
    size_t y() const
    {
        return _outerIndex;
    }

private:
    /**
     * Hilfsfunktionen
     */

    size_t numericSize() const
    {
        return height() * width();
    }
    size_t numericIndex() const
    {
        return (_outerIndex * width()) + _innerIndex;
    }
    size_t width() const
    {
        return _vectorOfVectors->size() ? _vectorOfVectors->at(0).size() : 0;
    }
    size_t height() const
    {
        return _vectorOfVectors->size();
    }

    self_type cend() const
    {
        return self_type(_vectorOfVectors, _vectorOfVectors->size(), 0);
    }

    self_type cbegin() const
    {
        return self_type(_vectorOfVectors, 0, 0);
    }

    void setToEnd()
    {
        _innerIndex = 0;
        _outerIndex = _vectorOfVectors->size();
    }

    void setToBegin()
    {
        _innerIndex = 0;
        _outerIndex = 0;
    }

    TContainerType* _vectorOfVectors;
    std::size_t _outerIndex = 0;
    std::size_t _innerIndex = 0;
};
