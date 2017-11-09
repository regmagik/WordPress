<!DOCTYPE html>
<html <?php language_attributes() ?>>
<head>
<meta http-equiv="Content-Type" content="<?php bloginfo('html_type'); ?>; charset=<?php bloginfo('charset'); ?>" />
<title><?php wp_title( '|', true, 'right' ); ?></title>
<link rel="pingback" href="<?php bloginfo('pingback_url'); ?>" />
<?php wp_head(); ?>
</head>
<body <?php body_class()?>>
	<div class="top-line"><div class="bottom-line">
    <div id="root">
        <div id="header">
        	<div class="headers">&nbsp;</div>
            <div class="content">
		<?php get_search_form() ?>
                <?php if ('blank' != get_header_textcolor()) : ?>
                    <h1><a href="<?php echo esc_url(home_url()); ?>"><?php bloginfo('name'); ?></a></h1>
                    <div class="description"><?php bloginfo('description'); ?></div>
                <?php endif; ?>
		<div style="clear:both"></div>
	        <div id="nav-bar" role="navigation" class="access">
                <?php wp_nav_menu(array('container_class' => 'menu-header', 'theme_location' => 'main', 'depth' => 1)); ?>
	        </div>
            </div>
        </div><!--#header-->
        <div id="main">
		  <div id="headerimg"></div>
