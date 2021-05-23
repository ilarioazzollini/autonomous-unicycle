ARG uid
ARG gid
FROM ubuntu:20.04

ENV HOME /root
ENV USERNAME root
USER $USERNAME
WORKDIR $HOME

RUN apt-get update && apt-get install -y sudo

RUN mkdir -p $HOME
RUN echo "$USERNAME:x:${uid}:${gid}:Developer,,,:$HOME:/bin/bash" >> /etc/passwd && \
    echo "$USERNAME:x:${gid}:" >> /etc/group && \
    echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME && \
    chown ${uid}:${gid} -R $HOME

ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/London"
RUN apt-get update && apt-get -y install tzdata

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgtest-dev

RUN apt-get update && apt-get install -y nautilus
