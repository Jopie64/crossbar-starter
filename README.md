## How to start on the Pi

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

Run Crossbar.io:

```console
docker run -it --rm crossbario/crossbar-armhf
```

Get Crossbar.io version:

```console
docker run -it --rm --entrypoint=/usr/local/bin/crossbar crossbario/crossbar-armhf version
```
