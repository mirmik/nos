ARG ARCH
FROM netricks/netricks-20.04-env:$ARCH

ADD . /root/nos

WORKDIR /root/nos
RUN ./make.py
RUN ./runtests
RUN sudo ./make.py install
