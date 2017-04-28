.PHONY: build

build: build_x86-64 build_armhf build_aarch64 file

build_x86-64:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_x86-64:/build \
		crossbario/autobahn-cpp:gcc \
		/usr/local/app/examples/build

build_armhf:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_armhf:/build \
		crossbario/autobahn-cpp-armhf:gcc \
		/usr/local/app/examples/build

build_aarch64:
	time docker run -it --rm \
		--net=host \
		-v ${PWD}/app:/usr/local/app/examples \
		-v ${PWD}/.build_aarch64:/build \
		crossbario/autobahn-cpp-aarch64:gcc \
		/usr/local/app/examples/build

file:
	ls -la .build_*
	file .build_x86-64/callee
	file .build_armhf/callee
	file .build_aarch64/callee

clean:
	-sudo rm -rf .build_x86-64/callee
	-sudo rm -rf .build_armhf/callee
	-sudo rm -rf .build_aarch64/callee
