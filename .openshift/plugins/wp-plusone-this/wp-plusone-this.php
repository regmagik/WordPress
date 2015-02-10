<?php
    /*
    Plugin Name: WP PlusOne This
    Version: 0.2
    Description: Automatically adds Google's PlusOne button to your posts
    Author: Dennis Hernandez
    Author URI: http://bloggermind.net
    Plugin URI: http://bloggermind.net/plugins/wp-plusone-this
    License: GPL2
    */        
/*  Copyright 2011  Dennis Hernandez  (email : plugins@bloggermind.net)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as 
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/      
    /* Version Check */
    global $wp_version;
    $exit_msg='WP PlusOne This requires Wordpress 2.5 or newer.
    <a href="http://codex.wordpress.org/Upgrading_Wordpress">Please update!</a>';
 if (version_compare($wp_version,"2.5","<"))
 {
 exit ($exit_msg);
 }   
/*Adds the neccesary Script to the Header of your Theme for WPPlusOneThis to Work */   
    function wpplusonethis() {
            echo "\n".'<!-- Start wpplusonethis -->'."\n";
            echo '<script type="text/javascript" src="https://apis.google.com/js/plusone.js"></script>' . "\n";   
            echo '<!-- End Of wpplusonethis -->'."\n";
    }
    add_action('wp_head','wpplusonethis');
    
    /* Show a Google Plus One Link */
      add_filter('the_content', 'WPPlusOneThis_ContentFilter');
function WPPlusOneThis_Link()
{
    global $post;
    echo '<div style="display:inline;float:right;margin-left:1em"><g:plusone href="'.get_permalink().'"></g:plusone></div>' . "\n";
    // get the URL to the post or page
}
 function WPPlusOneThis_ContentFilter($content)
{        
    return $content.WPPlusOneThis_Link();        
}

 ?>