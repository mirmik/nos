#ifndef NOS_INPUT_ERROR_H
#define NOS_INPUT_ERROR_H

namespace nos
{
    struct input_error
    {
        bool _is_timeout = false;
        bool _is_closed = false;

        static input_error timeout()
        {
            return {true, false};
        }

        static input_error closed()
        {
            return {false, true};
        }

        static input_error ok()
        {
            return {false, false};
        }

        bool is_timeout() const
        {
            return _is_timeout;
        }

        bool is_closed() const
        {
            return _is_closed;
        }

        bool is_ok() const
        {
            return !(_is_timeout || _is_closed);
        }

        operator bool() const
        {
            return is_ok();
        }
    };
}

#endif