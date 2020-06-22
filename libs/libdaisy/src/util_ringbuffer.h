// # RingBuffer
// ## Description
// Utility Ring Buffer
// ## Credit
// imported from pichenettes/stmlib
//
#pragma once
#ifndef DSY_RINGBUFFER_H
#define DSY_RINGBUFFER_H

#include <algorithm>

namespace daisy
{
// ## RingBuffer
template <typename T, size_t size>
class RingBuffer
{
  public:
    RingBuffer() {}

	// ### Init
    // Initializes the Ring Buffer
	// ~~~~
    inline void Init() { read_ptr_ = write_ptr_ = 0; }
	// ~~~~

	// ### capacity
	// Returns the total size of the ring buffer
	// ~~~~
    inline size_t capacity() const { return size; }
    // ~~~~

    // ### writable
    // Returns the number of samples that can be written to ring buffer without overwriting unread data.
	// ~~~~
    inline size_t writable() const
	// ~~~~
    {
        return (read_ptr_ - write_ptr_ - 1) % size;
    }

	// ### readable
    // Returns number of unread elements in ring buffer
	// ~~~~
    inline size_t readable() const { return (write_ptr_ - read_ptr_) % size; }
	// ~~~~

	// ### Write
    // Writes the value to the next available position in the ring buffer
	// ~~~~
    inline void Write(T v)
	// ~~~~
    {
        while(!writable())
            ;
        Overwrite(v);
    }

	// ### Overwrite
	// Writes the new element to the ring buffer, overwriting unread data if necessary.
    inline void Overwrite(T v)
    {
        size_t w   = write_ptr_;
        buffer_[w] = v;
        write_ptr_ = (w + 1) % size;
    }

	// ### Read
	// Reads the first available element from the ring buffer
	// ~~~~
    inline T Read()
	// ~~~~
    {
        while(!readable())
            ;
        return ImmediateRead();
    }

	// ### ImmediateRead
	// Reads next element from ring buffer immediately
	// ~~~~
    inline T ImmediateRead()
	// ~~~~
    {
        size_t r      = read_ptr_;
        T      result = buffer_[r];
        read_ptr_     = (r + 1) % size;
        return result;
    }

	// ### Flush
	// Flushes unread elements from the ring buffer
	// ~~~~
    inline void Flush() { write_ptr_ = read_ptr_; }
	// ~~~~

	// ### Swallow
	// Read enough samples to make it possible to read 1 sample.
	// ~~~~
    inline void Swallow(size_t n)
	// ~~~~
    {
        if(writable() >= n)
        {
            return;
        }
        read_ptr_ = (write_ptr_ + 1 + n) % size;
    }

	// ### ImmediateRead (Multiple elements)
	// Reads a number of elements into a buffer immediately
	// ~~~~
    inline void ImmediateRead(T* destination, size_t num_elements)
	// ~~~~
    {
        size_t r    = read_ptr_;
        size_t read = num_elements;

        if(r + read > size)
        {
            read = size - r;
        }
        std::copy(&buffer_[r], &buffer_[r + read], destination);
        if(read != num_elements)
        {
            std::copy(
                &buffer_[0], &buffer_[num_elements - read], destination + read);
        }
        read_ptr_ = (r + num_elements) % size;
    }

	// ### Overwrite (Multiple elements)
	// Overwrites a number of elements using the source buffer as input.
	// ~~~~
    inline void Overwrite(const T* source, size_t num_elements)
	// ~~~~
    {
        size_t w       = write_ptr_;
        size_t written = num_elements;

        if(w + written > size)
        {
            written = size - w;
        }
        std::copy(source, source + written, &buffer_[w]);
        if(written != num_elements)
        {
            std::copy(source + written, source + num_elements, &buffer_[0]);
        }

        write_ptr_ = (w + num_elements) % size;
    }

  private:
    T               buffer_[size];
    volatile size_t read_ptr_;
    volatile size_t write_ptr_;
};

template <typename T>
class RingBuffer<T, 0>
{
  public:
    RingBuffer() {}

    inline void   Init() {}
    inline size_t capacity() const { return 0; }
    inline size_t writable() const { return 0; }
    inline size_t readable() const { return 0; }
    inline void   Write(T v) {}
    inline void   Overwrite(T v) {}
    inline T      Read() { return T(0); }
    inline T      ImmediateRead() { return T(0); }
    inline void   Flush() {}
    inline void   ImmediateRead(T* destination, size_t num_elements) {}
    inline void   Overwrite(const T* source, size_t num_elements) {}

  private:
};

} // namespace daisy

#endif
