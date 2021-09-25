#!/usr/bin/env bash
if [ ! -d /etc/nginx/msunspot.key ]; then
	openssl req -x509 -nodes -days 30 -newkey rsa:2048 -subj "/C=RU/ST=Russia/L=Moscow/" \
		-keyout /etc/nginx/msunspot.key -out /etc/nginx/msunspot.crt
	mv ./nginx.conf /etc/nginx/
fi
exec "$@"