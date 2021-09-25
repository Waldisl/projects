<?php
define( 'DB_NAME', 'wp' );
define( 'DB_USER', 'msunspot' );
define( 'DB_PASSWORD', 'Spotmsun' );
define( 'DB_HOST', 'mariadb' );
define( 'DB_CHARSET', 'utf8' );
define( 'WP_DEBUG', true );
define( 'WP_DEBUG_LOG', true );
define( 'WP_DEBUG_DISPLAY', false );

$table_prefix = 'wp_';

require_once(ABSPATH . 'wp-settings.php');