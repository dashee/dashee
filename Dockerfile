FROM ubuntu

RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install g++ make libcppunit-dev -y

ADD . /code
WORKDIR /code
