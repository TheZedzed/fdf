FROM alpine

RUN apk -U upgrade && apk add \
	gcc \
	make \
	musl-dev \
	valgrind \
	libx11-dev \
	libxext-dev \
	libbsd-dev

WORKDIR	/home

COPY project .

RUN chmod +x install.sh

CMD ["./install.sh"]
