<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://codex.wordpress.org/Editing_wp-config.php
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'me');

/** MySQL database password */
define('DB_PASSWORD', 'justword');

/** MySQL hostname */
define('DB_HOST', 'mysql.regmagik.svc');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8mb4');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         '(VcDLF-K_5F!<8T@?[6]&{C8+`PJ&Mh u7K(iBh284he[PqQU@i;yc-uFmSEr)1s');
define('SECURE_AUTH_KEY',  ' MMDs1l)lif.|K,.Ubn@xe386c&-<T+/>%$ZSq Bc:<n!7g_9K<hG6|tFo}iM]R-');
define('LOGGED_IN_KEY',    'Y?cJlbN]#sZXN|/M|Q[wHe^h+v9|)rKSwnq@_3aPX?zZ`7}l&*1Vx<;#(N]9CIqH');
define('NONCE_KEY',        '0I7b:&ad|UioObsT2X^M&HLR]f>-0[r+},iJh>(W`?{RQd[Y]cg6Z+$w*U+=|NU/');
define('AUTH_SALT',        'MS+Fk@6HI}s;$V72:*#O$YkrwUjx/LVi1?lWxNNyZb1T.[Ig=1X?v*I)%5v0U)7[');
define('SECURE_AUTH_SALT', 'bWq%ZMF$~fSWIm;]-r9g4nVU#s-Oabgh76Osh(5+G_h]lNT}Lt5[C.vh;+QNeX`6');
define('LOGGED_IN_SALT',   'W;etaOqOHbtn2`FQrJV R! }a`};mIQVW(MJ/KD9C~#tcF.<oir:-7t=OH&qg`Bh');
define('NONCE_SALT',       '(f#OUjUWYq+2-3H`W)i,:7? ;__5G*QX$||z#@1mP1Kp)4Ym?7TR5w-D#w0y~cJ+');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the Codex.
 *
 * @link https://codex.wordpress.org/Debugging_in_WordPress
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');
