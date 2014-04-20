<?php
function _RequestInt( $key, $default=0 ) {if(isset($_REQUEST[$key])) return intval($_REQUEST[$key]);else return $default;}
define( 'HardLimit', 10, true );
define( 'DefaultVertexes', 5, true );

$edges = _RequestInt('edges', DefaultVertexes);
$edges = (2<=$edges && $edges<HardLimit) ? $edges : DefaultVertexes;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
	<title>Graphs with <?php echo $edges; ?> Vertices</title>
	<meta name="author" content="Jimmy Liu" />
	<meta name="keywords" content="" />
	<meta name="description" content="" />
<style type="text/css">
body{ font-family: "Microsoft YaHei UI", "微软雅黑", "Segoe UI", "黑体"; background: #69adf8; }
h1 { font-size: 3em; text-align: center; }
h2 { font-size: 2em; text-align: center; }
#Page { width: 80%; margin: auto;text-align: center; }
.Graph { text-align: center; }
</style>
</head>

<body>
<div id="Page">
<h1>Graphs with <?php echo $edges; ?> Vertices</h1>
<?php

$combines = $edges*($edges-1)/2;
$half_combs = floor($combines/2);

$result = file_get_contents('./ResultCache/v'.$edges.'.txt');
$result = explode( "\n", $result );

$savePath = './'.$edges.'/';

echo '<h2>0 Edges: </h2><p>';

$e = $count = 0;
while( $value = each($result) ) {
	$value = $value[1];
	if ( strlen($value)<10 ) {
		$e++;
		if ($e > $half_combs) { $e = $half_combs+1; break; }
		echo "\n</p><h2>".$e.' Edges: </h2><p>';
		continue;
	} $count++;
	$value = explode( '|', $value );
	echo '<img src="'.$savePath.$count.'.png" class="Graph" />';
}

$result = array_reverse($result);
$half_combs = ''.ceil($combines/2);
while ( $value = each($result) ) {
	$value = $value[1];
	if ( strlen($value)>=10 && strncmp($half_combs, $value, strlen($half_combs))!=0 ) break; 
} prev($result); if ($edges==2) { reset($result); each($result); }

echo "\n</p><h2>".$e.' Edges: </h2><p>';
while( $value = each($result) ) {
	$value = $value[1];
	if ( strlen($value)<10 ) {
		$e++;
		echo "\n</p><h2>".$e.' Edges: </h2><p>';
		continue;
	} $count++;
	$value = explode( '|', $value );
	echo '<img src="'.$savePath.$count.'.png" class="Graph" />';
}

?></p>
</div>
</body>
</html>
