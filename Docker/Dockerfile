# This Dockerfile was written based on a similar one by Gabriele Baris, check
# out his profile on https://github.com/gabrielebaris.

FROM debian:jessie

ENV USERNAME coder
ENV PASSWORD coder

# Install all the dependencies
RUN apt-get update

# Useful stuff
RUN apt-get install -y \
	apt-file \
	apt-utils \
	build-essential \
	make \
	man \
	sudo \
	tmux \
	less \
	gdb
#	curl \
#	cpio \
#	emacs \
#	git \

# add webupd8 repository (for java8)
#RUN \
#	echo "===> add webupd8 repository..."  && \
#	echo "deb http://ppa.launchpad.net/webupd8team/java/ubuntu trusty main" | tee /etc/apt/sources.list.d/webupd8team-java.list  && \
#	echo "deb-src http://ppa.launchpad.net/webupd8team/java/ubuntu trusty main" | tee -a /etc/apt/sources.list.d/webupd8team-java.list  && \
#	apt-key adv --keyserver keyserver.ubuntu.com --recv-keys EEA14886  && \
#	apt-get update  && \
#	\
#	\
#	echo "===> install Java"  && \
#	echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections  && \
#	echo debconf shared/accepted-oracle-license-v1-1 seen true | debconf-set-selections  && \
#	DEBIAN_FRONTEND=noninteractive  apt-get install -y --force-yes oracle-java8-installer oracle-java8-set-default  && \
#	\
#	\
#	echo "===> clean up..."  && \
#	rm -rf /var/cache/oracle-jdk8-installer

# for XML-RPC in Java (libs and deps)
#RUN apt-get install -y \
#	libxmlrpc3-server-java \
#	libxmlrpc3-client-java \
#	libavalon-framework-java \
#	liblog4j1.2-java \
#	libexcalibur-logkit-java

# for XML-RPC in C
#RUN apt-get install -y libxmlrpc-core-c3

# for OmniORB
#RUN apt-get install -y apt-file

#RUN apt-get install -y \
#	omniidl \
#	omniidl-python \
#	libomnithread3c2 \
#	libomniorb4-1 \
#	libomniorb4-dev

# for ProtoBuf
#RUN apt-get install -y \
#	libprotobuf-dev \
#	libprotobuf-c-dev \
#	protobuf-compiler

# For D-Bus
#RUN apt-get install -y \
#	libdbus-1-dev \
#	libglib2.0-0 \
#	libdbus-glib-1-dev

#For OpenDDS (not used?)
#RUN apt-get install -y \
#	perl-base \
#	perl-modules

#ADD OpenDDS-DDS-3.12.2 /opt/OpenDDS

#RUN cd /opt/OpenDDS && \
#	./configure --prefix=/usr/local --no-tests && \
#	make && \
#	make install && \
#	cp -a /opt/OpenDDS/ACE_wrappers/MPC /usr/local/share/ace/MPC

#ENV ACE_ROOT=/usr/local/share/ace \
#	TAO_ROOT=/usr/local/share/tao \
#	DDS_ROOT=/usr/local/share/dds \
#	PATH=".:/usr/local/share/ace/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# The OpenDDS folder should be deleted

# For alsa
#RUN apt-get install -y libasound2-dev


# Cleaning up stuff
RUN apt-get clean

# Creating a user
RUN useradd --create-home --shell /bin/bash ${USERNAME} && echo "${USERNAME}:${PASSWORD}" | chpasswd && adduser ${USERNAME} sudo
USER ${USERNAME}

# Move to the actual working directory
RUN mkdir /home/${USERNAME}/cbsd-lab
WORKDIR /home/${USERNAME}/cbsd-lab
