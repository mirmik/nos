#ifndef NOS_IO__FDFILE_H
#define NOS_IO__FDFILE_H

#include <nos/io/iostream.h>
#include <nos/util/osutil.h>

namespace nos
{

    class file : public nos::iostream
    {
    private:
        int m_fd = -1;

    public:
        file(int fd) : m_fd(fd) {}
        file() {}
        file(const char *path, int flags)
        {
            open(path, flags);
        }

        void set_fd(int fd)
        {
            m_fd = fd;
        }

        int write(const void *ptr, size_t sz) override
        {
            return nos::osutil::write(m_fd, ptr, sz);
        }

        nos::expected<int, nos::input_error> read(void *ptr,
                                                  size_t sz) override;

        bool good()
        {
            return m_fd >= 0;
        }

        int open(const char *path, int mode)
        {
            m_fd = nos::osutil::open(path, mode);
            return m_fd;
        }

        int flush() override
        {
            return 0;
        }

        int close()
        {
            return nos::osutil::close(m_fd);
        }

        int fd() const
        {
            return m_fd;
        }

        int nonblock(bool en)
        {
            return nos::osutil::nonblock(fd(), en);
        }
    };
}

#endif
