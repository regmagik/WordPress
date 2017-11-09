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
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         ',Au97(Gp.PtX`F5@[(o+y:%R|^Pbu8Qo<buiz@~u4b7!@/8P5W&ITUPU[o]q#MY;');
define('SECURE_AUTH_KEY',  '/D0 BSra&cpKepWhS)V}^Lf;$0]d}0x7!N5pno~X|&|PLX<kD?bosptz>kJ^M@tx');
define('LOGGED_IN_KEY',    'O13w)3+I)dy}Iaj0D/_?JlpNtWF!!cbGs*A[Kw:Kxg.dRF!|lwu!^==<sbjKQj6g');
define('NONCE_KEY',        '7A|w@N99ii5W#EFk3I#m8.8{Umg|uWjCP:sP`o(5:]#mUN%T{!;N6|PP+3v~9%]9');
define('AUTH_SALT',        '!er[e )2s7=2VJ?RMW3L-<z%t8(bplG<QE2{fLM/_wy|.Xwx=w :snG:mn_gsi4]');
define('SECURE_AUTH_SALT', 'nqG0=l`G0Q~xL859:_$,NSx_DU4Uv/N>Pjw5d,K|,|Q^ySn6p.^CAr<$M;PQ}8}Y');
define('LOGGED_IN_SALT',   'e*c0U6ekT(z8t$>9jKy0R:~iu7HfqMu<w6eD<hkLEDn0-gmeWfUJAzv5!!s#P#N&');
define('NONCE_SALT',       '@*Qn~Z%u8Y#yd:TA*unq8GErf:mef%;^k}7/),*k2H_6S3@d<)D^:AX:cF0K]d86');

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
