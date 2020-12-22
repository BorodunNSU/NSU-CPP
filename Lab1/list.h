#pragma once

#include "listException.h"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <memory>

template<class T>
class List {
private:
    struct node {
        node *next = nullptr;
        node *previous = nullptr;
        T data = T();

        node() = default;

        explicit node(T data, node *previous = nullptr, node *next = nullptr) :
                data(data), previous(previous), next(next) {}
    };

    node *tail;
    size_t listSize;
public:
    /// \class \a iterator
    /// \brief Iterates through \a list
    class iterator {
        friend class List<T>;

        node *currPtr;
    public:

        /// \brief  Constructor
        ///
        /// Makes \a iterator from \a node pointer
        /// \param[in] current
        explicit iterator(node *current) : currPtr(current) {};

        /// \brief Copy constructor
        ///
        /// Copies iterator
        /// \param other An \a iterator to copy from
        iterator(const iterator &other) {
            currPtr = other.currPtr;
        }

        /// \brief Copy assigment operator
        ///
        /// Copies \a iterator
        /// \param other An \a iterator to copy from
        iterator &operator=(const iterator &other) {
            if ((*this) == other) {
                return *this;
            }
            currPtr = other.currPtr;
            return *this;
        }

        /// \brief \a iterator comparison
        ///
        /// \param[in] other An \a iterator to compare with
        /// \returns \b True if iterators are different
        bool operator!=(const iterator &other) const {
            return currPtr != other.currPtr;
        }

        /// \brief \a iterator comparison
        ///
        /// \param[in] other An \a iterator to compare with
        /// \returns \b True if iterators are similar
        bool operator==(const iterator &other) const {
            return currPtr == other.currPtr;
        }

        /// \brief Element dereferencing
        ///
        /// \returns \b Data on which an \a iterator points to
        T &operator*() {
            return currPtr->data;
        }

        /// \brief Element pointer
        ///
        /// \returns  \a Pointer to a current element
        T *operator->() {
            return &(currPtr->data);
        }

        /// \brief Prefix increment
        ///
        /// \returns \a iterator to the next element
        iterator &operator++() {
            currPtr = currPtr->next;
            return *this;
        }

        /// \brief Postfix increment
        ///
        /// \returns \a iterator that points to the current element
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        /// \brief Prefix decrement
        ///
        /// \returns \a iterator to the previous element
        iterator &operator--() {
            currPtr = currPtr->previous;
            return *this;
        }

        /// \brief Postfix decrement
        ///
        /// \returns \a iterator that points to the current element
        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
    };

    /// \class const_iterator
    /// \brief constant iterator
    class const_iterator  {
        node *currPtr;
    public:
        /// \see \a iterator constructor
        explicit const_iterator (node *current) : currPtr(current) {};

        /// \see \a iterator copy constructor
        const_iterator (const_iterator  const &other) {
            currPtr = other.currPtr;
        }

        /// \see \a iterator copy assigment operator
        const_iterator  &operator=(const const_iterator  &other) {
            if (this == other) {
                return *this;
            }
            currPtr = other.currPtr;
            return *this;
        }

        /// \see \a iterator comparison
        bool operator!=(const const_iterator  &other) const {
            return currPtr != other.currPtr;
        }

        /// \see \a iterator comparison
        bool operator==(const const_iterator  &other) const {
            return currPtr == other.currPtr;
        }

        /// \see \a iterator element dereferencing
        const T &operator*() {
            return currPtr->data;
        }

        /// \see \a iterator element pointer
        const T *operator->() {
            return &(currPtr->data);
        }

        /// \see \a iterator prefix increment
        const_iterator  &operator++() {
            currPtr = currPtr->next;
            return *this;
        }

        /// \see \a iterator postfix increment
        const_iterator  operator++(int) {
            const_iterator  old = *this;
            ++(*this);
            return old;
        }

        /// \see \a iterator prefix decrement
        const_iterator  &operator--() {
            currPtr = currPtr->previous;
            return *this;
        }

        /// \see \a iterator postfix decrement
        const_iterator  operator--(int) {
            const_iterator  old = *this;
            --(*this);
            return old;
        }
    };

    /// \brief Base constructor
    ///
    /// Creates an empty \a list
    List() : listSize(0), tail(new node()) {
        tail->next = tail;
        tail->previous = tail;
    }

    /// \brief Copy constructor
    ///
    /// Allocates new memory and copy data from other
    /// \param[in] other \a list to copy
    List(const List &other) : List() {
        listSize = 0;
        for (auto &item : other) {
            push_back(item);
        }
    }

    /// \brief Move constructor
    ///
    /// Moves \b other to new \a list and than deletes \b other
    /// \param[in] other
    List(List &&other) noexcept {
        listSize = other.listSize;
        tail = other.tail;
        other.listSize = 0;
        other.tail = nullptr;
    }

    /// \brief Destructor
    ///
    /// Destroys List
    ~List() {
        if (!empty()) {
            clear();
        }
        delete tail;
    }

    /// \brief Copy assignment
    ///
    /// Overwrites \a list by \b other
    /// \param[in] other A \a list to copy from
    /// \returns Overwritten \a list
    List &operator=(const List &other) {
        if (this == &other) {
            return *this;
        }
        if (!empty()) {
            clear();
        }
        for (auto item : other) {
            push_back(item);
        }
        return *this;
    }

    /// \brief Move assignment
    ///
    /// Overwrites \a list by \b other and then destroys \b other
    /// \param[in] other A \a list to copy from
    /// \returns Overwritten \a list
    List &operator=(List &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        if (!empty()) {
            clear();
        }
        delete tail;
        listSize = other.listSize;
        tail = other.head;
        other.listSize = 0;
        other.head = nullptr;
        return *this;
    }

    /// \returns \a iterator to the first element of the \a list
    iterator begin() {
        return iterator(tail->next);
    }

    /// \returns \a constant \a iterator to the first element of the \a list
    const_iterator  begin() const {
        return const_iterator (tail->next);
    }

    /// \returns \a constant \a iterator to the first element of the \a list
    const_iterator  cbegin() const {
        return const_iterator (tail->next);
    }

    /// \returns \a iterator to the last element of the \a list
    iterator end() {
        return iterator(tail);
    }

    /// \returns \a constant \a iterator to the last element of the \a list
    const_iterator  end() const {
        return const_iterator (tail);
    }

    /// \returns \a constant \a iterator to the last element of the \a list
    const_iterator  cend() const {
        return const_iterator (tail);
    }

    /// \brief Returns size of List
    /// \returns \a list size
    [[nodiscard]] int size() const {
        return listSize;
    }

    /// \brief Checks if List is empty
    /// \returns \b True if \a list is empty
    [[nodiscard]] bool empty() const {
        return listSize == 0;
    }

    /// \returns reference to the first element in \a list
    T &front() {
        if (empty()) {
            throw ListException("front: List is empty");
        } else {
            return *begin();
        }
    }

    /// \returns reference to the first element in \a list
    const T &front() const {
        if (this->empty()) {
            throw ListException("front: List is empty");
        } else {
            return *begin();
        }
    }

    /// \returns reference to the last element in \a list
    T &back() {
        if (this->empty()) {
            throw ListException("back: List is empty");
        } else {
            return *(--end());
        }
    }

    /// \returns reference to the last element in \a list
    const T &back() const {
        if (this->empty()) {
            throw ListException("back: List is empty");
        } else {
            return *(--end());
        }
    }

    /// \brief Deletes element on position from \a list
    ///
    /// \param[in] position A position to delete element
    /// \returns next element
    iterator erase(iterator position) {
        if (empty() || position == end()) {
            throw ListException("erase: List is empty");
        }

        node *nextNode = position.currPtr->next;
        node *prevNode = position.currPtr->previous;
        prevNode->next = nextNode;
        nextNode->previous = prevNode;
        iterator next = iterator(nextNode);
        delete position.currPtr;
        listSize--;
        return next;
    }

    /// \brief Deletes elements from \a list in a range
    ///
    /// \b end position wont be deleted
    /// \param[in] begin A start position
    /// \param[in] end A finish position
    /// \returns end element
    iterator erase(iterator begin, iterator end) {
        iterator it = begin;
        while (it != end) {
            it = erase(it);
        }
        return end;
    }

    /// \brief Deletes all elements that store \b value
    ///
    /// \param[in] value
    /// \returns amount of deleted elements
    int remove(const T &value) {
        int count = 0;
        iterator current = begin();
        while (current != end()) {
            if (*current == value) {
                current = erase(current);
                ++count;
            } else {
                ++current;
            }
        }
        return count;
    }

    /// \brief Clears list
    void clear() {
        if (!empty()) {
            iterator current = begin();
            while (current != end()) {
                current = erase(current);
            }
        }
    }

    /// \brief Deletes the last element
    void pop_back() {
        erase(--end());
    }

    /// \brief Deletes the first element
    void pop_front() {
        erase(begin());
    }

    /// \brief Inserts element to the end of the \a list
    ///
    /// \param value A value to insert
    void push_back(const T &value) {
        insert(end(), value);
    }

    /// \brief Inserts element to the beginning of the \a list
    ///
    /// \param value A value to insert
    void push_front(const T &value) {
        insert(begin(), value);
    }

    /// \brieg Inserts value to the \a list
    ///
    /// Inserts value before \b before. If list is empty, creates new.
    /// \param before An iterator to insert before
    /// \param value A value to insert
    /// \returns \a iterator of the new element
    iterator insert(iterator before, const T &value) {
        node *newNode = new node(value);
        newNode->previous = before.currPtr->previous;
        newNode->next = before.currPtr;
        before.currPtr->previous->next = newNode;
        before.currPtr->previous = newNode;
        listSize++;
        return iterator(newNode);
    }

    /// \brief Appends one \a list to another
    ///
    /// \param other A \a list to append
    /// \returns United \a list
    List &operator+=(const List &other) {
        if (other.empty()) {
            return *this;
        }
        for (auto item : other) {
            push_back(item);
        }
        return *this;
    }
};

/// \brief Concatenates 2 lists
///
/// \param left first \a list
/// \param right first \a list
/// \returns United \a list
template<class T>
List<T> operator+(const List<T> &left, const List<T> &right) {
    List<T> jointList;
    jointList += left;
    jointList += right;
    return jointList;
}

/// \brief Lists comparison
///
/// \param left first \a list
/// \param right first \a list
/// \returns \b True if \a lists are equal
template<class T>
bool operator==(const List<T> &left, const List<T> &right) {
    if (&left == &right) {
        return true;
    }
    if (left.size() != right.size()) {
        return false;
    }
    auto itLeft = left.begin();
    auto itRight = left.begin();
    while (itLeft != left.end()) {
        if (*itLeft != *itRight) {
            return false;
        }
        ++itLeft;
        ++itRight;
    }
    if (*(left.end()) != *(right.end())) {
        return false;
    }
    return true;
}

/// \brief Lists comparison
///
/// \param left first \a list
/// \param right first \a list
/// \returns \b True if \a lists are not equal
template<class T>
bool operator!=(const List<T> &left, const List<T> &right) {
    return !(left == right);
}
