FROM ubuntu:20.04

ENV HOME /root

WORKDIR $HOME

RUN apt-get update && apt-get install -y build-essential

ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/London"
RUN apt-get -y install tzdata

RUN apt-get install -y cmake
RUN apt-get install -y libgtest-dev
