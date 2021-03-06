#!/bin/bash

#config nginx

cp etc/nginx.conf /etc/nginx/sites-available/localhost
ln -s /etc/nginx/sites-available/localhost /etc/nginx/sites-enabled/
rm -rf /etc/nginx/sites-enabled/default
chown -R www-data:www-data /var/www

# certificat SSL

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
-subj "/C=ru/ST=Russia/L=Kazan/O=Ecole_42/OU=School_21_Kazan/CN=Msunspot/" \
-keyout /etc/ssl/private/nginx-selfsigned.key -out /etc/ssl/certs/nginx-selfsigned.crt

# phpmyadmin

wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz
tar -zxvf phpMyAdmin-4.9.0.1-all-languages.tar.gz 
mv phpMyAdmin-4.9.0.1-all-languages phpmyadmin
mv phpmyadmin /var/www
rm phpMyAdmin-4.9.0.1-all-languages.tar.gz


# wordpress

wget https://wordpress.org/latest.tar.gz
tar -xzvf latest.tar.gz
mv wordpress /var/www
rm latest.tar.gz
mv var/wp-config.php var/www/wordpress


# start mysql

service mysql restart
echo "CREATE USER 'root'@'localhost';" | mysql -u root
echo "CREATE DATABASE wordpress;" | mysql -u root
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost' identified by 'root';" | mysql -u root
echo "FLUSH PRIVILEGES;" | mysql -u root


# restart
service php7.3-fpm restart 
service nginx restart
bash
