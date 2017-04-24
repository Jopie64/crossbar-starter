## How to start on the Pi

### Preparation

Download [Raspbian Jessie Lite](https://downloads.raspberrypi.org/raspbian_lite_latest), unpack and write the image to a SD card:

```console
sudo dd if=~/2017-04-10-raspbian-jessie-lite.img of=/dev/sdb bs=1M oflag=sync
```

As of the November 2016 release, Raspbian has the SSH server disabled by default (see [here](https://www.raspberrypi.org/documentation/remote-access/ssh/)). To enable SSH, mount the image on your PC and add a single file empty  `/boot/ssh`

```console
touch /media/oberstet/boot/ssh
sudo sync
```

Now SSH into the Pi (the default password is `raspberry`):

```console
ssh pi@192.168.1.31
```

Update the system

```console
sudo apt update
sudo apt dist-upgrade
```

and install Docker

```
curl -sSL get.docker.com | sh
sudo systemctl enable docker
sudo usermod -aG docker pi
sudo reboot
```

Test Docker:

```console
docker run -it --rm armhf/alpine /bin/sh
```


### Run Crossbar.io

To run a Docker container with Crossbar.io:

```console
docker run -it --rm crossbario/crossbar-armhf
```

To get the Crossbar.io software versions of the packages within the container:

```console
pi@raspberrypi:~ $ docker run -it --rm --entrypoint=/usr/local/bin/crossbar crossbario/crossbar-armhf version
     __  __  __  __  __  __      __     __
    /  `|__)/  \/__`/__`|__) /\ |__)  |/  \
    \__,|  \\__/.__/.__/|__)/~~\|  \. |\__/

 Crossbar.io        : 17.3.1 (Crossbar.io COMMUNITY)
   Autobahn         : 0.18.1 (with JSON, MessagePack, CBOR, UBJSON)
   Twisted          : 17.1.0-EPollReactor
   LMDB             : 0.92/lmdb-0.9.18
   Python           : 3.6.1/CPython
 OS                 : Linux-4.4.50-v7+-armv7l-with-debian-8.7
 Machine            : armv7l
 Release key        : RWRGxs0uB6vQemWGPeBt7nLG53ADoOtZy/Vve3BjlaXDqkCiVhCs7Zrv
```


### Crossbar.io and Autobahn

To get the starter template, clone our repo

```console
cd ~
git clone https://github.com/crossbario/crossbar-starter.git
```

In a first terminal, start Crossbar.io

```console
cd ~/crossbar-starter/crossbar
make start_armhf
```

In a second terminal, start Crossbar.io

```console
cd ~/crossbar-starter/autobahn-python
make start_armhf
```

In a third terminal, start Crossbar.io

```console
cd ~/crossbar-starter/autobahn-js
make start_armhf
```

### Development Setup

One way you can do development on the Pi that we find comfortable and relatively hassle free is to mount a working directory from your development notebook on the Pi.

Determine the IP address of your notebook on the local network, assuming this is a 192er network:

```console
oberstet@thinkpad-t430s:~/scm/crossbario/crossbar-starter$ ifconfig | grep 192
          inet Adresse:192.168.55.138  Bcast:192.168.55.255  Maske:255.255.255.0
```

Further assuming your working directory is `/home/oberstet/scm`. Then to remotely mount this, login on the Pi and install **sshfs** once:

```console
sudo apt-get install sshfs
```

and then mount the remote filesystem from your notebook on the Pi:

```console
sudo sshfs -o allow_other oberstet@192.168.55.138:/home/oberstet/scm ~/scm
```

Now, you can move around in the directories on this mountpoint, and effectively you will be browsing your notebook of course.

You can also open and edit files on your notebook using your favorite editor, and the changes will be be reflected on the Pi immediately.

And this is the key for this approach to the development cycle:

- you remotely log into the Pi at the console and start components directly from a mirror of your working directory
- you open and edit files locally on your notebook using your local editor


### Bundled Images

For the Pi, the following Docker images provided by the Crossbar.io Project will work:


```console
docker pull crossbario/crossbar-armhf:community-cpy3
docker pull crossbario/autobahn-python-armhf:cpy2
docker pull crossbario/autobahn-python-armhf:cpy3
docker pull crossbario/autobahn-python-armhf:pypy2
docker pull crossbario/autobahn-python-armhf:pypy3
docker pull crossbario/autobahn-python-armhf:cpy2-minimal-aio
docker pull crossbario/autobahn-python-armhf:cpy3-minimal-aio
docker pull crossbario/autobahn-python-armhf:cpy2-minimal-tx
docker pull crossbario/autobahn-python-armhf:cpy3-minimal-tx
docker pull crossbario/autobahn-js-armhf:full
docker pull crossbario/autobahn-js-armhf:alpine
```
