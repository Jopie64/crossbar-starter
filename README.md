# Crossbar.io and Autobahn Application Starter Templates

The Crossbar.io and Autobahn application starter templates in this repository provide minimal skeletons for creating WAMP routers and application components (workers).

The Autobahn starter templates allow development of application code in three languages:

* Python
* JavaScript
* C++

and for all four WAMP roles:

* Caller
* Callee
* Publisher
* Subscriber

All templates are Docker based and kept in sync with Crossbar.io, Autobahn and with each other, so you have a complete set of working code that can be run immediately.

The templates are liberally licensed under the MIT and can be used as a starting point in any licensing context.


## How to start

> The following describes running Crossbar.io via Docker, which is the quickest and easiest way. An alternative for running Crossbar.io without Docker is [installation into a Python virtualenv](http://asciinema.org/a/e9jpon411vb7w82c7fpikha6d
).

Assuming you already have Docker, clone the [Crossbar.io Starter Template Repository](https://github.com/crossbario/crossbar-starter):

```console
git clone https://github.com/crossbario/crossbar-starter.git
```

### Crossbar.io

Then start a new Crossbar.io node from the starter template in a container:

```console
cd crossbar-starter/crossbar
make start
```

[![asciicast](https://asciinema.org/a/6ufqm00z2xmdb3xdnrrzf4es7.png)](https://asciinema.org/a/6ufqm00z2xmdb3xdnrrzf4es7)


### AutobahnJS

Now go to the JavaScript/NodeJS based template folder and start an AutobahnJS component running on NodeJS and connecting to the Crossbar.io node of above:

```console
cd crossbar-starter/autobahn-js
make start
```

[![asciicast](https://asciinema.org/a/5bd3oco61umd4to8qxfixzbh4.png)](https://asciinema.org/a/5bd3oco61umd4to8qxfixzbh4)


### AutobahnPython

### AutobahnC++
