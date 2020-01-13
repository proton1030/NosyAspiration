#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>
#include "Interpolater.h"
/*! \brief implement a circular buffer of type T with time varying read pointer
*/
template <class T> 
class CRingBuffer
{
public:
    explicit CRingBuffer (int buff_length) :
        buff_length(buff_length),
        rptr(0),
        wptr(0),
        buff(buff_length, 0)
    {
        assert(buff_length > 0);
        reset();
    }

    /*! add a new value of type T to write index and increment write index
    \param new_val the new value
    \return void
    */
    void putPostInc (T new_val)
    {
        put(new_val);
        incPtr(wptr);
    }
    
    /*! add the new value of type T to the old value at write index and increment write index
     \param new_val the new value
     \return void
     */
    void putPostIncWithAdd (T new_val)
    {
        put(new_val + buff[wptr]);
        incPtr(wptr);
    }

    /*! add new values of type T to write index and increment write index
    \param vec: new values
    \return void
    */
    void putPostInc (const std::vector<T> &vec)
    {
        put(vec);
        incPtr(wptr, vec.size());
    }

    /*! add a new value of type T to write index
    \param new_val the new value
    \return void
    */
    void put(T new_val)
    {
        buff[static_cast<int>(wptr)] = new_val;
    }

    /*! add new values of type T to write index
    \param vec new values
    \return void
    */
    void put(const std::vector<T> &vec)
    {
        assert(vec.size() <= buff.size());
        // copy two parts: to the end of buffer and after wrap around
        int numValuesToEnd = std::min(vec.size(), buff.size() - wptr);
        std::copy(vec.begin(), vec.begin() + numValuesToEnd, buff.begin() + wptr);
        std::copy(vec.begin() + numValuesToEnd, vec.end(), buff.begin());
    }
    
    /*! return the value at the current read index and increment the read pointer
    \return T the value from the read index
    */
    T getPostInc ()
    {
        T value = get();
        incPtr(rptr, 1-g);
        return value;
    }

    /*! return the value at the current read index
    \param offset: read at offset from read index
    \return T the value from the read index
    */
    T get (float offset = 0) const
    {
        const float read_pos = fmod(rptr + offset, buff_length);
        return Interpolater::linearInterpolate(buff, read_pos);
    }
    
    /*! bulk fill in a given vec
    \param vec: vec to be filled
     */
    void get (std::vector<T> &vec)
    {
        assert(vec.size() <= buff.size());
        int numValuesToEnd = std::min(vec.size(), buff.size() - rptr);
        std::copy(buff.begin() + rptr, buff.begin() + rptr + numValuesToEnd, vec.begin(), vec.begin + numValuesToEnd);
        std::copy(buff.begin(), buff.begin() + vec.size() - numValuesToEnd, vec.begin() + numValuesToEnd, vec.end());
    }
    
    /*! set buffer content and indices to 0
    \return void
    */
    void reset ()
    {
        std::fill(buff.begin(), buff.end(), 0);
        rptr = 0;
        wptr = 0;
        g = 0;
    }

    /*! return the current index for writing/put
    \return float
    */
    float getWriteIdx () const
    {
        return wptr;
    }

    /*! move the write index to a new position
    \param new_wptr: new write position
    \return void
    */
    void setWriteIdx (float new_wptr)
    {
        incPtr(wptr, new_wptr - wptr);
    }

    /*! return the current index for reading/get
    \return float
    */
    float getReadIdx () const
    {
        return rptr;
    }

    /*! move the read index to a new position
    \param new_rptr: new read position
    \return void
    */
    void setReadIdx (float new_rptr)
    {
        incPtr(rptr, new_rptr - rptr);
    }
    
    /*! return the current time varying rate
    \return float
    */
    float getTimeVaryRate()
    {
        return g;
    }
    
    /*! change time varying rate to a new rate
    \param new_rptr: new read position
    \return void
    */
    void setTimeVaryRate (float new_g)
    {
        g = new_g;
    }

    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer () const
    {
        return (wptr - rptr + buff.size()) % buff.size();
    }
    
    /*! returns the delay line length according to read/write pointer position
    \return float
    */
    float getReadWritePtrDistance () const
    {
        return rptr > wptr ? static_cast<float>(buff_length) - fabs(rptr - wptr) : wptr - rptr;
    }

    /*! returns the length of the internal buffer
    \return int
    */
    int getLength () const
    {
        return buff_length;
    }
private:
    CRingBuffer ();
    CRingBuffer(const CRingBuffer& that);

    void incPtr (float &ptr, float offset = 1)
    {
        while ((ptr + offset) < 0)
        {
            // avoid negative buffer indices
            offset += buff_length;   
        }
        ptr = fmod(ptr + offset, buff_length);
    };

    int buff_length;              //!< length of the internal buffer
    float rptr, wptr;  //!< current read/write index
    float g; //!< delay changing rate
    
    std::vector<T> buff;                  //!< data buffer
};
#endif // __RingBuffer_hdr__
