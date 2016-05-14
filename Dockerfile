FROM ubuntu

RUN apt-get install software-properties-common -y
RUN add-apt-repository ppa:george-edison55/cmake-3.x -y
RUN apt-get update -qq -y && apt-get upgrade -qq -y
RUN apt-get install g++ cmake libcppunit-dev -qq -y

ADD . /code
RUN mkdir -p build
WORKDIR /code/build
RUN cmake ..
RUN make -j

CMD servo --config=files/examples/servod-dummy.conf

EXPOSE 2047
