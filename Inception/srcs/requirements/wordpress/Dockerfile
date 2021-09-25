FROM debian:buster

RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get -y install vim php-fpm php-mysql php-mbstring php-gd redis-server php-redis php-xml wget
COPY wpress.sh ./
RUN chmod 755 ./wpress.sh
COPY wp-config.php ./
RUN chmod 755 /wp-config.php
ENTRYPOINT [ "./wpress.sh" ]
CMD [ "/usr/sbin/php-fpm7.3", "--nodaemonize" ]