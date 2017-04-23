.PHONY: start start_armhf start_aarch64

start:
	docker run -v ${PWD}/app:/app  -it --rm --link crossbar crossbario/autobahn-js

start_armhf:
	docker run -v ${PWD}/app:/app  -it --rm --link crossbar crossbario/autobahn-js-armhf

start_aarch64:
	docker run -v ${PWD}/app:/app  -it --rm --link crossbar crossbario/autobahn-js-aarch64
