# Crossbar.io and Autobahn Starter Templates

The Crossbar.io and Autobahn starter templates in this repository provide minimal skeletons for Docker based router and application components and workers.

The Autobahn starter templates allow development of application code in three languages:

* Python
* JavaScript
* C++

## How to start

### Start Crossbar.io

> The following describes running Crossbar.io via Docker, which is the quickest and easiest way. An alternative for running Crossbar.io without Docker is [installation into a Python virtualenv](http://asciinema.org/a/e9jpon411vb7w82c7fpikha6d
).

Assuming you already have Docker, clone the [Crossbar.io Starter Template Repository](https://github.com/crossbario/crossbar-starter):

```console
git clone https://github.com/crossbario/crossbar-starter.git
```

Then start a new Crossbar.io node from the starter template in a container:

```console
cd crossbar-starter/crossbar
make start
```

[![asciicast](https://asciinema.org/a/6ufqm00z2xmdb3xdnrrzf4es7.png)](https://asciinema.org/a/6ufqm00z2xmdb3xdnrrzf4es7)

Now go to the JavaScript/NodeJS based template folder and start an AutobahnJS component running on NodeJS and connecting to the Crossbar.io node of above:

```console
cd crossbar-starter/autobahn-js
make start
```

[![asciicast](https://asciinema.org/a/5bd3oco61umd4to8qxfixzbh4.png)](https://asciinema.org/a/5bd3oco61umd4to8qxfixzbh4)

