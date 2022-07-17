FROM testlayer

RUN git clone https://github.com/mirmik/nos
RUN cd nos && ./make.py
RUN cd nos && ./make.py install