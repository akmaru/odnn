#
# base image
#
FROM ubuntu:22.04 AS base

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV PYTHONIOENCODING=utf-8

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    curl \
    git \
    wget \
    && apt-get clean && rm -rf /var/lib/apt/lists/*


#
# fev image
#
FROM base AS dev

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV PYTHONIOENCODING=utf-8

RUN apt-get update && apt-get install -y --no-install-recommends \
    sudo \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /workspaces/odnn
ENV DEB_PYTHON_INSTALL_LAYOUT=deb_system

# Add a user that UID:GID will be updated by vscode
ARG USERNAME=developer
ARG GROUPNAME=developer
ARG UID=1000
ARG GID=1000
ARG PASSWORD=developer
RUN groupadd -g $GID $GROUPNAME \
    && useradd -m -s /bin/bash -u $UID -g $GID -G sudo $USERNAME \
    && echo $USERNAME:$PASSWORD | chpasswd  \
    && echo "$USERNAME   ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers \
    && echo 'Defaults exempt_group = sudo' >> /etc/sudoers \
    && echo "export DEB_PYTHON_INSTALL_LAYOUT=deb_system" >> /home/developer/.bashrc
