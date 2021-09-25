#!/usr/bin/env bash
sed -i 's@listen = /run/php/php7.3-fpm.sock@listen = 9000@g' /etc/php/7.3/fpm/pool.d/www.conf
sed -i 's/supervised no/supervised systemd/g' /etc/redis/redis.conf
mkdir -p /run/php
touch /run/php/php7.3-fpm.pid
chown -R www-data:www-data /var/www/*
chmod -R 755 /var/www/*
if [ ! -f /var/www/html/wp-config.php ]; then
	mkdir -p /var/www/html/
	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod 555 wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp
	cd var/www/html/
	wp core download --allow-root
	mv /wp-config.php /var/www/html/
	wp core install --allow-root \
	--url=${WPRESS_URL} \
	--title=${WPRESS_TITLE} \
	--admin_user=${WPRESS_USER} \
	--admin_password=${WPRESS_PASS} \
	--admin_email=${WPRESS_EMAIL}
	wp user create --allow-root ${WPRESS_USER_OTH} ${WPRESS_EMAIL_OTH} --user_pass=${WPRESS_PASS_OTH}
fi
service redis-server start
exec "$@"